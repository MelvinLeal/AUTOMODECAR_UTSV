#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif


#include <Servo.h>
#include <math.h>
#include <ros.h>
#include <std_msgs/Float64.h>

int PINSERVO = 2;
int PULSOMIN = 500;
int PULSOMAX = 2500;
int input_d = 90;

ros::NodeHandle  nh;

Servo servo;

int rad_to_deg(float rad){
float deg = rad *180/PI;
return round(deg);
}

int fix_degree(int value){
 if(value> 45) value = 45;
  if(value<-45) value = -45;
  value = 90 + value;
  return value;
}

void servo_cb( const std_msgs::Float64& cmd_msg){
  input_d = fix_degree(rad_to_deg(cmd_msg.data));
  servo.write(input_d);
}

ros::Subscriber<std_msgs::Float64> sub("/steering", servo_cb);
void setup(){
  pinMode(13, OUTPUT);
  servo.attach(PINSERVO,PULSOMIN,PULSOMAX);
  servo.write(input_d);
  nh.initNode();
  nh.subscribe(sub);
  
  servo.attach(2);  //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}

