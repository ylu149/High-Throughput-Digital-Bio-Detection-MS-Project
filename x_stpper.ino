#include <Stepper.h>

const int stepsPerRevolution = 400;
const float stepDistance = 0.0128;
Stepper myStepper(stepsPerRevolution, 8, 9); // 8 is PUL, 9 is DIR

int currentPos = 0; 

void setup() {
    myStepper.setSpeed(1000); // Set the speed in RPM
    Serial.begin(9600); // Start serial communication
    // runner(1, -1000);
}

const long steps = mmToSteps(9);
void loop() {
    if (Serial.available() > 0) {
        Serial.println("Please enter a letter (A-H) or 0:");

        // Wait for all serial data to arrive
        delay(100); 

        String inputString = Serial.readStringUntil('\n'); // Read the entire string until newline

        // Check if the input string length is not 1
        if (inputString.length() != 1) {
            Serial.println("Invalid input. Please enter only a single character.");
            return;
        }

        char userChar = inputString.charAt(0); // Get the first character
        userChar = toupper(userChar); // Convert to uppercase

        // Check if input is 0 and treat as 'A'
        if (userChar == '0') {
            userChar = 'A';
        }

        // Validate if the input is a letter A-H
        if (userChar < 'A' || userChar > 'H') {
            Serial.println("Invalid input. Please enter a letter A-H or 0.");
            return;
        }

        int targetPos = userChar - 'A'; // Convert letter to number (0 or A-H)
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
