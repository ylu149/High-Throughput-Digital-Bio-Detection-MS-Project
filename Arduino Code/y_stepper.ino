#include <Stepper.h>

const int stepsPerRevolution = 400;
const float stepDistance = 0.0128;
Stepper myStepper(stepsPerRevolution, 8, 9); // 8 is PUL, 9 is DIR

int currentPos = 0; 

void setup() {
    myStepper.setSpeed(1000); // Set the speed in RPM
    Serial.begin(9600); // Start serial communication
    //myStepper.step(250);
}

const long steps = mmToSteps(9);
void loop() {
    if (Serial.available() > 0) {
        Serial.println("Please enter an integer between 1 and 12:");

        // Wait for all serial data to arrive
        delay(100); 

        String inputString = Serial.readStringUntil('\n'); // Read the entire string until newline

        // Convert the input string to an integer
        int userInput = inputString.toInt(); 

        // Check if the input is not between 1 and 12
        if (userInput < 0 || userInput > 12) {
            Serial.println("Invalid input. Please enter an integer between 1 and 12.");
            return;
        }

        if (userInput == 0){
          userInput = 1;
        }
        
        int targetPos = userInput - 1; // Convert to zero-based index
        int itersToMove = targetPos - currentPos; // Calculate the relative steps to move

        runner(itersToMove, steps); // Move the stepper

        currentPos = targetPos; // Update current position

        Serial.println();
        Serial.print("You are at position: ");
        Serial.print(currentPos);
    }
}

// Function to convert millimeters to steps
long mmToSteps(long mm) {
    return 8 * round(mm / stepDistance);
}

void runner(int iterations, long steps){
    if (iterations < 0){
        steps = -steps; // Reverse direction if iterations is negative
        iterations = -iterations; // Make iterations positive
    }
  
    for (int i = 0; i < iterations; i++){
        myStepper.step(steps);
        Serial.println(i);
    }
}
