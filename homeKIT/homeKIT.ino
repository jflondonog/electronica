#include <ESP8266WiFi.h>
#include "Fast.h"


const char* ssid = "Airport";
const char* password = "Allyouneedislove";

WiFiServer server(80);
Fast app();

byte r, g, b = 0;
String s = "";
long color = 0xFFFFFF;
String hexColor = "0xFFFFFF";
int val = 0;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    setColor();
    return;
  }

  // Wait until the client sends some data
  // Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  // Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("/rgb/off") != -1) {
    val = 0;
    s = app.res("");
  } else if (req.indexOf("/rgb/on") != -1) {
    val = 1;
    s = app.res("");
  } else if (req.indexOf("/rgb/status") != -1) {
    s = app.res("");
    s += val ?  "1" : "0";
  } else if (req.indexOf("/rgb/brightness") != -1) {
    s = app.res((val) ?  String(map((0.2126 * r + 0.7152 * g + 0.0722 * b), 0 , 255 , 0 , 100)) : "0");
  } else if (req.indexOf("/rgb/colorset") != -1) {
    s = app.res();
    if (req.indexOf("NANNAN") != -1) {
      hexColor = "0xFFFFFF";
    } else {
      hexColor = req.substring(18, 24);
    }
  } else if (req.indexOf("/rgb/set") != -1) {
    s = app.res(hexColor);
  } else {
    client.stop();
    return;
  }
  client.flush();
  client.print(s);
  s = "";
  delay(1);
}



void setColor(void) {
  color = (long) strtol( &hexColor[0], NULL, 16);
  if (val) {
    r = color >> 16;
    g = color >> 8 & 0xFF;
    b = color & 0xFF;
  } else {
    r = g = b = 0;
  }
}



