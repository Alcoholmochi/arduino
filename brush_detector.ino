// 아두이노 코드 

int count = 0;  //brush count(score)
int tilt = 2;  //tilt sensor pin num
int brush_button = 3;  //brush complete button pin num
int state = 0;  //var for switch falling edge
int buttonstate;  // var for switch falling edge
int goal = 1000; //goal of brush score

byte grapeChar[] = {  //grape icon 5*8 i2c display binary code
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
#include <LiquidCrystal_I2C.h>  //library for lcd display

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);  //serial begin
  pinMode(tilt, INPUT);  
  pinMode(brush_button,INPUT_PULLUP);
  lcd.init();   //initialize lcd
  lcd.createChar(0, grapeChar);  //make icon grape
}


void loop() {
  if(digitalRead(tilt)==LOW){  //when tilt
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
    lcd.clear();  //no lcd indicate score under 20
  }
  if(count==20){  //when count 20, score and lcd are start
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("brush your teeth!");
  }
  if(count==goal+20){  //when brush finish
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Brush Finished");
    lcd.setCursor(3,1);
    lcd.print(count-20);
    
  }
  buttonstate=digitalRead(brush_button); //brush complete button
  if(buttonstate == HIGH){
    if (state==0){
      delay(10);  //delay for debouncing
      state = 1;
    }
  }
  if (buttonstate == LOW){
    if (state == 1){
      
      if(count+20>=goal){
        Serial.println(count+20);  //send count value to serial
      }
      delay(10);
      state=0;
      count=0;
      lcd.noBacklight();
      lcd.clear();   //disable lcd
    }
  }
  delay(10);
}
//02:14
//comment at 06:44
