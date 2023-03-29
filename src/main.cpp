#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "Sinezio";
const char *password = "junior123%";

WiFiUDP udp;

IPAddress serverIP(192, 168, 0, 116); // replace with your server IP
unsigned int serverPort = 5005;       // replace with your server port

char mensage[] = "A"; // example string

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // send a message to the Python server
  udp.beginPacket(serverIP, serverPort);

  strcpy(mensage, "A");
  Serial.println("Sending: A");
  udp.write(reinterpret_cast<const uint8_t *>(mensage), strlen(mensage));
  udp.endPacket();

  udp.beginPacket(serverIP, serverPort);
  strcpy(mensage, "B");
  Serial.println("Sending: B");
  udp.write(reinterpret_cast<const uint8_t *>(mensage), strlen(mensage));
  udp.endPacket();

  delay(1000);
}
