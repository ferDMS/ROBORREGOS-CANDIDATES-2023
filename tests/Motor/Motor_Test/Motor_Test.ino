/*
Mini L298N Double motor connection
Arduino Nano
*/

// Motor A
#define IN1 3;
#define IN2 5;
// Motor B
#define IN3 6;
#define IN4 9;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Please press:\n\tW to go forward\n\tS to go backwards\n\tC to stop");
}

void loop() {
  char input;

  while(Serial.available()) {
    input = Serial.read();
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    if (input =='w' || input == 'W') Forward();
    else if (input =='s' || input == 'S') Reverse();
    else if (input == 'c' || input == 'C') Stop();
    else Serial.println("Invalid command");
  }
}

void Forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.print("Motor A Forward");
  Serial.println();
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
  Serial.println("Motor B Forward");
  Serial.println();
}

void Reverse() {
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);
  Serial.print("Motor A Reverse");
  Serial.println();
  
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);
  Serial.println("Motor B Reverse");
  Serial.println();
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.print("Motor A Stop");
  Serial.println();
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Motor B Stop");
  Serial.println();
}