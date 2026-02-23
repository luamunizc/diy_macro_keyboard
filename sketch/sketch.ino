#include <Encoder.h>

//#include <NimBLEDevice.h>

#include <BleKeyboard.h>

#define BTN_1 2
#define BTN_2 5
#define BTN_3 4

#define ENC_1 15
#define ENC_2 18
#define ENC_C 22

#define LED 14

BleKeyboard bleKeyboard;

enum State
{
    ADVERTISING,
    LAYER_DEFAULT,
    LAYER_ALT,
    LOW_BATTERY
};

State state = ADVERTISING;

void setState(State newState);

void setup() {
  Serial.begin(115200);
  pinMode(BTN_1 , INPUT_PULLUP);
  pinMode(BTN_2 , INPUT_PULLUP);
  pinMode(BTN_3 , INPUT_PULLUP);
  
  pinMode(ENC_1 , INPUT_PULLUP);
  pinMode(ENC_2 , INPUT_PULLUP);
  pinMode(ENC_C , INPUT_PULLUP);

  pinMode(LED , OUTPUT);

  bleKeyboard.begin();
  
  Encoder meuEncoder(ENC_1, ENC_2);

  long posicaoAntiga  = -999;
}

void loop() {
  digitalWrite(LED, LOW);
  delay(125);
  while (digitalRead(ENC_C) == LOW) {
    digitalWrite(LED, HIGH);
  delay(125);
  }

  if (digitalRead(BTN_1) == LOW) {
    Serial.println("'botão 1'");
  }

  if (digitalRead(BTN_2) == LOW) {
    Serial.println("'botão 2'");
  }

  if (digitalRead(BTN_3) == LOW) {
    Serial.println("'botão 3'");
  }
}
