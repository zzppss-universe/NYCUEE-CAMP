#include "Global_define.h"

// 讀取按鈕數值
void ReadButton(){
  for (int i = 0; i < buttonCount; i++) {
    bool currentState = !digitalRead(buttonPins[i]); // 按下為 LOW，取反
    if (currentState && !lastButtonStates[i]) {
      CoinData[i]++;
    }
    lastButtonStates[i] = currentState;
  }
}
