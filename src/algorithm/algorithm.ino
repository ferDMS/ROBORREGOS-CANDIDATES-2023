#include "ZoneA.h"
#include "Robot.h"

// Initialize robot object (and measure color)
Robot r;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

    r.color = "yellow";

    if (r.color == "yellow")
    {
        zoneA(r);
    }
    else if (r.color == "cyan")
    {
        // ramp(r);
    }
    else if (r.color == "pink")
    {
        // zoneB(r);
    }
    else if (r.color == "purple")
    {
        // zoneC(r);
    }
    else
    {
    }

    delay(2000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
}