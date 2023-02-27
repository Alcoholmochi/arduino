int count = 0;
int tilt = 2;
int brush_button = 3;
int state = 0;
int buttonstate;
int goal = 200;
int buz = 13;

byte grapeChar[] = {
  B01000,
  B00100,
  B01110,
  B10101,
  B10001,
  B10001,
  B01110,
  B00000
};

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  pinMode(tilt, INPUT);
  pinMode(brush_button,INPUT_PULLUP);
  pinMode(buz,OUTPUT);
  lcd.init();
  lcd.createChar(0, grapeChar);
}


void loop() {
  if(digitalRead(tilt)==LOW){
    count++;
    lcd.setCursor(3,1);
    lcd.print(count-20);
    lcd.setCursor(7,1);
    lcd.print("/");
    lcd.setCursor(8,1);
    lcd.print(goal);
    lcd.setCursor(13,1);
    lcd.write(0);
  }
  if(count<=20){
    lcd.clear();
  }
  if(count==20){
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("brush your teeth!");
   
  }
  if(count==goal+20){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Brush Finished");
    lcd.setCursor(3,1);
    lcd.print(count-20);
    tone(buz,440,125);
   
  }
  buttonstate=digitalRead(brush_button);
  if(buttonstate == HIGH){
    if (state==0){
      delay(10);
      state = 1;
    }
  }
  if (buttonstate == LOW){
    if (state == 1){
      
      if(count+20>=goal){
        Serial.println(count+20);
      }
      delay(10);
      state=0;
      count=0;
      lcd.noBacklight();
      lcd.clear();
    }
  }
  delay(10);
}
