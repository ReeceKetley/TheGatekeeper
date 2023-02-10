#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Define the I2C pins for the ADAU1452
#define SDA 21
#define SCL 22
//

// Declare all the ADAU1452 address and registers
#define ADAU1452_ADDRESS 0x38
#define REGISTER_THRESHOLD_LOW 0x50
#define REGISTER_THRESHOLD_MID 0x51
#define REGISTER_THRESHOLD_HIGH 0x52
#define REGISTER_RATIO_LOW 0x53
#define REGISTER_RATIO_MID 0x54
#define REGISTER_RATIO_HIGH 0x55
#define REGISTER_ATTACK_LOW 0x56
#define REGISTER_ATTACK_MID 0x57
#define REGISTER_ATTACK_HIGH 0x58
#define REGISTER_RELEASE_LOW 0x59
#define REGISTER_RELEASE_MID 0x5A
#define REGISTER_RELEASE_HIGH 0x5B
//

// Will decleare things like OLED screens and rotary pot here
// TODO: Add OLED pin declartions
// TODO: add the data pins for the rotary knob
//

void writeToAdau1452(uint8_t registerAddress, uint16_t data) {
  Wire.begin(SDA, SCL);
  Wire.beginTransmission(ADAU1452_ADDRESS);
  Wire.write(registerAddress);
  Wire.write(data & 0xFF);
  Wire.write(data >> 8);
  Wire.endTransmission();
}

AsyncWebServer server(80);

void handleThresholdLow(AsyncWebServerRequest *request) {
  uint16_t threshold = request->arg("threshold").toInt();
  writeToAdau1452(REGISTER_THRESHOLD_LOW, threshold);
  request->send(200, "text/plain", "Threshold for low frequency band set to " + String(threshold));
}

void handleRatioLow(AsyncWebServerRequest *request) {
  uint16_t ratio = request->arg("ratio").toInt();
  writeToAdau1452(REGISTER_RATIO_LOW, ratio);
  request->send(200, "text/plain", "Ratio for low frequency band set to " + String(ratio));
}

void handleAttackLow(AsyncWebServerRequest *request) {
  uint16_t attack = request->arg("attack").toInt();
  writeToAdau1452(REGISTER_ATTACK_LOW, attack);
  request->send(200, "text/plain", "Attack for low frequency band set to " + String(attack));
}

void handleReleaseLow(AsyncWebServerRequest *request) {
  uint16_t release = request->arg("release").toInt();
  writeToAdau1452(REGISTER_RELEASE_LOW, release);
  request->send(200, "text/plain", "Release for low frequency band set to " + String(release));
}

void handleThresholdMid(AsyncWebServerRequest *request) {
  uint16_t threshold = request->arg("threshold").toInt();
  writeToAdau1452(REGISTER_THRESHOLD_MID, threshold);
  request->send(200, "text/plain", "Threshold for mid frequency band set to " + String(threshold));
}

void handleRatioMid(AsyncWebServerRequest *request) {
  uint16_t ratio = request->arg("ratio").toInt();
  writeToAdau1452(REGISTER_RATIO_MID, ratio);
  request->send(200, "text/plain", "Ratio for mid frequency band set to " + String(ratio));
}

void handleAttackMid(AsyncWebServerRequest *request) {
  uint16_t attack = request->arg("attack").toInt();
  writeToAdau1452(REGISTER_ATTACK_MID, attack);
  request->send(200, "text/plain", "Attack for mid frequency band set to " + String(attack));
}

void handleReleaseMid(AsyncWebServerRequest *request) {
  uint16_t release = request->arg("release").toInt();
  writeToAdau1452(REGISTER_RELEASE_MID, release);
  request->send(200, "text/plain", "Release for mid frequency band set to " + String(release));
}

void handleThresholdHigh(AsyncWebServerRequest *request) {
  uint16_t threshold = request->arg("threshold").toInt();
  writeToAdau1452(REGISTER_THRESHOLD_HIGH, threshold);
  request->send(200, "text/plain", "Threshold for high frequency band set to " + String(threshold));
}

void handleRatioHigh(AsyncWebServerRequest *request) {
  uint16_t ratio = request->arg("ratio").toInt();
  writeToAdau1452(REGISTER_RATIO_HIGH, ratio);
  request->send(200, "text/plain", "Ratio for high frequency band set to " + String(ratio));
}

void handleAttackHigh(AsyncWebServerRequest *request) {
  uint16_t attack = request->arg("attack").toInt();
  writeToAdau1452(REGISTER_ATTACK_HIGH, attack);
  request->send(200, "text/plain", "Attack for high frequency band set to " + String(attack));
}

void handleReleaseHigh(AsyncWebServerRequest *request) {
  uint16_t release = request->arg("release").toInt();
  writeToAdau1452(REGISTER_RELEASE_HIGH, release);
  request->send(200, "text/plain", "Release for high frequency band set to " + String(release));
}

void setup() {
  Wire.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32 Multiband Compressor");

  server.on("/threshold_low", HTTP_GET, handleThresholdLow);
  server.on("/ratio_low", HTTP_GET, handleRatioLow);
  server.on("/attack_low", HTTP_GET, handleAttackLow);
  server.on("/release_low", HTTP_GET, handleReleaseLow);
  server.on("/threshold_mid", HTTP_GET, handleThresholdMid);
  server.on("/ratio_mid", HTTP_GET,handleRatioMid);
  server.on("/attack_mid", HTTP_GET, handleAttackMid);
  server.on("/release_mid", HTTP_GET, handleReleaseMid);
  server.on("/threshold_high", HTTP_GET, handleThresholdHigh);
  server.on("/ratio_high", HTTP_GET, handleRatioHigh);
  server.on("/attack_high", HTTP_GET, handleAttackHigh);
  server.on("/release_high", HTTP_GET, handleReleaseHigh);

  server.begin();
}

void loop() {
  server.handleClient();
}
