#include <Servo.h>
#include <Wire.h>
#include <U8g2lib.h>


// OLED 使用硬體 I2C（節省記憶體的 page buffer 模式）
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 基本腳位設定
#define vibrationPin A1
int servoPins[] = {3, 5, 6, 10};
Servo myServo[4];
bool servoSpeed = 1;
int servoAngle = 0;

#define motorPinB A0 //for digital output
#define motorPinA 11 //for analog output
int motorSpeed = 255;
bool motorDirect = 0 , motorAddSpeed = 1;

// 按鈕腳位
const int buttonPins[] = {4, 7, 8, 9, 12}; 
const int buttonCount = 5;

// 按鈕狀態變數
bool lastButtonStates[buttonCount] = {false, false, false, false, false};

// 光敏腳位 & 數據
const int photoPins[] = {A2, A3, A6, A7};
float threshold[4] = {0,0,0,0}; //自動門檻
const float hardThreshold = 0.4; //需要高平均 (1+hardThreshold) 倍才會觸發
int CoinData[4] = {0, 0, 0, 0};
bool CoinActive[4] = {0,0,0,0}; //硬幣是否落下

// 微動開關（尚未使用）
#define switchPin 2
#define ledPin 13

// 讀取光敏電阻，並設定平均值
void readPhoto(){
  Serial.println("Current :");
  for(int t=0;t<4;t++){
    CoinData[t] = analogRead(photoPins[t]);
    threshold[t] = 63*(threshold[t]/64.0) + ( CoinData[t] )/64.0;
    
    if(CoinData[t] > threshold[t]*hardThreshold)
      CoinActive[t] = 1;
    else
      CoinActive[t] = 0;
    Serial.print("  Coin[");
    Serial.print(t);
    Serial.print("] : threshold = ");
    Serial.print(threshold[t]);
    Serial.print(" CoinData = ");
    Serial.print(CoinData[t]);
    Serial.print(" CoinActive = ");
    Serial.println(CoinActive[t]);
  }
}

// 更新馬達狀態
void updateMotor(){
//  motorSpeed += motorAddSpeed - !motorAddSpeed;
//  if(motorSpeed==255){
//    motorAddSpeed = 0;
//  }
//  if(motorSpeed==0){
//    motorAddSpeed = 1;
//    motorDirect = !motorDirect;
//  }
  motorDirect = 0;
  digitalWrite(motorPinB, motorDirect);
  analogWrite(motorPinA, motorSpeed);
}

// 更新伺服馬達
void updateServo(){
  servoAngle += servoSpeed - !servoSpeed;
  if(servoAngle == 90 || servoAngle == 0)
    servoSpeed = !servoSpeed;
  for(int i=0;i<4;i++){
    myServo[i].write(servoAngle);
  }
}

// 顯示 OLED 畫面
void updateOLED() {
  const char* labels[] = {"1-dollar", "5-dollar", "10-dollar", "50-dollar"};
  char buffer[20];

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB14_tr); 

    for (int i = 0; i < 4; i++) {
      snprintf(buffer, sizeof(buffer), "%s: %d", labels[i], CoinData[i]);
      u8g2.drawStr(0, 15 + i * 15, buffer);
    }
  } while (u8g2.nextPage());
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.firstPage();
  do {
    u8g2.drawStr(0, 10, "System Initialized");
  } while (u8g2.nextPage());
  delay(1000);

  // 設定按鈕為輸入並啟用內建上拉電阻
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(motorPinA , OUTPUT);
  pinMode(motorPinB , OUTPUT);
  for(int i=0;i<4;i++){
    myServo[i].attach(servoPins[i]);
  }
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  for (int i = 0; i < buttonCount; i++) {
    bool currentState = !digitalRead(buttonPins[i]); // 按下為 LOW，取反
    if (currentState && !lastButtonStates[i]) {
      CoinData[i]++;
    }
    lastButtonStates[i] = currentState;
  }
  readPhoto();
  updateMotor();
  updateServo();
  updateOLED();
//  delay(25);
}
