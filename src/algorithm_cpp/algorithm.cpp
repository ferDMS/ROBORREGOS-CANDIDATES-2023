#include "ZoneA_Test.h"
#include "ZoneA.h"

// Initialize robot object (and measure color)
Robot r;

void setup()
{
    // Initialize a graph object through the default constructor
    Graph g(16);

    // Initialize zone A graph with test values
    zoneAGraphInit(g);

    // Perform test for Zone A
    testZoneA(g);
}

void loop()
{

    if (r.color == "yellow")
    {
        // zoneA(r);
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
        // Serial.print("Color not identified");
        std::cout << "Color not identified" << std::endl;
    }
}

int main()
{
    setup();
    loop();

    return 0;
}