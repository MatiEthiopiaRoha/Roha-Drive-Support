#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 11 // Onboard LED
#define pizzo 12
int maximumRange = 200; // Maximum range needed
int minimumRange = 10; // Minimum range needed
long duration, distance; // Duration used to calculate distance
 // make some custom characters:
byte ro[8] = {
  0b11111,
  0b10101,
  0b10111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};
byte ha[8] = {
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};
byte te[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b00100,
  0b00111,
  0b00101,
  0b00111
};
byte ch[8] = {
  0b10000,
  0b10000,
  0b11111,
  0b01001,
  0b11101,
  0b01001,
  0b10001,
  0b10001
};
byte no[8] = {
  0b11111,
  0b10101,
  0b10111,
  0b10000,
  0b11111,
  0b00001,
  0b00001,
  0b00001
};
byte lo[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b11111,
  0b10101,
  0b10111,
  0b10100,
  0b10100
};
byte gy[8] = {
  0b11111,
  0b00100,
  0b01110,
  0b01010,
  0b00100,
  0b11110,
  0b10010,
  0b10011
};
byte col[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b00100
};
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, ro);
  lcd.createChar(1, ha);
  lcd.createChar(2, te);
  lcd.createChar(3, ch);
  lcd.createChar(4, no);
  lcd.createChar(5, lo);
  lcd.createChar(6, gy);
  lcd.createChar(7, col);
  lcd.clear();
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(pizzo, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
  lcd.setCursor(4,0);
  lcd.write(0);
  lcd.setCursor(5,0);
  lcd.write(1);
  lcd.setCursor(6,0);
  lcd.print(":");
  lcd.setCursor(7,0);
  lcd.write(2);
  lcd.setCursor(8,0);
  lcd.write(3);
  lcd.setCursor(9,0);
  lcd.write(4);
  lcd.setCursor(10,0);
  lcd.write(5);
  lcd.setCursor(11,0);
  lcd.write(6);
  lcd.setCursor(0,1);
  lcd.print("TEL+251940818912");
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if ( distance <= minimumRange){
 Serial.println("-1");
 digitalWrite(LEDPin, HIGH);
 lcdwrite();
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
 digitalWrite(LEDPin, LOW); 
 }
 //Delay 50ms before next reading.
 
}
void lcdwrite(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0,1);
  lcd.print("ROHA TECHNOLOGY");
  delay(1000);
  lcd.clear();
}

