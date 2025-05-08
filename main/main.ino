#include "OLED_control.h"
#include "Servo_control.h"
#include "Button_read.h"
#include "Photo_read.h"
#include "Motor_control.h" 

void setup() {
  Serial.begin(9600);
  setupOLED();
  delay(1000);
  setupServo();
  
  // 設定按鈕為輸入並啟用內建上拉電阻
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(motorPinA , OUTPUT);
  pinMode(motorPinB , OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);

  ReadButton();
  ReadPhoto();
  updateMotor();
  updateServo();
  updateOLED();
//  delay(25);
}
