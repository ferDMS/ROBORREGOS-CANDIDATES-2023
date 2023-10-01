#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

Servo servoGripper;

//MOTORS
//Motors R
int IN1 = 44;
int IN2 = 46;
//Motors L
int IN3 = 48;
int IN4 = 50;
//speeds
int speed = 255;

#define INTERRUPT_PIN 2

#define LED_PIN 13
bool blinkState = false;

//Line following
int IRS_1 = 38;
int IRS_2 = 39;
int IRS_3 = 40;
int IRS_4 = 41;
int IRS_5 = 42;
int S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0;
char strBuf[50];

//sensor color
const int s0 = 3;  
const int s1 = 4;  
const int s2 = 5;  
const int s3 = 6;  
const int out = 7;
//colors
int color = 0;
int rojo = 0;  
int verde = 0;  
int azul = 0;
//valuers colors
int v_c[54] = {41,32,28,22,85,75,63,54,50,42,25,15,103,93,85,42,25,15,103,93,85,76,32,22,70,60,46,35,19,9,35,25,47,37,17,7,43,33,85,74,25,14,36,26,46,35,20,9,158,147,178,168,56,46};

//ultrasonic
//left ultrasonic
#define trigger_left 22
#define echo_left 23
//front ultrasonic
#define trigger_front 37
#define echo_front 35
//right ultrasonic
#define trigger_right 53
#define echo_right 52
#define V 0.034 // Velocity of sound in cm / microseconds
long time;
long distance;
int distance_left;
int distance_front;
int distance_right;

//led
const int LEDR = 24;
const int LEDG = 25;
const int LEDB = 26;

//motors funcions
void front(int speed){
  analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
}

