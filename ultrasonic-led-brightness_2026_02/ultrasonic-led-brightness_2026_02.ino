int LED4 = 10; // PWM pin connected to the LED
int trigPin = 5; // Trigger pin for the ultrasonic sensor
int echoPin = 6; // Echo pin for the ultrasonic sensor
float distance; // Measured distance in centimeters
float time; // Time taken for the ultrasonic pulse (microseconds)

void setup() {
  // Runs once at startup to configure pins and serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  //Initially setting the LED to low.
  digitalWrite(LED4, LOW);

  // Set trigPin LOW briefly to clear any leftover signal from past pulses
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond HIGH pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure how long the echo pin stays HIGH (time for sound to travel)
  time = pulseIn(echoPin, HIGH);

  // Convert time into distance (cm) using the speed of sound
  distance = (0.0343 * time)/2;

  // Limit the distance to a usable range (5 cm to 40 cm)
  // Values below 5 cm are treated as 5 cm, and values above 40 cm as 40 cm
  float constrainedDistance = constrain(distance, 5.0, 40.0);

  // Map the constrained distance to LED brightness (PWM)
  // Closer distance = brighter LED, farther distance = dimmer LED
  int brightness = map(constrainedDistance, 5.0, 40.0, 255, 0);

  // Apply the calculated brightness to the LED
  analogWrite(LED4, brightness);
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
