/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;  

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

const char* streamId   = "....................";
const char* privateKey = "....................";
const char* ssid = "iPhone";
const char* host="www.kma.go.kr";
const char* password = "chae9708";
const char* server="api.thingspeak.com";
String apiKey="D88BHZDMZEHX4D38";
int Pin=4;

void SendInformationToThingspeak(String kmaTemp, String sensorTemp){
    WiFiClient client2;

    
    if(!client2.connect(server,80)){
    Serial.print("connection fail!!");
    }
  else{
    // GET 방식으로 보내기 위한 String, Data 설정
    String getStr="GET /update?api_key=";
    getStr+=apiKey;
    getStr +="&field1=";
    getStr += sensorTemp;
    getStr +="&field2=";
    getStr += kmaTemp;
    getStr += "\r\n\r\n";
  
    client2.print(getStr);
     
  }
  client2.stop();
  Serial.println("Waiting...");
  delay(16000);
  


  
}

void setup()
{
    Serial.begin(115200);
    //소프트웨어 시리얼 시작
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

int value = 0;

void loop()
{
    delay(5000);
    ++value;
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);

    char buf[16];
    String strTemp=dtostrf(temperatureC,4,1,buf);
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/wid/queryDFSRSS.jsp?zone=4113554500";

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\n');
        if(line.indexOf("<temp>")>-1){
          //Serial.print(line);
          String stringSub=line.substring(9,13);
          SendInformationToThingspeak(stringSub,strTemp); 
       }
       
    }

    Serial.println();
    Serial.println("closing connection");
}
