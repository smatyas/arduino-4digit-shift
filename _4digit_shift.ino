//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;
// Digit 1 active pin
int digit1 = 2;
// Digit 2 active pin
int digit2 = 3;
// Digit 3 active pin
int digit3 = 4;
// Digit 4 active pin
int digit4 = 5;

unsigned long previousChange = 0;  
String text = "----";

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  
  digitalWrite(digit1, !LOW);
  digitalWrite(digit2, !LOW);
  digitalWrite(digit3, !LOW);
  digitalWrite(digit4, !LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousChange > 1000) {
    previousChange = currentMillis;
    text = String(random(-999,999));
  }

  display4(text);
}

void display4(String str) {
  byte data;
  while (str.length() < 4) {
    str = ' ' + str;
  }
  for (int i = 0; i < 4; i++) {
    switch (str[i]) {
      case '0':
        data = B00111111;
        break;
      case '1':
        data = B00000110;
        break;
      case '2':
        data = B01011011;
        break;
      case '3':
        data = B01001111;
        break;
      case '4':
        data = B01100110;
        break;
      case '5':
        data = B01101101;
        break;
      case '6':
        data = B01111101;
        break;
      case '7':
        data = B00000111;
        break;
      case '8':
        data = B01111111;
        break;
      case '9':
        data = B01101111;
        break;
      case '-':
        data = B01000000;
        break;
      default:
        data = B00000000;
        break;
    }
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data);  
    digitalWrite(latchPin, HIGH);

    switch (i) {
      case 0:
        renderDigit(digit1);
        break;
      case 1:
        renderDigit(digit2);
        break;
      case 2:
        renderDigit(digit3);
        break;
      case 3:
        renderDigit(digit4);
        break;
    }

    delay(5);
  }
}

void renderDigit(int digit) {

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);

  delayMicroseconds(100);
  
  digitalWrite(digit1, digit1 == digit ? LOW : HIGH);
  digitalWrite(digit2, digit2 == digit ? LOW : HIGH);
  digitalWrite(digit3, digit3 == digit ? LOW : HIGH);
  digitalWrite(digit4, digit4 == digit ? LOW : HIGH);
  
  delayMicroseconds(100);
  
}

