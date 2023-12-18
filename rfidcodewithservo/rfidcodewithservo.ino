
#include <Servo.h>
#include <SPI.h>
#include <RFID.h>
#include <Buzzer.h>

Buzzer buzzer(2, 6);

int time = 500;
#define CorrectLED 5
#define WrongLED 4
//#define buzzer 2

RFID rfid(10, 9);

byte kart[5] = { 3, 82, 69, 251, 239 };
Servo myservo;
boolean card;

void setup() {
  pinMode(CorrectLED, OUTPUT);
  pinMode(WrongLED, OUTPUT);
  digitalWrite(CorrectLED, LOW);
  digitalWrite(WrongLED, LOW);


  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  myservo.attach(3);
  myservo.write(100);
  buzzer.begin(10);
  buzzer.sound(NOTE_G3, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_G3, time * 2);
}

void loop() {

  if (rfid.isCard()) {


    if (rfid.readCardSerial()) {
      Serial.print("Found ID: ");
      Serial.print(rfid.serNum[0]);
      Serial.print(",");
      Serial.print(rfid.serNum[1]);
      Serial.print(",");
      Serial.print(rfid.serNum[2]);
      Serial.print(",");
      Serial.print(rfid.serNum[3]);
      Serial.print(",");
      Serial.println(rfid.serNum[4]);
    }
    for (int i = 1; i < 5; i++) {
      if (rfid.serNum[0] == kart[0] && rfid.serNum[1] == kart[1] && rfid.serNum[2] == kart[2] && rfid.serNum[3] == kart[3] && rfid.serNum[4] == kart[4]) {
        card = true;
      } else {
        card = false;
      }
    }
    if (card == true) {
      Serial.println("Correct Card");
      myservo.write(20);
      digitalWrite(CorrectLED, HIGH);
      digitalWrite(WrongLED, LOW);

      buzzer.sound(NOTE_C7, 80);
      buzzer.sound(NOTE_E7, 80);
      buzzer.sound(0, 80);
      buzzer.end(20);
      delay(2000);

      myservo.write(100);
      digitalWrite(CorrectLED, LOW);
      digitalWrite(WrongLED, LOW);
    } else {
      Serial.println("Wrong Card");
      digitalWrite(CorrectLED, LOW);
      digitalWrite(WrongLED, HIGH);

      buzzer.sound(NOTE_E7, 80);
      buzzer.sound(NOTE_E7, 80);
      buzzer.sound(0, 80);
      buzzer.sound(NOTE_E7, 80);
      buzzer.sound(0, 80);
      buzzer.end(20);
      
    }
    rfid.halt();
  } else {
    digitalWrite(CorrectLED, LOW);
    digitalWrite(WrongLED, LOW);
  }
}