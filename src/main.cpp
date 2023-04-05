#include <WiFi.h>
#include <WiFiUdp.h>

#define XPORT 32
#define YPORT 34

const char *ssid = "Sinezio";
const char *password = "junior123%";

WiFiUDP udp;

IPAddress serverIP(192, 168, 0, 116); // replace with your server IP
unsigned int serverPort = 5005;       // replace with your server port

char mensage[3];
const char *ID = "2";

// Define the deadzone ranged
const int JOYSTICK_DEADZONE = 50;

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

  // Set pins for joystick axes to input
  pinMode(XPORT, INPUT);
  pinMode(YPORT, INPUT);
}

void loop()
{
  // send a message to the Python server
  udp.beginPacket(serverIP, serverPort);

  int xVal = analogRead(XPORT); // read X port
  int yVal = analogRead(YPORT); // read Y port

  // map the joystick values from 0-4095 to -100 to 100
  int xMapped = map(xVal, 0, 4095, -100, 100);
  int yMapped = map(yVal, 0, 4095, -100, 100);

  std::string yCode = "0";
  std::string xCode = "0";

  // Apply deadzone to joystick values

  if (xMapped >= JOYSTICK_DEADZONE)
  {
    xCode = "L";
  }
  else if (xMapped <= -JOYSTICK_DEADZONE)
  {
    xCode = "R";
  }

  if (yMapped >= JOYSTICK_DEADZONE)
  {
    yCode = "D";
  }
  else if (yMapped <= -JOYSTICK_DEADZONE)
  {
    yCode = "U";
  }

  sprintf(mensage, "%s-%s,%s", ID, yCode.c_str(), xCode.c_str());

  Serial.println(mensage);
  udp.write(reinterpret_cast<const uint8_t *>(mensage), strlen(mensage));
  udp.endPacket();

  delay(10);
}
