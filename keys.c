#include <OneWire.h>

#define pin 10

byte key_to_write[] = { 0x89, 0x35, 0xC0, 0x3C, 0x0B, 0x00, 0x50, 0x3F };

const int buttonPin  = 8;     // the pin that the pushbutton is attached to
const int ledPin     = 13;    // the pin that the LED is attached to
int counter = 1;

int buttonState      = 0;     // current state of the button
int lastButtonState  = 0;     // previous state of the button
int ledState         = 0;     // remember current led state
int stateNum         = 1;

OneWire ds(pin);  // pin 10 is 1-Wire interface pin now

void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(buttonPin, INPUT);
}

void loop() {
  
 // read the pushbutton input pin
  buttonState = digitalRead(buttonPin);
 
  // check if the button is pressed or released
  // by comparing the buttonState to its previous state 
  if (buttonState != lastButtonState) {
    
    // change the state of the led when someone pressed the button
    byte key_to_write[8];
    if (buttonState == 1 & stateNum < 9) 
 {
      stateNum++; 
      Serial.print(stateNum);
      switch (stateNum) 
   {
    case 1:
      key_to_write[] = { 0x9B, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };
      beep();
      break;
    case 2:
      key_to_write[] = { 0xE1, 0x00, 0x36, 0x5A, 0x11, 0x40, 0xBE, 0x01 };
      beep();beep();
      break;
    case 3:
      key_to_write[] = { 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };
      beep();beep();beep();
      break;
    case 4:
      key_to_write[] = { 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
      beep();beep();beep();beep();
      break;
    case 5:
      key_to_write[] = { 0xE6, 0x00, 0x00, 0x09, 0x3C, 0xE4, 0xA9, 0x01 };
      beeep();
      break;
    case 6:
      key_to_write[] = { 0xFB, 0x00, 0x00, 0xAA, 0x11, 0xBE, 0x00, 0x01 };
      beeep();beeep();
      break;
    case 7:
      key_to_write[] = { 0x5C, 0x00, 0x00, 0x0F, 0x2E, 0xB8, 0x76, 0x01 };
      beeep();beeep();beeep();
      break;
    case 8:
      key_to_write[] = { 0x2D, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01 };
      beeep();beeep();beeep();beeep();
      break;
    default:
      stateNum = 1;
      key_to_write[]= { 0x9B, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };
      beep();
      break;      
 }
}

    }

    // remember the current state of the button
    lastButtonState = buttonState;
  }
  // adding a small delay prevents reading the buttonState to fast
  // ( debouncing )
  delay(100);
      
  byte i;
  byte data[8];

  ds.reset();
  delay(50);
  ds.write(0x33); // "READ" command
  
  ds.read_bytes(data, 8);

  Serial.print("KEY ");
  for( i = 0; i < 8; i++) {
    Serial.print(data[i], HEX);
    if (i != 7) Serial.print(":");
  }

  // Check if FF:FF:FF:FF:FF:FF:FF:FF
  // If your button is really programmed with FF:FF:FF:FF:FF:FF:FF:FF, then remove this check
  if (data[0] & data[1] & data[2] & data[3] & data[4] & data[5] & data[6] & data[7] == 0xFF)
  {
    Serial.println("...nothing found!"); 
    return;
  }

  // Check if read key is equal to the one to be programmed
  for (i = 0; i < 8; i++)
    if (data[i] != key_to_write[i])
      break;
    else
      if (i == 7)
      {
        Serial.println("...already programmed!");
        digitalWrite(ledPin, HIGH);delay(150);digitalWrite(ledPin, LOW);
        delay(150);
        digitalWrite(ledPin, HIGH);delay(500);digitalWrite(ledPin, LOW);
        return;
      }

  Serial.println();
  Serial.print("Programming new key...");
  
  for (uint8_t i = 0; i < 8; i++)
  {
    ds.reset();
    data[0] = 0x3C; // "WRITE" command
    data[1] = i; // programming i-th byte
    data[2] = 0;
    data[3] = key_to_write[i];
    ds.write_bytes(data, 4);
    Serial.print(".");
  
    uint8_t crc = ds.read();
    
    if (OneWire::crc8(data, 4) != crc) {
        Serial.print("error!\r\n");
        beep();beep();beep();
        return;
    }
    else
      Serial.print(".");
    
    send_programming_impulse();
  }
  
  Serial.println("done!");
  beep();beeep();
  return;
}

void send_programming_impulse()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); 
  delay(60);
  digitalWrite(pin, LOW); 
  delay(5);
  digitalWrite(pin, HIGH); 
  delay(50); 
}

void beep()
{
  digitalWrite(ledPin, HIGH);delay(75);digitalWrite(ledPin, LOW);
  delay(25);
}

void beeep()
{
  digitalWrite(ledPin, HIGH);delay(125);digitalWrite(ledPin, LOW);
  delay(50);
}