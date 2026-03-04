from flask import Flask, jsonify, request

app = Flask(__name__)

current_data = {
    "temp" : 25.0,
    "humidity" : 44.0,
    "pressure" : 1010.0,
    "gas_lvl" : 400
}

# ESP32 sends data via WI-FI:
@app.route('/api/update', methods=['POST'])
def update_data():
    global current_data
    data = request.get_json()

    if data:
        current_data.update(data)
        print(f"New data --- Temp: {current_data['temp']}°C --- Gas: {current_data['gas_lvl']}")
        return jsonify({"Confirmation " : " SUCCES" , "Message " : " Data saved!"}), 200
    return jsonify({"Confirmation " : " ERROR" , "Message " : " INVALID DATA!"}), 400

