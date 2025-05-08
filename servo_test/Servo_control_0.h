#include "Global_define.h"
#include <Servo.h>

// 宣告伺服馬達
Servo myServo[4];

// 計算何時開始轉
bool button_Triggered = 0;

// 伺服馬達初始設定
void setupServo(){
  servoSpeed = 1;
  for(int i=0;i<4;i++){
    myServo[i].attach(servoPins[i]);
    servoAngle[i] = 120;
  }
}

// 計算伺服馬達角度（可變更）
void calculateServo(){
  if(button_Triggered == 1){
    for(int i=0;i<4;i++)
      servoAngle[i] += 2 * servoSpeed;
    if(servoAngle[0] == 180 || servoAngle[0] == 120) //從60轉到0再轉回來，重複
      servoSpeed = -servoSpeed;
    Serial.println(servoAngle[0]);
  }
}

// 計算何時開始轉
void ServoTrigger(){
  for(int i=0;i<4;i++){
    if(button_currentValue[i] == 1){
      button_Triggered = 1;
    }
  }
}

// 更新伺服馬達
void updateServo(){
  ServoTrigger();
  calculateServo();
  for(int i=0;i<4;i++){
    myServo[i].write(servoAngle[i]);
  }
}
