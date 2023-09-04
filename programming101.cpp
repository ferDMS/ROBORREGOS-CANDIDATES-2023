/* 
Due to the low memory of a microprocessor, C++ is used because it has a better runtime.
In Arduino, you can't simply #import <vector>, there is a specific way, search online.
Serial.begin(9600) --> Initialize serial communication between the computer and Arduino, the number is for confirmation.
delay(1) --> Pause the program for a certain amount of time.
digitalWrite(PIN, HIGH/LOW) --> To send a signal on a digital pin.
pinMode(PIN, INPUT/OUTPUT) --> To change the type of signal transmission.
analogRead(PIN) --> To interpret analog value ranges in a certain way.
setup and loop --> Functions that are executed when the program starts and something that runs forever after setup.
*/

#include <iostream>
using namespace std;

// Iterative fibonacci sequence example exercise
int main()
{
    int n = 8;
    int nums[n];
    nums[0] = 1;
    nums[1] = 1;

    for (int i = 2; i < n; i++) {
        nums[i] = nums[i-1] + nums[i-2];
    }
    
    for (int i = 0; i < n; i++) {
        cout << nums[i] << "  " << endl;
    }

    return 0;
}
