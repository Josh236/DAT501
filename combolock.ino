#include <rgb_lcd.h>

int lock = 0; 
const int SW_pin = 7; //Digital input pin for joystick switch
const int X_pin = A0; //Analog input pin for X axis of the joystick
const int Y_pin = A2; //Analog input pin for Y axis of the joystick
int counter = 0; //counts the number of components per input
int limit = 0; //counts the number of input
char *input[4]; //stores components of inputs
char *passcode[4] = {"Right", "Right", "Right", "Right"}; //password for locking and unlocking the lock
rgb_lcd lcd; //Digital input pins connected to LCD Display


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);//declares the rows and colums of the LCD Screen (2 rows, 16 columns)
  lcd.setRGB(255, 0, 0);
  lcd.print("Locked: R _ _ R");//Prints Locked and hint of combination
  lcd.setCursor(0, 1);
  lcd.print("Control Inverted");
  pinMode(SW_pin, INPUT); //sets up the joystick switch in order to take in input
  digitalWrite(SW_pin, HIGH);
}

void loop() {
  if (limit < 3) {
    if (counter < 4) {
      if (analogRead(X_pin) < 60) { //inverted controls
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Down");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Down";
        counter++;
      }
      else if (analogRead(X_pin) > 600) { //inverted 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Up");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Up";
        counter++;
      }
      else if (analogRead(Y_pin) < 60) { //inverted
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Left");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Left";
        counter++;
      }
      else if (analogRead(Y_pin) > 600) { //inverted
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Right");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Right";
        counter++;
      }

      delay(200);
    }
    else {
      if ((input[0] == passcode[0]) && (input[1] == passcode[1]) && (input[2] == passcode[2]) && (input[3] == passcode[3])) {
        lcd.clear();
        limit = 0;
        counter = 0;
        if (lock == 0) {
          lcd.setRGB(0, 255, 0);
          lcd.print("Unlocked");
          for (lock = 0; lock < 90; lock++)
          {
            delay(15);
          }
        }
        else {
          lcd.setRGB(255, 0, 0);
          lcd.print("Locked");
          for (lock = 90; lock > 0; lock--)
          {
            delay(15);
          }
        }
      }
      else {
        lcd.clear();
        limit++;
        counter -= 4;
        lcd.setRGB(255, 0, 0);
        lcd.print("Wrong Attempt");
        lcd.setCursor(0, 1);
        lcd.print("Attempts left:");
        lcd.setCursor(15, 1);
        lcd.print(3-limit);
      }
    }

  }
  else {
    lcd.clear();
    lcd.setRGB(255, 0, 0);
    lcd.print("Intruder Alert");
    lcd.setCursor(0, 1);
    lcd.print("Locked");
    delay(500);
      }
  }
