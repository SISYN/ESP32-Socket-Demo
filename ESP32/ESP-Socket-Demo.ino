#include <DHT.h>
#include <WiFi.h>
#include <NodeJoy.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>

int PHR_PIN = 0;
int DHT_PIN = 18;

int TRANSMIT_LAST = millis();
const int TRANSMIT_INTERVAL = 33; // ms

NodeJoy* SYS = new NodeJoy;
DHT DHT_INTERFACE(DHT_PIN, DHT22);
WebSocketsClient WebSocketClient;

StaticJsonBuffer<512> JSON_Buffer;
JsonObject& JSON_Root = JSON_Buffer.createObject();
JsonObject& JSON_Self = JSON_Root.createNestedObject("self");
JsonObject& JSON_Data = JSON_Root.createNestedObject("data");

void setup() {
  Serial.begin(115200);
  WaitForWiFi("[YOUR WIFI SSID]", "[YOUR WIFI PASSWORD]");
  JSON_Self["mac"] = SYS->MAC();
  WebSocketConnect();
}
void loop() {
  WebSocketClient.loop();
  Transmit();
}

void WaitForWiFi(const char ssid[], const char pkey[]) {
  WiFi.begin(ssid,pkey);
  while (WiFi.status() != WL_CONNECTED) { // Check for the connection
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
void WebSocketConnect() {
  Serial.println("Connecting to WebSocket server");
  WebSocketClient.begin("NODEJS SERVER IP", 8080); // Change to your NodeJS server port
  WebSocketClient.onEvent(WebSocketEvent);
  WebSocketClient.setReconnectInterval(5000); // retry every 5s if connection failed
  Serial.println("Successfully connected to WebSocket server");
}
void WebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] Server says: %s\n", payload);
      break;
  }
}
void Transmit() {
  if ( millis() - TRANSMIT_LAST >= TRANSMIT_INTERVAL ) {
    TRANSMIT_LAST = millis();
    String JSON;
    JSON_Self["ms"] = millis();
    JSON_Data["light"] = analogRead(PHR_PIN);
    JSON_Data["humidity"] = DHT_INTERFACE.readHumidity();
    JSON_Data["centigrade"] = DHT_INTERFACE.readTemperature();
    JSON_Data["farenheit"] = DHT_INTERFACE.readTemperature() * 9 / 5 + 32;

    JSON_Root.printTo(JSON);
    WebSocketClient.sendTXT(JSON);
    Serial.println(JSON);
  }
}
