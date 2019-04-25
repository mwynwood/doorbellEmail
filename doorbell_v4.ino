// When the doorbell LED lights up, hit a website.

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String lastUpdate = "11 July, 2018";

// WiFi Details
const char* ssid = "XXX";
const char* password = "XXX";

// The URL to hit when the doorbell is pressed
String urlDoorbell = "http://example.com/doorbell.php?id=FRONT-DOOR";

// This is the pin the doorbell LED is connected to
int pinDoorbellLed = D3;

// A reset function, to reboot the device
void(* resetFunc) (void) = 0; //declare reset function at address 0

void setup () {
  // Set up IO
  pinMode(pinDoorbellLed, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on

  // Connect to WiFi
  Serial.begin(115200);

  Serial.println("DOORBELL");
  Serial.println("LAST UPDATED: " + lastUpdate + "\n");

  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off
  Serial.println("");
  Serial.println("Waiting for doorbell...");
}

void loop() {

  // If for some reason we're not on the WiFi, reboot!
  if (WiFi.status() != WL_CONNECTED) {
    resetFunc(); //call reset
  }

  // If the doorbell is pressed, its LED turns on, and triggers this:
  if (digitalRead(pinDoorbellLed) == 1) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on
    Serial.println("DING DONG!");

    HTTPClient http;
    http.begin(urlDoorbell);
    http.GET();
    Serial.println("Notification sent to: " + urlDoorbell);
    http.end();

    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off
    Serial.println("Waiting for 15 seconds...");
    delay(15000); // This is to allow the doorbell chime to sound, and to also debounce the button!
    Serial.println("");
    Serial.println("Waiting for doorbell...");
  }

}
