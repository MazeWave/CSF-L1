from flask import *

app = Flask(__name__, template_folder='./')

@app.route("/")
def get_index():
    return render_template('web.html', page="Home")

@app.route("/stats")
def get_stats():
    return render_template('web.html', page='Stats')

@app.route("/logs")
def get_console():
    return render_template('web.html', page='Logs')


if __name__ == '__main__':
    app.run(host="localhost", port=3000, debug=True)

