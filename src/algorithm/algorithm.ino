#include "ZoneA_Test.h"
#include "ZoneA.h"

// Initialize robot object (and measure color)
Robot r;

void setup() {
    // Initialize Serial monitor connection
    Serial.begin(9600);

    // Initialize zone A graph with test values
    Graph g = zoneAGraphInit();

    // Perform test for Zone A
    testZoneA(g);
}

void loop() {
    delay(1000);
    // put your main code here, to run repeatedly:

    if (r.color == "yellow") {
        // zoneA(r);
    } else if (r.color == "cyan") {
        // ramp(r);
    } else if (r.color == "pink") {
        // zoneB(r);
    } else if (r.color == "purple") {
        // zoneC(r);
    } else {
        Serial.print("Color not identified");
        // std::cout << "Color not identified" << std::endl;
    }
}
