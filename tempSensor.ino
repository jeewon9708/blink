/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com  
*********/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;  

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
String apiKey="D88BHZDMZEHX4D38";
const char *ssid="iPhone";
const char *pw="1234567890";
const char* server="api.thingspeak.com";
WiFiClient client;
 
void setup() {
  // Start the Serial Monitor
    Serial.begin(115200);
    delay(10);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, pw);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("");
    Serial.print("WiFi connected");
  
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);

  char buf[16];
  String strTemp=dtostrf(temperatureC,4,1,buf);

  if(!client.connect(server,80)){
    Serial.print("connection fail!!");
    }
  else{
    // GET 방식으로 보내기 위한 String, Data 설정
    String getStr="GET /update?api_key=";
    getStr+=apiKey;
    getStr +="&field1=";
    getStr += strTemp;
    getStr += "\r\n\r\n";
  
    client.print(getStr);


     if(client.connected()){
      Serial.print("fully connected!");
     }

    Serial.println(strTemp);            
    Serial.println("%. Send to Thingspeak.");
  }

   client.stop();
    Serial.println("Waiting...");
    delay(16000);
  
 
}