void back(int speed){
  analogWrite(IN1, 0);
  analogWrite(IN2, speed);
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void left(int speed){
  analogWrite(IN1, 0);
  analogWrite(IN2, speed);
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
}

void right(int speed)
{
  analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

//funcions move
void turn_left()
{
  left(speed);
  delay(1400);
}

void turn_right()
{
  right(speed);
  delay(550);
}

void forward(int delay_)
{
  front(speed);
  delay(delay_);
}

int back_(int delay_)
{
  back(speed);
  delay(delay_);
}

//color funcions
int max_(int array[])
{
  int n = array[0];
  for(int i=1; i<7; i++)
  {
    if(array[i] > n){
      n = array[i];
    }
  }
  return n;
}

void color_sensor()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  rojo = pulseIn(out, LOW); 
  digitalWrite(s3, HIGH);   
  verde = pulseIn(out, LOW); 
  digitalWrite(s2, HIGH);    
  azul = pulseIn(out, LOW); 
}

// Para confirmar el color
int color_()
{
  int array_color[9] = {0,0,0,0,0,0,0,0,0};

  for(int i=0; i<15; i++)
  {
    color_sensor();
    if (rojo <= v_c[0] && rojo >=v_c[1] && azul <= v_c[2] && azul >= v_c[3] && verde <= v_c[4] && verde >= v_c[6])
    {
      //Rojo
      array_color[0] =  array_color[0] + 1; 
    }
    else if ((rojo <= v_c[6] && rojo >= v_c[7]) && (azul <= v_c[8] && azul >= v_c[9]) && (verde <= v_c[10] && verde >= v_c[11]))
    {
      //Verde
      array_color[1] =  array_color[1] + 1; 
    }
    else if ((rojo <= v_c[12] && rojo >= v_c[13]) && (azul <=v_c[14]  && azul >= v_c[15]) && (verde <= v_c[16] && verde >= v_c[17]))
    {
      //Azul
      array_color[2] =  array_color[2] + 1;   
    }
    else if ((rojo <= v_c[18] && rojo >= v_c[19]) && (azul <= v_c[20] && azul >= v_c[21]) && (verde <= v_c[22] && verde >= v_c[23]))
    {
      //Celeste
      array_color[3] =  array_color[3] + 1;   
    }
    else if ((rojo <= v_c[24] && rojo >= v_c[25]) && (azul <= v_c[26] && azul >= v_c[27]) && (verde <= v_c[28] && verde >= v_c[29]))
    {
      //Rosa
      array_color[4] =  array_color[4] + 1;   
    }
    else if ((rojo <= v_c[30] && rojo >=v_c[31]) && (azul <= v_c[32] && azul >=v_c[33]) && (verde <= v_c[34] && verde >= v_c[35]))
    {
      //Violeta
      array_color[5] =  array_color[5] + 1;   
    }
    else if ((rojo <= v_c[36] && rojo >= v_c[37]) && (azul <= v_c[38] && azul >=v_c[39]) && (verde <= v_c[40] && verde >= v_c[41]))
    {
      //Amarillo
      array_color[6] =  array_color[6] + 1; 
    }
    else if ((rojo <= v_c[42] || rojo >= v_c[43]) && (azul <= v_c[44] || azul >= v_c[45]) && (verde <= v_c[46] && verde >= v_c[47]))
    {
      //Negro
      array_color[7] =  array_color[8] + 1; 
    }
    else if (rojo == verde || verde == azul || azul == rojo)
    {
      //Aluminio
      array_color[8] =  array_color[8] + 1; 
    }
    //Serial.print(rojo);
    //Serial.print("  ");
    //Serial.print(verde);
    //Serial.print("  ");
    //Serial.print(azul);
    //Serial.println("  ");
    delay(25);
  }
  int num_color = max_(array_color);
  //   for(int i=0; i<9; i++)
  //   {
  //     Serial.print(array_color[i]);
  //     Serial.print("  ");
  //   }
  Serial.print("Color detectado: ");
  Serial.println(num_color+1);

  if (num_color != 0)
  {
    for(int i=0; i<7; i++)
    {
      if(num_color = array_color[i])
      {
        return i + 1;
      }
    }
  }
  else
  {
    return -1;
  }
}

// Checar mientras se mueve
int color_check()
{
  delay(100);
  color_sensor();
  if (rojo <= v_c[0] && rojo >=v_c[1] && azul <= v_c[2] && azul >= v_c[3] && verde <= v_c[4] && verde >= v_c[6])
  {
    //Rojo
    return 1;
  }
  else if ((rojo <= v_c[6] && rojo >= v_c[7]) && (azul <= v_c[8] && azul >= v_c[9]) && (verde <= v_c[10] && verde >= v_c[11]))
  {
    //Verde
    return 2;
  }
  else if ((rojo <= v_c[12] && rojo >= v_c[13]) && (azul <=v_c[14]  && azul >= v_c[15]) && (verde <= v_c[16] && verde >= v_c[17]))
  {
    //Azul
    return 3;
  }
  else if ((rojo <= v_c[18] && rojo >= v_c[19]) && (azul <= v_c[20] && azul >= v_c[21]) && (verde <= v_c[22] && verde >= v_c[23]))
  {
    //Celeste
    return 4;
  }
  else if ((rojo <= v_c[24] && rojo >= v_c[25]) && (azul <= v_c[26] && azul >= v_c[27]) && (verde <= v_c[28] && verde >= v_c[29]))
  {
    //Rosa
    return 5;
  }
  else if ((rojo <= v_c[30] && rojo >=v_c[31]) && (azul <= v_c[32] && azul >=v_c[33]) && (verde <= v_c[34] && verde >= v_c[35]))
  {
    //Violeta
    return 6; 
  }
  else if ((rojo <= v_c[36] && rojo >= v_c[37]) && (azul <= v_c[38] && azul >=v_c[39]) && (verde <= v_c[40] && verde >= v_c[41]))
  {
    //Amarillo
    return 7; 
  }
  else if ((rojo <= v_c[42] || rojo >= v_c[43]) && (azul <= v_c[44] || azul >= v_c[45]) && (verde <= v_c[46] && verde >= v_c[47]))
  {
    //Negro
    return 8;
  }
  else if (rojo == verde || verde == azul || azul == rojo)
  {
    //Alumnio
    return 9;
  }
}

//line following
void line_following()
{
  S1 = digitalRead(IRS_1);
  S2 = digitalRead(IRS_2);
  S3 = digitalRead(IRS_3);
  S4 = digitalRead(IRS_4);
  S5 = digitalRead(IRS_5);
  if (S1 == 1 && S2==1 && S3==0&& S4==1 && S5==1){
    front(speed);
    Serial.println("front");
  }
  else if((S1==1 || S2==1) && S3 == 0)
  {
    left(speed);
    Serial.println("left");
  }
  else if ((S4 == 1 || S5==1) && S3==0){
    right(speed);
    Serial.println("right");
  }
  else if (S1 == 1 && S2==1 && S3==1 && S4==1 && S5==1){
    stop();
    Serial.println("stop");
  }
}

//ultrasonic
long ultrasonic_calcu(long time)
{
  // Calculating the distance
  distance = (time*V) / 2;
  return distance;
}

long ultrasonic_left()
{
  // Clear the trigger pin
  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  // Input time
  time = pulseIn(echo_left, HIGH);
  distance = ultrasonic_calcu(time);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

long ultrasonic_right()
{
  // Clear the trigger pin
  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  // Input time
  time = pulseIn(echo_right, HIGH);
  distance = ultrasonic_calcu(time);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

long ultrasonic_front()
{
  // Clear the trigger pin
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  // Input time
  time = pulseIn(echo_front, HIGH);
  distance = ultrasonic_calcu(time);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

//led
void led_red()
{
  for(int i=0; i<5; i++)
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    delay(300);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    delay(300);
  }
}

void led_green()
{
  for(int i=0; i<5; i++)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
    delay(300);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    delay(300);
  }
}

void led_blue()
{
  for(int i=0; i<5; i++)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
    delay(300);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    delay(300);
  }
}

void led_alu()
{
  for(int i=0; i<5; i++)
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    delay(300);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    delay(300);
  }
}

void gripperOn()
{
  servoGripper.write(180);            
  delay(2000);                        
}

void gripperOff()
{
  servoGripper.write(0);
  delay(2000);
}