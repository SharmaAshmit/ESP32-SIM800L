#include <HardwareSerial.h>

#define MODEM_RX 26
#define MODEM_TX 27
HardwareSerial sim800(1);

String apn = "simgprs.com";  
String firebaseHost = "___";
String firebaseSecret = "___";
String path = "/sensorData.json?auth=" + firebaseSecret;
String jsonData = "{\"temperature\":28.5,\"humidity\":60}";

void sendAT(String command, const char* expectedResponse = "OK", int timeout = 5000) {
  sim800.println(command);
  unsigned long startTime = millis();  
  String response;

  while (millis() - startTime < timeout) {
    while (sim800.available()) {
      char c = sim800.read();
      response += c;
    }

    if (response.indexOf(expectedResponse) != -1) {
      Serial.println(response);
      return;
    }
  }

  Serial.println("Waiting for next command to execute");
  Serial.println(response);
}

void setup() {
  Serial.begin(115200);
  sim800.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  Serial.println("Initializing SIM800L...");

  sendAT("AT");
  sendAT("ATE0"); 
  sendAT("AT+CSQ"); 
  sendAT("AT+CPIN?");
  sendAT("AT+CREG?");

  Serial.println("Setting up GPRS...");
  sendAT("AT+CSTT=\"" + apn + "\"");
  sendAT("AT+CIICR");
  sendAT("AT+CIFSR", ".", 10000);  // Show IP address

  Serial.println("Initializing HTTP...");
  sendAT("AT+HTTPINIT");
  sendAT("AT+HTTPPARA=\"CID\",1");
  sendAT("AT+HTTPPARA=\"URL\",\"http://" + firebaseHost + path + "\"");
  sendAT("AT+HTTPPARA=\"CONTENT\",\"application/json\"");

  Serial.println("Preparing to send JSON data...");
  sendAT("AT+HTTPDATA=" + String(jsonData.length()) + ",10000", "DOWNLOAD", 10000);
  delay(100);  // Slight delay before sending data
  sim800.print(jsonData);  // Send JSON data
  delay(2000); // Allow module to buffer data

  Serial.println("Performing HTTP POST...");
  sendAT("AT+HTTPACTION=1", "+HTTPACTION:", 10000);

  // HTTPREAD to view response
  Serial.println("Reading HTTP Response...");
  sendAT("AT+HTTPREAD", "OK", 10000);

  sendAT("AT+HTTPTERM");
}

void loop() {
  // You can repeat this process periodically if needed
}
