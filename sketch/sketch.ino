#include <Encoder.h>
#include <WiFi.h>
#include <BleKeyboard.h>

#define BTN_1 3
#define BTN_2 5
#define BTN_3 4

#define ENC_1 15
#define ENC_2 18
#define ENC_C 22

#define LED 14

Encoder encoder(ENC_1, ENC_2);

long posicaoAntiga = -999;

unsigned long previousMillis = 0;
const long interval = 500;
bool ledState = LOW;

BleKeyboard bleKeyboard;

bool lastB1 = HIGH;
bool lastB2 = HIGH;
bool lastB3 = HIGH;
bool lastEC = HIGH;

enum State {
  ADVERTISING,
  LAYER_DEFAULT,
  LAYER_ALT,
  LOW_BATTERY
};

State state = ADVERTISING;

void setState(State newState);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  delay(1000);

  Serial.println("Ligou agora");

  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  pinMode(ENC_1, INPUT_PULLUP);
  pinMode(ENC_2, INPUT_PULLUP);
  pinMode(ENC_C, INPUT_PULLUP);

  pinMode(LED, OUTPUT);

  bleKeyboard.begin();
}

void loop() {

  unsigned long currentMillis = millis();

  switch (state) {
    case ADVERTISING:

      if (bleKeyboard.isConnected()) {
        setState(LAYER_DEFAULT);
      }

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        ledState = !ledState;
        digitalWrite(LED, ledState);
      }
      break;

    case LAYER_DEFAULT:
      digitalWrite(LED, LOW);
      copy(BTN_1);
      paste(BTN_2);
      lockComputer(BTN_3);
      switchLayer(LAYER_ALT, ENC_C);
      zoom();
      if (!bleKeyboard.isConnected()) {
        setState(ADVERTISING);
      }
      break;

    case LAYER_ALT:
      digitalWrite(LED, HIGH);
      gitStatus(BTN_1);
      taskStart(BTN_2);
      neverForget(BTN_3);
      zoom();
      switchLayer(LAYER_DEFAULT, ENC_C);
      if (!bleKeyboard.isConnected()) {
        setState(ADVERTISING);
      }
      break;

    case LOW_BATTERY:
      // Lógica de bateria fraca.
      break;
  }
}

void setState(State newState) {
  state = newState;
}

void copy(int button) {
  bool estadoAtual = digitalRead(button);
  
  if (estadoAtual != lastB1) {
    delay(50);
    estadoAtual = digitalRead(button);
    
    if (estadoAtual == LOW && lastB1 == HIGH) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press('c');
      delay(50);
      bleKeyboard.releaseAll();
    }
    lastB1 = estadoAtual;
}

void paste(int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastB2) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastB2 == HIGH) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press('v');
      delay(50);
      bleKeyboard.releaseAll();
    }
    lastB2 = estadoAtual;
  }
}

void lockComputer(int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastB3) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastB3 == HIGH) {
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('l');
      delay(50);
      bleKeyboard.releaseAll();
    }
    lastB3 = estadoAtual;
  }
}

void switchLayer(State nextState, int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastEC) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastEC == HIGH) {
      setState(nextState);
    }
    lastEC = estadoAtual;
  }
}

void gitStatus(int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastB1) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastB1 == HIGH) {
      bleKeyboard.print("git status");
    }
    lastB1 = estadoAtual;
  }
}

void taskStart(int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastB2) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastB2 == HIGH) {
      bleKeyboard.print("task start");
    }
    lastB2 = estadoAtual;
  }
}

void neverForget(int button) {
  bool estadoAtual = digitalRead(button);
  if (estadoAtual != lastB3) {
    delay(50);
    estadoAtual = digitalRead(button);
    if (estadoAtual == LOW && lastB3 == HIGH) {
      bleKeyboard.print("await ");
    }
    lastB3 = estadoAtual;
  }
}

void zoom() {
  long novaPosicao = encoder.read();

  if (novaPosicao - posicaoAntiga >= 4) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('+');
    delay(20);
    bleKeyboard.releaseAll();
    posicaoAntiga = novaPosicao;
  } else if (posicaoAntiga - novaPosicao >= 4) {
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('-');
    delay(20);
    bleKeyboard.releaseAll();
    posicaoAntiga = novaPosicao;
  }
}