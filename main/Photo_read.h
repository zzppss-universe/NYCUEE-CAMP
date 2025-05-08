#include "Global_define.h"

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
