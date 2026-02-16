#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int countPin = 2;
const int switchPin = 3;
const int powerPin = 4;

long count1 = 0;
long count2 = 0;
long sum = 0;
int mode = 0;
bool state = 0;

void setup() {
  lcd.init();
  lcd.noBacklight();

  pinMode(countPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(powerPin) == LOW) {
    state = !state;
    lcd.clear();
    
    if(state) {
      lcd.backlight();
    } else {
      lcd.noBacklight();
    }
    
    delay(500); // Debounce
  }

  if (state == true){

    sum = count1 + count2;
    
    if(mode == 0){

      delay(20);
      lcd.setCursor(0,1);
      lcd.print("Set Number 1    ");
      
      if(digitalRead(countPin) == LOW){
        count1++;
        delay(50);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 1;
        delay(50);
      }
    }
    else if(mode == 1){

      delay(20);
      lcd.setCursor(0,1);
      lcd.print("Set Number 2    ");
      
      if(digitalRead(countPin) == LOW){
        count2++;
        delay(50);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 2;
        delay(200);
      }

      
    }
    else if(mode == 2){
      lcd.setCursor(0,1);
      lcd.print("= ");
      lcd.print(sum);
      lcd.print("              ");

      if(digitalRead(switchPin) == LOW){
        count1 = 0;
        count2 = 0;
        mode = 0;
        lcd.clear();
        delay(200);
      }
    }

      lcd.setCursor(0,0);
      lcd.print(count1);
      lcd.print(" + ");
      lcd.print(count2);
      lcd.print("        ");
      
  }
}

//February 16th, 2026
//Addition function on LCD screen
