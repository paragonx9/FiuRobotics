#include <PID_v1.h>

const int middleSensor = 1;
const int rightSensor = 2;
const int leftSensor = 0;


/* 
 *if 1 sensor is long range,
 *if 0 sensor is short range.
*/

const double r_Long = 1; 
const double l_Long = 1;
const double m_Long = 0;

//Sets pins for the motor's speed and direction

const int leftMotorDirectionPin = 4;
const int leftMotorSpeedPin = 5;

const int rightMotorDirectionPin = 7;
const int rightMotorSpeedPin = 6;

double distanceFromWall = 4; //in centimeters
double distanceReading; //sensor Reading in centimeters
double motorSpeed; //value to be changed 
double Kp = 5;
double Ki = 0;
double Kd = 2;
PID  pd(&distanceReading, &motorSpeed, &distanceFromWall, Kp, Ki, Kd, DIRECT);
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
Serial.begin(9600);
pd.SetMode(AUTOMATIC);
pd.SetSampleTime(100);
pd.SetOutputLimits(-75, 75);
}

void loop() {
  // put your main code here, to run repeatedly:
distanceReading = readSensor("Right");

pd.Compute();
Serial.print("MotorSpeed: " );
Serial.print(motorSpeed );
Serial.print(" DistanceReading: " );
Serial.println(distanceReading);
followWall();
}

void followWall(){
   setSpeed("right", (175+ motorSpeed));
 setSpeed("left", ( 175- motorSpeed));
}


void followWallAndTurn(){
if(readSensor("middle") == 1){ //if the front sensor senses a wall turn...
  digitalWrite(13, HIGH);
  if(readSensor("right") < readSensor("left"))//if the distance is bigger on the right than on the left turn right..... else turn left
  {
 setSpeed("right", (175+ motorSpeed));
 setSpeed("left", ( 100- motorSpeed));
  }else //turn left
  {
    setSpeed("right", (100+ motorSpeed));
  setSpeed("left", ( 175- motorSpeed));
  }
}else{ // if no wall is sense keep going forward
  digitalWrite(13, LOW);
 setSpeed("right", (100+ motorSpeed));
 setSpeed("left", ( 100- motorSpeed));
}

  
}




int readSensor(String c){
  if(c.equalsIgnoreCase("right")){
    return (r_Long)*(2076/(analogRead(rightSensor)-11)) + (1-r_Long)*(analogRead(rightSensor) > 400 ? 1 : 0);
  }else if(c.equalsIgnoreCase("left")){
    return (l_Long)*(2076/(analogRead(leftSensor)-11)) + (1-l_Long)*(analogRead(leftSensor) > 400 ? 1 : 0);
  }else if (c.equalsIgnoreCase("middle")){
    return (m_Long)*(2076/(analogRead(middleSensor)-11)) + (1-m_Long)*(analogRead(middleSensor) > 400 ? 0 : 1);
  }
 }

 void setSpeed(String c, int s){
  if(c.equalsIgnoreCase("right")) {
    if(s < 0) {
     analogWrite(rightMotorSpeedPin, s);
      digitalWrite(rightMotorDirectionPin, LOW);
    }else {
     analogWrite(rightMotorSpeedPin, s);  
      digitalWrite(rightMotorDirectionPin, HIGH);
  }}else{
    if(s < 0) {
     analogWrite(leftMotorSpeedPin, s);
      digitalWrite(leftMotorDirectionPin, HIGH);
    }else {
      analogWrite(leftMotorSpeedPin, s);
      digitalWrite(leftMotorDirectionPin, LOW);
    }  
}
}
