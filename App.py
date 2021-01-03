from flask import *
from threading import Thread
app = Flask(__name__)


@app.route("/")
def home():
    return render_template("main.html")


def webApp():
    app.run(host='localhost', port='5000', debug=False)

def startWebApp():
    Thread(target=webApp).start()