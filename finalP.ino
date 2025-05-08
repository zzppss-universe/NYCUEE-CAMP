#define VibrationPin 2
int ServoPins[] = {3,4,5,6};
#define MotorpinB 8
#define MotorpinA 9
#define ButtonUp 7
#define ButtonDown 10
#define ButtonLeft 11
#define ButtonRight 12
#define ButtonSel 13
int PhotoPins[] = {A0, A1, A2, A3}; //1、5、10、50
//微動開關
#define Switchpin A6
#define LEDpin A7

// 馬達控制變數
int motorSpeed = 0;  // 0-255
bool motorDirection = true; // true=正向, false=反向

void setup() {
  // 初始化馬達控制腳位
  pinMode(MotorpinA, OUTPUT);
  pinMode(MotorpinB, OUTPUT);
  
  // 初始化按鈕腳位
  pinMode(ButtonUp, INPUT_PULLUP);
  pinMode(ButtonDown, INPUT_PULLUP);
  pinMode(ButtonLeft, INPUT_PULLUP);
  pinMode(ButtonRight, INPUT_PULLUP);
  pinMode(ButtonSel, INPUT_PULLUP);
  
  // 初始化LED腳位
  pinMode(LEDpin, OUTPUT);
  
  // 初始化序列通訊
  Serial.begin(9600);
  Serial.println("馬達控制系統已啟動");
}

void loop() {
  // 檢查按鈕輸入
//  checkButtons();
  
  // 控制馬達
  controlMotor();
  
  // 讀取光敏電阻值
//  readPhotoResistors();
  
  // 檢查微動開關
//  checkLimitSwitch();
  
  delay(50); // 小延遲防止按鈕彈跳
}

void checkButtons() {
  // 加速按鈕
  if (digitalRead(ButtonUp) == LOW) {
    motorSpeed = min(motorSpeed + 10, 255);
    Serial.print("速度增加至: ");
    Serial.println(motorSpeed);
    delay(200); // 防彈跳
  }
  
  // 減速按鈕
  if (digitalRead(ButtonDown) == LOW) {
    motorSpeed = max(motorSpeed - 10, 0);
    Serial.print("速度減少至: ");
    Serial.println(motorSpeed);
    delay(200);
  }
  
  // 改變方向按鈕
  if (digitalRead(ButtonLeft) == LOW) {
    motorDirection = true;
    Serial.println("方向設定為: 正向");
    delay(200);
  }
  
  if (digitalRead(ButtonRight) == LOW) {
    motorDirection = false;
    Serial.println("方向設定為: 反向");
    delay(200);
  }
  
  // 選擇按鈕
  if (digitalRead(ButtonSel) == LOW) {
    motorSpeed = 0; // 停止馬達
    Serial.println("馬達停止");
    delay(200);
  }
}

void controlMotor() {
  motorSpeed = 0;
  motorDirection = 1;
  if (motorDirection) {
    // 正向轉動
    analogWrite(MotorpinA, motorSpeed);
    digitalWrite(MotorpinB, HIGH);
  } else {
    // 反向轉動
    analogWrite(MotorpinA, motorSpeed);
    digitalWrite(MotorpinB, LOW);
  }
}

void readPhotoResistors() {
  // 讀取所有光敏電阻值
  for (int i = 0; i < 4; i++) {
    int value = analogRead(PhotoPins[i]);
    Serial.print("光敏電阻 ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
  }
  delay(1000); // 每秒讀取一次
}

void checkLimitSwitch() {
  if (analogRead(Switchpin) > 500) { // 假設按下時值會大於500
    digitalWrite(LEDpin, HIGH); // 觸發時點亮LED
//    motorSpeed = 0; // 停止馬達
    Serial.println("微動開關觸發，馬達停止");
  } else {
    digitalWrite(LEDpin, LOW);
  }
}
