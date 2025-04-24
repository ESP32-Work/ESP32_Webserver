#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Testwifi";
const char* password = "x11y22z33";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#define MAX_CLIENTS 2
#define FRAME_INTERVAL 200  // Increased to 200ms (5 FPS)

unsigned long lastFrameTime = 0;

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    if(ws.count() <= MAX_CLIENTS){
      Serial.println("WebSocket client connected");
    } else {
      Serial.println("Too many clients. Rejecting connection.");
      client->close();
    }
  } else if(type == WS_EVT_DATA){
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= FRAME_INTERVAL) {
      ws.textAll((char*)data);
      lastFrameTime = currentTime;
      Serial.printf("Forwarded frame of size %u\n", len);
    }
  }
}

void setup(){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", R"(
      <!DOCTYPE html>
      <html>
      <head>
        <title>ESP32 Webcam Stream</title>
      </head>
      <body>
        <h1>ESP32 Webcam Stream</h1>
        <img id="stream" style="width:320px;height:240px;">
        <script>
          var ws = new WebSocket('ws://' + location.hostname + '/ws');
          ws.onmessage = function(msg) {
            document.getElementById('stream').src = 'data:image/jpeg;base64,' + msg.data;
          };
        </script>
      </body>
      </html>
    )");
  });

  server.begin();
}

void loop(){}