#include "Global_define.h"
#include <Servo.h>

// 宣告伺服馬達
Servo myServo[4];

// 伺服馬達初始設定
void setupServo(){
  for(int i=0;i<4;i++){
    myServo[i].attach(servoPins[i]);
  }
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
