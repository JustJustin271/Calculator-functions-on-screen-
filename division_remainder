#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Defines size of screen and library
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int countPin = 2;
const int switchPin = 3;
const int powerPin = 4;

//Stores variables
long count1 = 0;
long count2 = 0;
long quotient = 0;
int mode = 0;
bool state = 0;

void setup() {
  lcd.init();
  lcd.noBacklight();
  //Starts the Arduino


  pinMode(countPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(powerPin) == LOW) { //If preseed, it will turn on/off
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

    if (count2 != 0){ //If the not the illegal case, proceed
      quotient = count1 / count2;
    } 

    //Usual logic


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
//Logic for computation
    else if(mode == 2){
      lcd.setCursor(0,1);
      if (count2 == 0){
        lcd.print("NaN :(             "); //Error message if you even think about dividing by 0
      } else{
        lcd.print("= ");
        lcd.print(quotient); //Arduino will round down as it is an int
        lcd.print(" R: "); //Remainder
        lcd.print(count1 % count2); //Uses modulo for remainder
        lcd.print("              "); //S P A C E
      }

      if(digitalRead(switchPin) == LOW){ //Reset o' clock!
        count1 = 0;
        count2 = 0;
        mode = 0;
        lcd.clear();
        delay(200);
      }
    }


      //Display functions :)

      lcd.setCursor(0,0);
      lcd.print(count1);
      lcd.print(" / ");
      lcd.print(count2);
      lcd.print("        ");
      
  }
}

//February 16th, 2026
//Division_Remainder function done on the LCD screen :)
