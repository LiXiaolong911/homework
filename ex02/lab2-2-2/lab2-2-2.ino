const int ledPin = 2;

// 定义每个动作：{电平, 持续时间(ms)}
struct Action {
  bool level;        // HIGH 或 LOW
  unsigned long duration;
};

// SOS 序列（依次执行）
const Action actions[] = {
  {HIGH, 200}, {LOW, 200},   // S 第1脉冲
  {HIGH, 200}, {LOW, 200},   // S 第2脉冲
  {HIGH, 200}, {LOW, 200},   // S 第3脉冲
  {LOW, 500},               // 字母间隔（S→O）

  {HIGH, 600}, {LOW, 200},   // O 第1脉冲
  {HIGH, 600}, {LOW, 200},   // O 第2脉冲
  {HIGH, 600}, {LOW, 200},   // O 第3脉冲
  {LOW, 500},               // 字母间隔（O→S）

  {HIGH, 200}, {LOW, 200},   // S 第1脉冲
  {HIGH, 200}, {LOW, 200},   // S 第2脉冲
  {HIGH, 200}, {LOW, 200},   // S 第3脉冲
  {LOW, 2000}               // 单词间隔（SOS结束，等待2秒后重复）
};

const int actionCount = sizeof(actions) / sizeof(actions[0]);
int currentAction = 0;                // 当前执行的动作索引
unsigned long previousMillis = 0;     // 上次动作切换时间
bool actionCompleted = false;        // 辅助标志

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // 获取当前要执行的动作
  Action act = actions[currentAction];

  // 设置LED电平（只在切换时执行，避免重复写）
  static bool lastLevel = !act.level; // 初始与第一次不同，确保首次更新
  if (lastLevel != act.level) {
    digitalWrite(ledPin, act.level);
    lastLevel = act.level;
    // 可选打印电平变化（调试）
  }

  // 检查该动作是否已完成
  if (currentMillis - previousMillis >= act.duration) {
    previousMillis = currentMillis;       // 重置定时
    currentAction++;                      // 移动到下一个动作
    if (currentAction >= actionCount) {
      currentAction = 0;                  // 循环播放
    }
    // 注意：下个循环会立即切换到下一个动作并设置电平
  }
}