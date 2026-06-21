// 定义LED引脚（ESP32板载LED通常接GPIO2）
const int ledPin = 2;

// 状态变量
unsigned long previousMillis = 0;    // 记录上次LED翻转的时间
const unsigned long interval = 1000; // 间隔1秒（1000毫秒）
bool ledState = LOW;                 // 当前LED状态

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);    // 初始状态为熄灭
}

void loop() {
  unsigned long currentMillis = millis(); // 获取当前时刻

  // 非阻塞定时判断：如果到达间隔时间
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   // 更新上次时间戳（相当于重置定时器）

    // 翻转LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // 根据新状态打印对应信息（只在翻转时打印一次）
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }

}