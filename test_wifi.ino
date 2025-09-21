
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Unsupported board: select ESP32 or ESP8266 in Tools > Board
#endif
#include <Firebase_ESP_Client.h>
// #include <DHT.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// Định nghĩa chân kết nối DHT22
#define DHT_PIN 4
#define DHT_TYPE DHT22

// Khởi tạo đối tượng DHT
DHT dht(DHT_PIN, DHT_TYPE);

// Thông tin WiFi
const char* ssid = "BKSTAR_T2_02";
const char* password = "stemstar";

// // Thông tin Firebase
// #define API_KEY "AIzaSyBZI7_eorZ8XjfLA7tEhnJZFnrtQPUVYuY"
// #define DATABASE_URL "https://fire-detect-44fc7-default-rtdb.asia-southeast1.firebasedatabase.app/"
// #define USER_EMAIL "minh.s061809@gmail.com"
// #define USER_PASSWORD "Minh0618"

// // Đối tượng Firebase
// FirebaseData fbdo;
// FirebaseAuth auth;
// FirebaseConfig config;

// // Biến thời gian
// unsigned long lastTime = 0;
// const unsigned long timerDelay = 5000;  // 5 giây

// // Biến lưu UID người dùng
// String uid;

void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println();
  Serial.println("Booting...");

  // Khởi tạo cảm biến DHT
  dht.begin();

  // Kết nối WiFi
  #if defined(ESP8266)
  WiFi.mode(WIFI_STA);
  #endif
  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Đã kết nối WiFi với IP: ");
  Serial.println(WiFi.localIP());

  // // Cấu hình Firebase
  // config.api_key = API_KEY;
  // config.database_url = DATABASE_URL;

  // // Đăng nhập Firebase
  // auth.user.email = USER_EMAIL;
  // auth.user.password = USER_PASSWORD;

  // // Gán callback function cho quá trình đăng nhập
  // config.token_status_callback = tokenStatusCallback;

  // // Khởi tạo Firebase
  // Firebase.begin(&config, &auth);
  // Firebase.reconnectWiFi(true);
}

void loop() {
  // Tạm thời để trống khi debug kết nối WiFi
}
