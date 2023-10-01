#include "ZoneA.h"
#include "ZoneB.h"
#include "ZoneA_Test.h"
#include "Robot.h"
#include "Ramp.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Functions.h"
#endif

// Initialize robot object (and measure color)

void setup()
{
    Serial.begin(500000);

    //Motors
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    //mpu
    //Line following
    pinMode(IRS_1, INPUT);
    pinMode(IRS_2, INPUT);
    pinMode(IRS_3, INPUT);
    pinMode(IRS_4, INPUT);
    pinMode(IRS_5, INPUT);
    //sensor color
    digitalWrite(s0,HIGH);  
    digitalWrite(s1,HIGH); 
    //led
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    //ultrasonic left
    pinMode(trigger_left, OUTPUT);
    pinMode(echo_left, INPUT);
    digitalWrite(trigger_left, LOW);
    //ultrasonic front
    pinMode(trigger_front, OUTPUT);
    pinMode(echo_front, INPUT);
    digitalWrite(trigger_front, LOW);
    //ultrasonic right
    pinMode(trigger_right, OUTPUT);
    pinMode(echo_right, INPUT);
    digitalWrite(trigger_right, LOW);
    servoGripper.attach(8);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("Setup Done");
}

void loop()
{

    Robot r;

    // // Declare graph object
    // Graph g(16);
    // // Initialize vertex values
    // zoneAGraphInit(g);
    // // Test zone A;
    // testZoneA(r, g);

    // r.getColor();
    // // r.getAllDistances();
    // Serial.print("Color detectado: ");
    // Serial.println(r.color);

    // r.rgb("red");
    // // r.rgb("green");
    // // r.rgb("blue");

    for (int i = 0; i < 50; i++) {
        r.getDistance("right");
        delay(300);
    }

    // ramp(r);

    zoneA(r);

    if (r.color == "yellow")
    {
        Serial.print("Yellloowwwww");
        // zoneA(g);
    }
    else if (r.color == "cyan")
    {
        ramp(r);
    }
    else if (r.color == "pink")
    {
        zoneB(r);
    }
    else if (r.color == "purple")
    {
        // zoneC(r);
    }
    else
    {
    }

    exit(0);

    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
}