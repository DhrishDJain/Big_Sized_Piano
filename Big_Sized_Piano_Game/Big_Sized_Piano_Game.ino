#include "pitches.h"

#define SPEAKER_PIN 8

const uint8_t buttonPins[] = { 12, 11, 10, 9, 7, 6, 5, 4 };
const String buttonPinscolor[] = { "Red", "Orange", "Yellow", "Green", "Cyan", "Blue", "Purple", "LastRed" };
const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const int numTones = sizeof(buttonPins) / sizeof(buttonPins[0]);
int selectedTones[7]; // Array to hold the randomly selected tones
int userInputs[7]; // Array to hold user inputs

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  randomSeed(analogRead(0)); // Seed the random number generator

  // Set button pins as input
  for (uint8_t i = 0; i < numTones; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(SPEAKER_PIN, OUTPUT);

  // Randomly select 7 unique tones
  selectRandomTones();

  // Play the randomly generated sequence
  playSequence(selectedTones);

  // Prompt user to press buttons
  Serial.println("Press the buttons corresponding to the played tones.");
}

void loop() {
  static int inputCount = 0; // Count of inputs received

  // Check for button presses
  for (uint8_t i = 0; i < numTones; i++) {
    if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
      userInputs[inputCount] = buttonTones[i]; // Store the tone
      inputCount++;
      tone(SPEAKER_PIN, buttonTones[i]);
      delay(300); // Debounce delay
      noTone(SPEAKER_PIN);
      Serial.print("Input received: ");
      Serial.println(buttonPinscolor[i]);
    }
  }

  // Check if we have received 7 inputs
  if (inputCount == 7) {
    // Compare user inputs with the selected tones
    bool match = true;
    for (int i = 0; i < 7; i++) {
      if (userInputs[i] != selectedTones[i]) {
        match = false;
        break;
      }
    }

    // Provide feedback
    if (match) {
      Serial.println("Congratulations! You matched the sequence!");
    } else {
      Serial.println("Sorry, the sequence did not match. Try again!");
    }

    // Reset for next attempt
    inputCount = 0;
    memset(userInputs, 0, sizeof(userInputs)); // Clear user inputs
    selectRandomTones(); // Select a new sequence
    playSequence(selectedTones); // Play the new sequence
    Serial.println("Press the buttons corresponding to the played tones.");
  }
}

void selectRandomTones() {
  bool selected[numTones] = { false }; // Track selected tones
  int count = 0;

  while (count < 7) {
    int randomIndex = random(numTones);
    if (!selected[randomIndex]) {
      selected[randomIndex] = true;
      selectedTones[count] = buttonTones[randomIndex];
      Serial.println(buttonPinscolor[randomIndex]);
      count++;
    }
  }
}

void playSequence(int tones[]) {
  for (int i = 0; i < 7; i++) {

    tone(SPEAKER_PIN, tones[i]);
    delay(500); // Delay to allow the note to play
    noTone(SPEAKER_PIN);
    delay(100); // Short delay between notes
  }
}