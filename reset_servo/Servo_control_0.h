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
  for(int i=0;i<4;i++){
    myServo[i].write(0);
  }
}
