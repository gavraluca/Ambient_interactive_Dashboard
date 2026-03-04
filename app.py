from flask import Flask

app = Flask(__name__)

current_data = {
    "temp" : 25.0,
    "humidity" : 44.0,
    "pressure" : 1010.0,
    "gas-lvl" : 400
}

