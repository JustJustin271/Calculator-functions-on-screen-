#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

//Defines pins
const int countPin = 2;
const int switchPin = 3;
const int powerPin = 4;

const int addPin = 12;
const int subPin = 11;
const int multPin = 10;
const int divPin = 9;

//Defines variables
long count1 = 0;
long count2 = 0;
float answer = 0;
int mode = 0;
bool state = 0;

int function = 0;
String functionName = " ? ";

void setup() {
  lcd.init();
  lcd.noBacklight();

  pinMode(countPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
  
  pinMode(addPin, INPUT_PULLUP);
  pinMode(subPin, INPUT_PULLUP);
  pinMode(multPin, INPUT_PULLUP);
  pinMode(divPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(powerPin) == LOW) {
    state = !state;
    lcd.clear();
    
    if(state) { 
      lcd.init(); 
      lcd.backlight(); 
    } 
    else { 
      lcd.noBacklight(); 
    }
    delay(400);
  }

  if (state == true){
      // Removed the constant 100ms math delays to keep the screen smooth
      
      if(function == 0){ //Uknown operator
        functionName = " ? ";
      }
      
      if(function == 1) { //Additon function
        answer = count1 + count2;
        functionName = " + ";
      }
      
      if(function == 2) { //Subtraction function
        answer = count1 - count2;
        functionName = " - ";
      }
      
      if(function == 3) { //Multiplication function
        answer = count1 * count2;
        functionName = " * ";
      }
    
      if(function == 4) { //Division function
          functionName = " / ";
          if (count2 != 0){ //Decimal points
                answer = (float)count1 / count2;
          } else { //Else, do "?"
              answer = 0;
          }
      }
    
    if(mode == 0){
      lcd.setCursor(0,1); //Makes it written on the bottm row
      lcd.print(F("Set Number 1    ")); // F() macro keeps text in Flash memory
      
      if(digitalRead(countPin) == LOW){
        count1++; 
        delay(150); //Delay to prevent Arduino from exploding ;)
      }
      if(digitalRead(switchPin) == LOW){
        mode = 3; 
        delay(301);
      }
    }
    
    else if(mode == 3) {
        lcd.setCursor(0,1);
        lcd.print(F("Choose function "));

        //Function operations
        if(digitalRead(addPin) == LOW) {
            function = 1;
            delay(200);
            mode = 1;
        }
        
        if(digitalRead(subPin) == LOW) {
            function = 2;
            delay(200);
            mode = 1;
        }
        
        if(digitalRead(multPin) == LOW) {
            function = 3;
            delay(200);
            mode = 1;
        }
        
        if(digitalRead(divPin) == LOW) {
            function = 4;
            delay(200);
            mode = 1;
        }
    }
    
    else if(mode == 1){
      lcd.setCursor(0,1);
      lcd.print(F("Set Number 2    "));
      
      if(digitalRead(countPin) == LOW){
        count2++; 
        delay(150);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 2; 
        delay(301);
      }
    }
    
    //Displays the result of the function :D
    else if(mode == 2){
      lcd.setCursor(0,1);
      if ((function == 4)&&(count2 == 0)){ //If dividing by 0, conclude with error message
        lcd.print(F("NaN D:         "));
      } else {
        lcd.print(F("= "));
        lcd.print(answer, 4);
        lcd.print(F("        "));
      }

      //Clears it when pressed
      if(digitalRead(switchPin) == LOW){
        count1 = 0;
        count2 = 0;
        function = 0;
        functionName = " ? ";
        mode = 0;
        lcd.clear();
        delay(500);
      }
    }

    //Basics of the screen, constant update
    lcd.setCursor(0,0);
    lcd.print(count1);
    lcd.print(functionName);
    lcd.print(count2);
    lcd.print(F("        "));

    // Simple session timer in the bottom right corner (Seconds since power on)
    lcd.setCursor(12, 1);
    lcd.print(millis() / 1000);
    lcd.print(F("s"));

    delay(50); // Small loop delay to keep I2C stable
  }
}

//For RAM control
//Feb 16, 2026
//Main code by Justin Cheung, AI altered for RAM if needed, I don't trust the delays tbh
