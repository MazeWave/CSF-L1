from flask            import Flask, render_template
from paho.mqtt.client import Client
from threading        import Thread, RLock
from random           import randint
from json             import loads, dumps
from datetime         import datetime

app = Flask(__name__, template_folder='./')
dataLock = RLock()


broker = 'eu1.cloud.thethings.network'
port   = 1883
topic  = "v3/valuence-project@ttn/devices/valuence-1/up"

client_id = f'valuence-mqtt-{randint(0, 100)}'
username = 'valuence-project@ttn'
password = 'FILL ME'

def connect_mqtt() -> Client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def subscribe(client: Client):
    def on_message(client, userdata, msg):
        data = loads(msg.payload.decode())
        dataLock.acquire()
        print(dumps(data, indent=4, sort_keys=True))
        with open("data.csv", mode="a", encoding="UTF-8") as file:
            payload = data["uplink_message"]["decoded_payload"]
            file.write(f"{payload['devid']},{datetime.now()},{payload['motions']}\n")
        dataLock.release()

    client.subscribe(topic)
    client.on_message = on_message


def mqtt_run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()

mqtt = Thread(target=mqtt_run)

@app.route("/")
def get_index():
    return render_template('web.html', page="Home")

@app.route("/stats")
def get_stats():
    with open("data.csv", mode="r", encoding="UTF-8") as file:
        motions = [int(line.split(",")[2]) for line in file.readlines()]
    return render_template('web.html', page='Stats', total=sum(motions))

@app.route("/logs")
def get_console():
    with open("data.csv", mode="r", encoding="UTF-8") as file:
        data = [line.split(",") for line in file.readlines()]
        logs = [f"DEVICE {devid} AT {time} : {motions} occurences." for devid, time, motions in data]
    return render_template('web.html', page='Logs', logdata=logs)



if __name__ == '__main__':
    mqtt.start()
    app.run(host="localhost", port=3000, debug=True)
    mqtt.join()

