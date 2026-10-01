// libraries to be included for this excercise
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin definitions/declarations
#define trigPin 3
#define echoPin 2

// variable declarations
Servo servo;
int sound = 250;
LiquidCrystal_I2C lcd(0x27, 20, 4);

// code for setup
void setup() {

// code to initialise the serial monitor
Serial.begin (9600);

// declaration of inputs/outputs
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

// code to initialise servo
servo.attach(6);

}

// code for main loop
void loop() {

// initialisation of variables
long duration, distance;

  // code to run lcd screen & its backlight
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,2);
  lcd.setCursor(0,3);

// code to write to trigger pin
digitalWrite(trigPin, LOW);

// code to initialise the delay
delayMicroseconds(2);

// code to write the trigger pin
digitalWrite(trigPin, HIGH);

// code to initialise the delay
delayMicroseconds(10);

// code to write the trigger pin
digitalWrite(trigPin, LOW);

// codes for initialising the variables (duration/distance)
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1; 

// code for my if statement 
if (distance < 15) {

// code to print to the serial monitor
Serial.print(distance);

// code to display the distance on the lcd screen
lcd.print(distance);

// code to display cm's on the serial monitor
Serial.println(" cm");

// code to display cm's on the lcd screen 
lcd.setCursor(0,1);
lcd.print("  cm");

// code to set the servo to 0
servo.write(0);

}

// code for my else if statement
else if ((distance > 15) && (distance <180)) {

// code to declare variable in this instance
int servo_limits = (distance/2);

// code to print the distance on the serial monitor
Serial.print(distance);

// code to print the distance on the lcd screen
lcd.print(distance);

// code to print cm's on the serial monitor
Serial.println(" cm");

// code to print cm's on the lcd screen
lcd.setCursor(0,1);
lcd.print("  cm");

// code to set the servo based on the distance
servo.write(servo_limits); }

// code for my final else statement
else {

// code to print a message to the serial monitor
Serial.println("The distance is more than 180cm");

// code to print a message on the lcd screen
lcd.print( "Distance is more than 180 cm");

}

// code to set the delay
delay(500);

}
