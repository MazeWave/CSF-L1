import flask    as flk
import sqlite3  as sql
import requests as req

app = flk.Flask(__name__, template_folder='./')
con = sql.connect("./data")
mem = sql.connect(":memory:")

@app.route("/")
def get_index():
    return flk.render_template('web.html', page="Home")

@app.route("/stats")
def get_stats():
    return flk.render_template('web.html', page='Stats')

@app.route("/logs")
def get_console():
    return flk.render_template('web.html', page='Logs')



if __name__ == '__main__':
    app.run(host="localhost", port=3000, debug=True)
    con.close()
    mem.close()

