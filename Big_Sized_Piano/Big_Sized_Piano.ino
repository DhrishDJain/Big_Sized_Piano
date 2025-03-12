
const int NUM_SENSORS = 6;
const int SPEAKER_PIN = 9;
const int SENSOR_PINS[NUM_SENSORS] = { A0, A1, A2, A3, A4, A5 };

// Piano note frequencies in Hz
const int NOTES[NUM_SENSORS] = {
  2000,  // C4 (middle C)
  587,  // D4
  980,  // E4
  349,
  1049,
  47   // F4
};

// How sensitive the piezo sensors are (lower = more sensitive)
const int THRESHOLD = 1022;

// How long each note plays
const int NOTE_DURATION = 200;

void setup() {
  // Set up speaker pin as output
  pinMode(SPEAKER_PIN, OUTPUT);

  // Set up piezo sensor pins as inputs
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
  }

  // Optional: for debugging
  Serial.begin(9600);
}

void loop() {
  // Check each sensor
  for (int i = 0; i < NUM_SENSORS; i++) {
    // Read the sensor value
    int sensorValue = analogRead(SENSOR_PINS[i]);
    // If the sensor is hit hard enough
    // Serial.println(sens            orValue);
    if (sensorValue > THRESHOLD) {
      // Play the note
      tone(SPEAKER_PIN, NOTES[i], NOTE_DURATION);
      sensorValue -= 100;

      // Optional: print the sensor value for debugging
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(sensorValue);

      // Wait for note to finish
      delay(NOTE_DURATION);
      noTone(SPEAKER_PIN);
    }
  }
}