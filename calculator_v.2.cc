#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

//Pins
const int countPin1 = 5;
const int countPin10 = 4;
const int countPin100 = 3;

const int switchPin = 2;


const int clearPin = 6;
const int powerPin = 7;


//Operations
const int addPin = 12;
const int subPin = 11;
const int multPin = 10;
const int divPin = 9;

long count1 = 0;
long count2 = 0;
float answer = 0;
int mode = 0;
bool state = 0;
int lastPowerState = HIGH;

int function = 0;
String functionName = " ? ";

void setup() {
  lcd.init();
  lcd.noBacklight();

  pinMode(countPin1, INPUT_PULLUP);
  pinMode(countPin10, INPUT_PULLUP);
  pinMode(countPin100, INPUT_PULLUP);

  
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(clearPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
  
  pinMode(addPin, INPUT_PULLUP);
  pinMode(subPin, INPUT_PULLUP);
  pinMode(multPin, INPUT_PULLUP);
  pinMode(divPin, INPUT_PULLUP);
}

void loop() {

//Power button falling edge
int powerState = digitalRead(powerPin);

  if (powerState == LOW && lastPowerState == HIGH) {
    state = !state;
    lcd.clear();
    
    if(state) { 
    lcd.backlight(); 
    lcd.display(); 
    } else { 
      lcd.noBacklight(); 
      lcd.noDisplay();
    }
    delay(100);
  }
  lastPowerState = powerState;



  //In charge of the operation and what to do
  //Math portion of the calculator

  if (state == true){
      delay(100);
      if(function == 0){
        functionName = " ? ";
      }
      
      if(function == 1) {
        delay(100);
        answer = count1 + count2;
        functionName = " + ";
      }
      
      if(function == 2) {
        delay(100);
        answer = count1 - count2;
        functionName = " - ";
      }
      
      if(function == 3) {
        delay(100);
        answer = count1 * count2;
        functionName = " * ";
      }
    
      if(function == 4) {
        delay(100);
          functionName = " / ";
          if (count2 != 0){
                answer = (float)count1 / count2;
                
          } else {
              delay(100);
              answer = 0;
          }
      }


    //Lets the user input the first number
    
    if(mode == 0){
      lcd.setCursor(0,1);
      lcd.print(F("Set Number 1    "));
      
      if(digitalRead(countPin1) == LOW){
        count1++; 
        delay(100);
      }
      if(digitalRead(countPin10) == LOW){
        count1+= 10;
        delay(100);
      }
      if(digitalRead(countPin100) == LOW){
        count1 += 100; 
        delay(100);
      }
      if(digitalRead(clearPin) == LOW){
        count1 = 0; 
        delay(100);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 3; 
        delay(100);
      }
    }



    //Lets the user pick the operation to perform
        
    else if(mode == 3) {
        delay(100);
        lcd.setCursor(0,1);
        lcd.print(F("Choose function ") );
        
        if(digitalRead(addPin) == LOW) {
            function = 1;
            delay(100);
            mode = 1;
        }
        
        if(digitalRead(subPin) == LOW) {
            function = 2;
            delay(100);
            mode = 1;
        }
        
        if(digitalRead(multPin) == LOW) {
            function = 3;
            delay(100);
            mode = 1;
        }
        
        if(digitalRead(divPin) == LOW) {
            function = 4;
            delay(100);
            mode = 1;
        }
    }

    //Lets the user input the 2nd number
    
    else if(mode == 1){
      lcd.setCursor(0,1);
      lcd.print(F("Set Number 2    "));
      
      if(digitalRead(countPin1) == LOW){
        count2++; 
        delay(100);
      }
      if(digitalRead(countPin10) == LOW){
        count2 += 10;
        delay(100);
      }
      if(digitalRead(countPin100) == LOW){
        count2 += 100; 
        delay(100);
      }
      if(digitalRead(clearPin) == LOW){
        count2 = 0; 
        delay(100);
      }
      if(digitalRead(switchPin) == LOW){
        mode = 2; 
        delay(100);
      }



    //Displaying Result
    
    }
    else if(mode == 2){
      lcd.setCursor(0,1);
      if ((function == 4)&&(count2 == 0)){
        lcd.print(F("NaN D:           "));
      } else{
        lcd.print("= ");
        if(answer == (long)answer){
          lcd.print((long)answer);
        } else {
          lcd.print(answer, 4);
        }
        lcd.print(F("                "));
        delay(200);
      }

    //Resets variables to 0 and default

      if(digitalRead(clearPin) == LOW){
        count1 = 0;
        count2 = 0;
        function = 0;
        functionName = " ? ";
        mode = 0;
        lcd.clear();
        delay(250);
      }
    }

  //Constant and will ALWAYS be done

      lcd.setCursor(0,0);
      lcd.print(count1);
      lcd.print(functionName);
      lcd.print(count2);
      lcd.print(F("          "));

      delay(50);
      
  }
}

//February 17th, 2026
//This is an updated calculator and changed how decimal points work
//Falling edge added to power button
//Easier number entering with +10Pin and +100Pin
