#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* SSID = "DIGI_6e3520";
const char* PASSWORD = "aa2191ca";
const char* serverUrl = "http://192.168.1.6:5000/api/update";


// screen settings
#define SCREEN_W 128
#define SCREEN_H 64
#define SDA_I2C 18
#define SCL_I2C 19
#define MQ135_PIN 34 //calitatea aerului

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
Adafruit_BME280 bme;

void setup() {
  // serial speed for laptop
  Serial.begin(115200);
  
  // start i2c pins
  Wire.begin(SDA_I2C, SCL_I2C);
  
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("/n Wi-Fi CONNECTED!");


  //reset and screen test
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("could not find oled at 0x3C");
  } else {
    
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("RESET OK"); 
    display.display(); 
    delay(3000);       
    
    
    display.clearDisplay(); 
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println("Welcome,");
    display.setTextSize(2);
    display.setCursor(0, 35);
    display.println("LUCA!");
    display.display(); 
    delay(3000);       
  }

  //searching for BME280 sensor
  Serial.println("Searching for BME280 sensor...");
  if (!bme.begin(0x76, &Wire)) {
    if (!bme.begin(0x77, &Wire)) {
      Serial.println("ERROR: BME sensor not found!");
  
      display.setTextSize(1);
      display.setCursor(10, 45);
      display.println("BME: NOT FOUND");
      display.display();
    }
  } else {
    Serial.println("BME sensor OK!");
  }
}

void loop() {
  //   read data from bme
  float temp = bme.readTemperature();
  float humid = bme.readHumidity();
  int air = analogRead(MQ135_PIN);

  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient HTTP;
    HTTP.begin(serverUrl);
    HTTP.addHeader("Content-Type" , "application/json");
    StaticJsonDocument<200> DOC;
    DOC["temp"] = temp;
    DOC["humidity"] = humid;
    DOC["quality_lvl"] = air;

    String JSON_STR;
    serializeJson(DOC, JSON_STR);

    int httpResponseCode = HTTP.POST(JSON_STR);
    Serial.print("FLASK Response: ");
    Serial.println(httpResponseCode);
    HTTP.end();

  }

  //display on screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  
  if (isnan(temp)) {
    display.println("BME Error");
  } else {
    display.print(temp);
    display.print(" C ");
  }
  
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(humid);
  display.print(" % ");

  display.display();
  delay(10000);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Air Quality: ");
  display.print(air);

  display.setCursor(0,30);
  if(air < 1000) display.print("Quality: GOOD :) ");
  else if(air < 2000) display.print("Quality: MODERATE :| ");
  else display.print("Quality: BAD :( ");

  display.display();
  delay(10000);

  Serial.print("Air Quality Value: ");
  Serial.println(air);
  
  // still trying...
  static int count = 0;
  Serial.print("still trying... ");
  Serial.println(count++);
  
  delay(2000);
}



