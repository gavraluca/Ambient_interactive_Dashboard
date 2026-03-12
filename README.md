Project Overview:

I built a smart device with a friendly interface that measures temperature, humidity, and lastly, air quality in real-time.
The data is displayed on a small OLED screen and sent over Wi-Fi to a Python server that runs on my PC.

Technologies I used:

Hardware: ESP32 board, BME280 sensor (for temperature / humidity), MQ-135 sensor (for air quality), OLED display.
Programming: C++ (Arduino IDE) for the firmware, Python (Flask) for the server backend.

How does it work: I used JSON to format the data and HTTP POST requests to send it over Wi-Fi.
