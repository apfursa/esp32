#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <ESP32SSDP.h>

WebServer server(80);
WiFiManager wifiManager;
int a=0;
const char *nameAP = "Sensor1";

void setup()
{
  pinMode(2, OUTPUT); // Изменил пин модели на ESP32
  Serial.begin(115200);
  wifiManager.setConfigPortalTimeout(120);
  wifiManager.autoConnect(nameAP);
  HTTP_init();
  SSDP_init();
}

void loop()
{
  server.handleClient();
  delay(5000);
  a++;
}

void HTTP_init(void)
{
  server.on("/index.html", HTTP_GET, []() {
    server.send(200, "text/plain", "Test "+String(a));
  });
  server.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(server.client());
  });
  server.begin();
}

void SSDP_init(void)
{
  SSDP.begin();
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("WiFiManager + SSDP");
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("index.html");
  SSDP.setModelName("WiFiManager + SSDP");
  SSDP.setModelNumber("000000000001"); 
  SSDP.setModelURL("http://esp8266-arduinoide.ru/wifimanager/");
  SSDP.setManufacturer("Tretyakov Sergey");
  SSDP.setManufacturerURL("http://www.esp8266-arduinoide.ru");
}
