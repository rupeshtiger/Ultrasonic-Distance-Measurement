#include <LiquidCrystal.h> // Include the LCD library

// Define pins for Ultrasonic Sensor
const int trigPin = 9;  // Trigger pin
const int echoPin = 10; // Echo pin

// Define LCD pin connections (Optional)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// Variables for duration and distance
long duration;
int distance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes for Trigger and Echo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LCD (Optional)
  lcd.begin(16, 2); // Set up the LCD with 16 columns and 2 rows
  lcd.print("Distance:");  // Print a fixed message on the first row
}

void loop() {
  // Variable for averaging the distance readings
  long total = 0;

  // Take 5 readings and average them for better accuracy
  for (int i = 0; i < 5; i++) {
    // Clear the trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigger pin high for 10 microseconds to send out the pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo pin and calculate the duration
    total += pulseIn(echoPin, HIGH);
  }

  duration = total / 5;  // Average of 5 readings

  // Calculate the distance in cm (speed of sound is 0.0343 cm/µs)
  distance = duration * 0.0343 / 2;

  // Check if the distance is within the sensor's range
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
    
    // Display on LCD (Optional)
    lcd.setCursor(0, 1); // Set the cursor to the second row
    lcd.print("Out of range   ");
  } else {
    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Display the distance on the LCD (Optional)
    lcd.setCursor(0, 1); // Set the cursor to the second row
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm  ");  // Add spaces to clear any previous text
  }

  // Short delay before the next measurement
  delay(500);
}
