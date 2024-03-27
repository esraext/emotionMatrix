#include <Arduino.h>

const int eyesPin1 = 17;
const int eyesPin2 = 16;
const int smileyPins[] = {4, 15, 25, 26, 0};
const int sadPins[] = {39, 13, 15, 26, 25};
const int amazedPins[] = {32, 33, 15, 26};
const int pokerPins[] = {25, 15, 26};

const int buttonPin = 27;

int currentEmotion = 0;
int numEmotions = 4;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200; // Increase debounce delay for better response

void setup() {
  pinMode(eyesPin1, OUTPUT);
  pinMode(eyesPin2, OUTPUT);
  digitalWrite(eyesPin1, HIGH);
  digitalWrite(eyesPin2, HIGH);

  for (int i = 0; i < sizeof(smileyPins) / sizeof(smileyPins[0]); i++) {
    pinMode(smileyPins[i], OUTPUT);
    pinMode(sadPins[i], OUTPUT);
  }

  for (int i = 0; i < sizeof(amazedPins) / sizeof(amazedPins[0]); i++) {
    pinMode(amazedPins[i], OUTPUT);
  }

  for (int i = 0; i < sizeof(pokerPins) / sizeof(pokerPins[0]); i++) {
    pinMode(pokerPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT_PULLUP);
}

void turnOnPins(const int pins[], int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pins[i], HIGH);
  }
}

void turnOffPins(const int pins[], int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pins[i], LOW);
  }
}

void showEmotion(int emotionIndex) {
  currentEmotion = emotionIndex;

  turnOffPins(smileyPins, sizeof(smileyPins) / sizeof(smileyPins[0]));
  turnOffPins(sadPins, sizeof(sadPins) / sizeof(sadPins[0]));
  turnOffPins(amazedPins, sizeof(amazedPins) / sizeof(amazedPins[0]));
  turnOffPins(pokerPins, sizeof(pokerPins) / sizeof(pokerPins[0]));

  switch (currentEmotion) {
    case 0:
      turnOnPins(smileyPins, sizeof(smileyPins) / sizeof(smileyPins[0]));
      break;
    case 1:
      turnOnPins(sadPins, sizeof(sadPins) / sizeof(sadPins[0]));
      break;
    case 2:
      turnOnPins(amazedPins, sizeof(amazedPins) / sizeof(amazedPins[0]));
      break;
    case 3:
      turnOnPins(pokerPins, sizeof(pokerPins) / sizeof(pokerPins[0]));
      break;
  }
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && millis() - lastDebounceTime > debounceDelay) {
    showEmotion((currentEmotion + 1) % numEmotions);
    lastDebounceTime = millis();
  }
}
