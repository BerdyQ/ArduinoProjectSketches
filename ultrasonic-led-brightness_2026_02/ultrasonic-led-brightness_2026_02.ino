int LED4 = 10;
int trigPin = 5;
int echoPin = 6;
float distance;
float time;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  //Initially setting the LED to low.
  digitalWrite(LED4, LOW);
  // Setting the trigPin to low for 2 microseconds to avoid leftover values from past pulses
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Setting the trigPin to high for 10 microseconds so that the sensor knows to start sending waves
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  // Measures the time of the pulse when echoPin is high
  time = pulseIn(echoPin, HIGH);
  distance = (0.0343 * time)/2;
  // Handles low and high distances to put them in a range of 5 to 40. When distance is lower then 5, it is set to 5 and when it is bigger then 40, it is set to 40;
  float constrainedDistance = constrain(distance, 5.0, 40.0);
  // Maps the constrained distance calculated to the brightness
  int brightness = map(constrainedDistance, 5.0, 40.0, 255, 0);
  // Sets the brightness value to the led
  analogWrite(LED4, brightness);
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
