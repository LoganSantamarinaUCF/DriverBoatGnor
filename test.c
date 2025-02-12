//This is a script that will test my math and values cause I dont have the parts or boat yet
#include <stdio.h>
#include <math.h>

// Define the variables
float motor_speed;

float servo_motor_angle;

// Variables for the points that follow the line and form a right triangle
float px, py;
float qx, qy;
float rx, ry;

// The distance between x and x1 when calculating direction; lower values will have a more accurate slope but higher values will be better for the boat's length on the curve
float boat_scalar = 0.1;

// Angle starts at 90 degrees
float current_angle = 90;

float t = 0;  // This value drives the boat along within the functions

// Function prototypes
float Distance(float x1, float y1, float x2, float y2);
float CurveX(int t);
float CurveY(int t);
void AddTime(float val);

int main() {
    // This simulates the loop of the Arduino moving 100 units
    for (int i = 0; i < 100; i++) {  // Run the loop 100 times (you can adjust as necessary)
        // Point p
        px = CurveX(t - boat_scalar);
        py = CurveY(t - boat_scalar);

        // Point q
        qx = CurveX(t + boat_scalar);
        qy = CurveY(t + boat_scalar);

        // Point r
        rx = CurveX(t - boat_scalar);
        ry = CurveY(t + boat_scalar);

        // Create vector PR and calculate its magnitude
        float vertical = Distance(px, py, rx, ry);
        // Create vector QR and calculate its magnitude
        float horizontal = Distance(qx, qy, rx, ry);

        // Determine angle of measure and adjust the boat accordingly
        current_angle = atan(vertical / horizontal);

        // Print the current angle
        printf("At time %f Current Angle: %f radians or %f degrees\n",t, current_angle, current_angle * 180 / 3.14);

        // Update time
        AddTime(1);
    }

    return 0;
}

// Function to calculate distance between two points
float Distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Curve function for X (this is a placeholder)
float CurveX(int t) {
    return t;
}

// Curve function for Y (this is a placeholder, you had a typo here - you need to multiply by `t * t`)
float CurveY(int t) {
    return -0.1 * (t * t);
}

// Function to simulate the progression of time
void AddTime(float val) {
    t += val;
}
