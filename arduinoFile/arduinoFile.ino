#include <Servo.h>

Servo esc;
int motor_speed;

Servo servo;
int motor_angle;

//Variables for drive
float x=0,y=0;
float current_angle;

float t_time = 0; // this value is the value that drives the boat along within the functions

float angle_error = 0;

void setup() {
  // put your setup code here, to run once:
  esc.attach(3, 1000,2000); //attach the esc to pin D3 on the arduino nano and that set the min max for the PWM signal. (1000 and 2000 are placeholders) our esc is 8000-16000
  servo.attach(9,1000, 2000);
}

void loop() {
  //Steps to drive boat without gyroscope

  //update x and y positions
  x = CurveX(t_time);
  y= CurveY(t_time);
  //Gather tangent vector of the boat

  //Gather real position of boat


  //Determine angle of measure and adjust the boat acordingly
  angle_error = GatherError();

  //adjust the angle of the servo i dont know by how much or what the error margin should be but Ill figure it out later.
  if(angle_error > 3){
    //turn right?
  }else{
    //turn left?
  }

  AddTime(0.5);

  //makes sure that the boat doesnt rip into the infinite void of the wall
  delay(500);
}

float CurveX(int t){
  return t;
}
float CurveY(int t){
  return -0.1(t*t);
}

void AddTime(float val = 1){
  t_time += val;
  //Every Half Second the t value will prgress by 1
  // delay(500);
}

float GatherError(float tangent, float realDis, float err){

}
