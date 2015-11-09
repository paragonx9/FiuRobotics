const double r_Long = 1; 
const double l_Long = 1;
const double m_Long = 0;
const int middleSensor = 1;
const int rightSensor = 2;
const int leftSensor = 0;
//Sets pins for the motor's speed and direction
const int leftMotorDirectionPin = 4;
const int leftMotorSpeedPin = 5;

const int rightMotorDirectionPin = 7;
const int rightMotorSpeedPin = 6;

const int r_threshhold = 6;
const int l_threshhold = 6;
const int m_threshhold = 6;
void setup (){
  
}
int turnSpeed = 100;
int threshhold = 3;

//void loop(){
//  if(readSensor("middle") == false){
//   while(readSensor("middle") == false){
//     backwards(100);
//     delay(100);
//  }
//  if(readSensor("right") <  readSensor("left")){
//    turnLeft(100);
//    delay(100);
//  }else if(readSensor("right") >  readSensor("left")){
//    turnRight(100);
//    delay(100);  
//  }
//  }else{
//   forward(150);
//  delay(100); 
//  }
//  
//}
void loop (){
  turnLeft(100);
}



const int readSensor(String c){
  if(c.equalsIgnoreCase("right")){
    return (r_Long)*(2076/(analogRead(rightSensor)-11)) - r_threshhold > 0 ? (r_Long)*(2076/(analogRead(rightSensor)-11)) : 0 + (1-r_Long)*(analogRead(rightSensor) > 400 ? 1 : 0);
  }else if(c.equalsIgnoreCase("left")){
    return (l_Long)*(2076/(analogRead(leftSensor)-11)) - l_threshhold > 0 ? (l_Long)*(2076/(analogRead(leftSensor)-11)) : 0 + (1-l_Long)*(analogRead(leftSensor) > 400 ? 1 : 0);
  }else if (c.equalsIgnoreCase("middle")){
    return (m_Long)*(2076/(analogRead(middleSensor)-11)) - m_threshhold > 0 ? (m_Long)*(2076/(analogRead(middleSensor)-11)) : 0 + (1-m_Long)*(analogRead(middleSensor) > 400 ? 1 : 0);
  }
 }

void turnRight(int s)
{
  setSpeed("right",-s);
  setSpeed("left", s);
}
void turnLeft(int s)
{
  setSpeed("right",s);
  setSpeed("left", -s);
}
void forward(int s)
{
  setSpeed("right",s);
  setSpeed("left", s);
}
void backwards(int s)
{
  setSpeed("right",-s);
  setSpeed("left", s);
}
void stopAll()
{
  setSpeed("right",0);
  setSpeed("left", 0);
}



//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                          // Set Speed Function and Followall Function
void setSpeed(String c, int s){
  if(c.equalsIgnoreCase("right")) 
  {
    if(s < 0) 
    {
     analogWrite(rightMotorSpeedPin, s);
      digitalWrite(rightMotorDirectionPin, LOW);
    }
    else 
    {
     analogWrite(rightMotorSpeedPin, s);  
      digitalWrite(rightMotorDirectionPin, HIGH);}
    }else{
    if(s < 0) {
     analogWrite(leftMotorSpeedPin, s);
      digitalWrite(leftMotorDirectionPin, HIGH);
    }else {
      analogWrite(leftMotorSpeedPin, s);
      digitalWrite(leftMotorDirectionPin, LOW);
    }  
}
}

void followWall(int distance, int v, String side)
{
  String oppSide = "";
  int sensorVal = readSensor("right");
  if(side.equalsIgnoreCase("right")) oppSide = "left";
  else oppSide = "right";
  
  if(sensorVal - distance < 0){
    setSpeed(oppSide, v + turnSpeed);
    setSpeed(side, v - turnSpeed); 
  }else if(sensorVal  - distance > 0 ){
   setSpeed(oppSide, v - turnSpeed  );
   setSpeed(side, v + turnSpeed); 
  }
else{
   setSpeed(oppSide, v);
   setSpeed(side, v); 
  }}
