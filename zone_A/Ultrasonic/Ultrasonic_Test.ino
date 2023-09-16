#define TRIGGER 2
#define ECHO 3
#define V 0.034  // Velocity of sound in cm / microseconds
long time;
long distance;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIGGER, LOW);
}

void loop() {
// Clear the trigger pin
digitalWrite(TRIGGER, LOW);
delayMicroseconds(2);

// Sets the trigger pin on HIGH state for 10 micro seconds
digitalWrite(TRIGGER, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER, LOW);

// Input time
time = pulseIn(ECHO, HIGH);

// Calculating the distance
distance = (time*V) / 2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

delay(100);
}

