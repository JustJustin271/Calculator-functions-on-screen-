#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
//Defines screen and library


//Defines pins
const int countPin = 2;
const int switchPin = 3;
const int powerPin = 4;


//Variables
long count1 = 0;
long count2 = 0;
float quotient = 0; //Now a coke float :)
int mode = 0;
bool state = 0;

void setup() {
  lcd.init();
  lcd.noBacklight();
  //Tells the Arduino to lock in
  
  pinMode(countPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(powerPin) == LOW) { //Toggles on and off
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

    if (count2 != 0){
      quotient = (float)count1 / count2; //Dividing by 0...in 2026? Eeeeewwwww
    } 


    //Button logic
    if(mode == 0){
      delay(50);
      lcd.setCursor(0,1);
      lcd.print("Set Number 1    ");
      
      if(digitalRead(countPin) == LOW){
        count1++; 
        delay(75);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 1; 
        delay(300);
      }
    }

    //Button logic 2
    else if(mode == 1){
      delay(50);
      lcd.setCursor(0,1);
      lcd.print("Set Number 2    ");
      
      if(digitalRead(countPin) == LOW){
        count2++; 
        delay(75);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 2; 
        delay(300);
      }

      
    }
    //Display result logic
    else if(mode == 2){
      lcd.setCursor(0,1);
      if (count2 == 0){
        lcd.print("NaN D:         ");
      } else{
        lcd.print("= ");
        lcd.print(quotient, 4); //Rounds to 4 decimal places
        lcd.print("              ");
      }

      //Resets the calculator
      if(digitalRead(switchPin) == LOW){
        count1 = 0;
        count2 = 0;
        mode = 0;
        lcd.clear();
        delay(200);
      }
    }



    //Display functions
      lcd.setCursor(0,0);
      lcd.print(count1);
      lcd.print(" / ");
      lcd.print(count2);
      lcd.print("        ");
      
  }
}

//February 16th, 2026
//Function for 4 decimal places in divsion
