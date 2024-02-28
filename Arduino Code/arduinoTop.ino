#include <Stepper.h>

const int stepsPerRevolution = 400;  // Number of steps per revolution
const float stepDistance = 0.00396875;  // Distance per step in inches

Stepper myStepper(stepsPerRevolution, 8, 9);

void setup() {
    myStepper.setSpeed(500);
    Serial.begin(9600);
    Serial.flush();
    myStepper.step(8000);
}

const long steps = mmToSteps(1);
const int iters = 6;
void loop() {
    //Move down
    if (promptUser('y')) {
        runner(iters, -steps);
        delay(1000);
    }

    // Move up
    if (promptUser('y')) {
        runner(iters, steps);
        delay(1000);
    }
}

long mmToSteps(float mm) {
    float mmPerStep = stepDistance / 25.4;
    return round(mm / mmPerStep);
}

void runner(int iterations, long steps) {
    for (int i = 0; i < iterations; i++) {
        myStepper.step(steps);
    }
}

bool promptUser(char expectedChar) {
    Serial.print("Press '");
    Serial.print(expectedChar);
    Serial.println("' to move the stepper motor:");

    while (true) {
        if (Serial.available() > 0) {
            char receivedChar = Serial.read();
            if (receivedChar == expectedChar) {
                return true;
            }
        }
    }
}
