#include <Servo.h>

//the motor speed variable is the one being manipulated across time. the default speed is a constant that will make sure the boat doesnt go crazy
Servo esc;
int motor_speed = 60;
const int defaultSpeed = 60;
float speed_scalar;

//Servo motor its angle and its output which is mapped between -40 and 40
Servo servo;
int motor_angle;
float servo_output;
float function_angle = 0;
//the distance between x and x1 when calculating direction lower values will have a more accurate slope but higher values will be better for the boats length on the curve
float boat_scalar = 0.1; 

//Variables for the points that follow the line and form a right triangle
float px, py;
float qx, qy;
float rx, ry;


float t = 0;  // this value is the value that drives the boat along within the parametric function

void setup() {
  esc.attach(3, 1000, 2000);  //attach the esc to pin D3 on the arduino nano and that set the min max for the PWM signal. (1000 and 2000 are placeholders) our esc is 8000-16000 perchance
  servo.attach(9, 1000, 2000);

  InitialSpeedBoost(2,3);
}

void loop() {

  //this maps the angle we get from the graph and translates it into the angle we need for the turn (I think this will work but I have no clue)
  function_angle = UpdateAngle();
  servo_output = map(function_angle, -90,90, -45,45);
  servo.write(servo_output);

  if(boosted) motor_speed = speed_scalar * defaultSpeed;
  esc.write(motor_speed);

  //makes sure that the boat doesnt rip into the infinite void of the wall
  AddTime(0.5);
  delay(500);
}

float UpdateAngle(){
  //point p
  px = CurveX(t - boat_scalar);
  py = CurveY(t - boat_scalar);

  //point q
  qx = CurveX(t + boat_scalar);
  qy = CurveY(t + boat_scalar);

  //point r
  rx = CurveX(t - boat_scalar);
  ry = CurveY(t + boat_scalar)


  //Create vector PR and calculate its magnitude the vertical stem of the triangle
  float vertical = Distance(px, py, rx, ry);

  //Create vector QR and calculate its magnitude the horizontal stem of the triangle
  float horizontal = Distance(qx, qy, rx, ry);

  //This creates the vector PQ which has a magnitude that gets smaller the steeper the slope is so this will be used to slow the boat down on sharp turns (hypotoneuse)
  speed_scalar = Distance(px, py, qx, qy);

  //Calculate the angle measured
  return atan(vertical / horizontal);
}
//this will give our boat an intial speed for a short time to avoid getting run into
bool boosted = false;
void InitialSpeedBoost(float scalar, float seconds){
    motor_speed *= scalar;
    delay(seconds * 1000);
    motor_speed /= scalar;
    boosted = true;
}

float Distance(float x1, float y1, float x2, float y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
//We can enter any parametric function into here!
//including a circle which would just be rcos(t) and rsin(t)
float CurveX(int t) {
  return t;
}
float CurveY(int t) {
  return -0.1(t * t);
}

void AddTime(float val = 1) {
  t += val;
  //Every Half Second the t value will prgress by 1
  // delay(500);
}
