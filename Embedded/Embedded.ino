#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SEGERRR";
const char* password = "JusBawang7890";
const char* mqtt_server = "192.168.43.131";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0; 
long lastRead = 0;
String msg, msgtopic; 

char CB1[]="0"; 
char CB2[] ="1000";

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic ");
  Serial.print(topic);
  Serial.print(": ");
  msgtopic = String((char*)topic);
  char msgchar[length];
  msg = "";
  for (int i = 0; i < length; i++) { 
    msg += (char)payload[i];
    msgchar[i] = (char)payload[i];
  }
  Serial.println(msg);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("topic1");
      client.subscribe("topic2"); 
      } 
      else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 3000);
  client.setCallback(callback);
 }

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  
  long now = millis();  
  if (now - lastMsg > 1000) {
    lastMsg = now;
    client.publish("topic3", "3"); 
    client.publish("topic4", "4"); 
    }
}    
