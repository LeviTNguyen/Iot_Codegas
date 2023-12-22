#define BLYNK_TEMPLATE_ID "TMPL62LMoFRTz"
#define BLYNK_TEMPLATE_NAME "MQ2Sensor"
#define BLYNK_AUTH_TOKEN "XmyrMbRlyD1DfvvaFrtXrUh1dcaGu3mQ"
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>


const int gasSensorPin = A0;    // Chân analog cảm biến khí gas
const int buzzerPin = D5;       // GPIO 14 trên ESP8266
const int redLEDPin = D7;       // GPIO 13 trên ESP8266
const int greenLEDPin = D6;     // GPIO 12 trên ESP8266
char ssid[] = "DONG NAU COFFEE"; // Tên WiFi của bạn
char password[] = "xincamon";    // Mật khẩu WiFi của bạn

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  Serial.begin(115200);

  WiFi.begin("DONG NAU COFFEE", "xincamon"); // Kết nối với WiFi
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
}

void loop() {
  Blynk.run();
  int gasValue = analogRead(gasSensorPin);  // Đọc giá trị từ cảm biến khí gas
  Serial.print("Gas value: ");
  Serial.println(gasValue);  // In giá trị đọc được lên Serial Monitor
   Blynk.virtualWrite(V1, gasValue); // Gửi giá trị đọc từ cảm biến lên gauge trên Blynk

  // Kiểm tra giá trị cảm biến để xác định ngưỡng cảnh báo
  if (gasValue > 500) {
    // Nếu cảm biến phát hiện nồng độ khí gas vượt ngưỡng, bật buzzer và đèn LED đỏ
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW); // Tắt đèn LED xanh dương 
     Blynk.virtualWrite(V0, LOW  ); // Bật LED đỏ trên Blynk
    Blynk.virtualWrite(V2, HIGH); // Bật LED xanh trên Blynk
  } else {
    // Nếu không có khí gas vượt ngưỡng, tắt buzzer và đèn LED đỏ, bật đèn LED xanh dương
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
     Blynk.virtualWrite(V0, HIGH); // Tắt LED đỏ trên Blynk
    Blynk.virtualWrite(V2, LOW); // bât LED xanh trên Blynk
  }

  delay(1000);  // Delay giữa các lần đọc cảm biến
}
