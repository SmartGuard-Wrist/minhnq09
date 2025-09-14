#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

// ====== Thông tin WiFi ======
const char* ssid = "BKSTAR_T2_02";
const char* password = "stemstar";

// ====== ThingSpeak ======
WiFiClient client;
unsigned long myChannelNumber = 3074142;        // Thay bằng Channel ID của bạn
const char* myWriteAPIKey = "H2B0CH4COA1YTMJI";     // Thay bằng Write API Key

// ====== Cảm biến Pulse ======
int pulsePin = A0;  

// Biến tính BPM
volatile int beatCount = 0;
unsigned long lastBeatTime = 0;
unsigned long lastSendTime = 0;
float bpm = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  ThingSpeak.begin(client);
}

void loop() {
  int sensorValue = analogRead(pulsePin);

  // Ngưỡng phát hiện nhịp tim (cần chỉnh cho phù hợp cảm biến)
  if (sensorValue > 550 && (millis() - lastBeatTime) > 300) { 
    beatCount++;
    lastBeatTime = millis();
  }

  // Cứ mỗi 10 giây thì tính BPM và gửi lên Thingspeak
  if (millis() - lastSendTime > 15000) {
    bpm = (beatCount * 60.0) / 15.0;  // Số nhịp trong 10 giây * 6 = BPM
    Serial.print("BPM: ");
    Serial.println(bpm);

    int status = ThingSpeak.writeField(myChannelNumber, 1, bpm, myWriteAPIKey);
    if (status == 200) {
      Serial.println("Đã gửi BPM thành công!");
    } else {
      Serial.println("Lỗi khi gửi dữ liệu: " + String(status));
    }

    beatCount = 0;  // reset bộ đếm nhịp
    lastSendTime = millis();
  }
}