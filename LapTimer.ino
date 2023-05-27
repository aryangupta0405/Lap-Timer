#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial mySerial(10,11);    // TX of LoRa, RX of LoRa

volatile unsigned int LapCounter=0;
int i=0;
byte IntPin=2;
int ResetPin=3;  //Red
int touchTime=1000;
unsigned long long prevmillis=0;
unsigned long long currmillis;
float tim;
int state=0;
void setup()
{
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  pinMode(IntPin,INPUT_PULLUP);
  pinMode(ResetPin,INPUT_PULLUP);
  Serial.begin(115200);
  mySerial.begin(9600);  
  attachInterrupt(digitalPinToInterrupt(IntPin),startCount,FALLING);
  attachInterrupt(digitalPinToInterrupt(ResetPin),Res,LOW);
}

void loop()
{
  LTimer();
  i =mySerial.read(); 
  if (i==5){
    startCount();
  }
}

void LTimer(){
  lcd.clear();
  if (state==1){
    currmillis=millis(); 
    lcd.setCursor(2,0);   
    lcd.print("Lap : ");
    lcd.print(LapCounter);    
    lcd.setCursor(2,1);
    lcd.print("Time : ");
    lcd.print(tim/1000);
  }

  else{
    prevmillis=0;
    tim=0;
    lcd.setCursor(2,0);
    lcd.print("START!!");
  }
  delay(150);
}

void startCount()
{
  if ((millis()-prevmillis)>=touchTime){
    if(state==1){
      tim=currmillis-prevmillis;
      prevmillis=currmillis;
      LapCounter++;
      }
    if (state==0){
      prevmillis=millis();
      state=1;
      }
    
  }
}

void Res(){
  state=0;  
  LapCounter=0;
  
}


