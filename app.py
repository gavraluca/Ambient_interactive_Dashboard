from flask import Flask, jsonify, request

app = Flask(__name__)

current_data = {
    "temp" : 25.0,
    "humidity" : 44.0,
    "pressure" : 1010.0,
    "quality_lvl" : 400
}

# ESP32 sends data via WI-FI:
@app.route('/api/update', methods=['POST'])
def update_data():
    global current_data
    data = request.get_json()

    if data:
        current_data.update(data)
        print(f"New data --- Temp: {current_data['temp']}°C --- Air Quality: {current_data['quality_lvl']}")
        return jsonify({"Confirmation " : " SUCCES" , "Message " : " Data saved!"}), 200
    return jsonify({"Confirmation " : " ERROR" , "Message " : " INVALID DATA!"}), 400

#WEB interface reads data
@app.route('/api/data', methods=['GET'])
def get_data():
    return jsonify(current_data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
