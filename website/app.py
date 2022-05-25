from flask import Flask
from flask import *

app = Flask(__name__)

@app.route("/")
def index():
    return(render_template('home.html'))