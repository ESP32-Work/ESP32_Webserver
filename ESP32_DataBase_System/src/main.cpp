#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "";
const char *password = "";

const char *servername = "";
String apiKeyValue = "";

String sensorName = "Touch";
String sensorLocation = "HomeOffice";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(servername);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key= " + apiKeyValue + "&sensor= " + sensorName + "&location= " + sensorLocation + "&value1= " + "value1" + "&value2= " + "value2" + "&value3= " + "value3";
    Serial.println("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      // String response = http.getString();
      Serial.println("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(30000);
}
 
