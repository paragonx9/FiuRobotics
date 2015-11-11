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

const int r_threshhold = 8;
const int l_threshhold = 8;
const int m_threshhold = 6;
void setup (){
  Serial.begin(9600);
}
int tSpeed = 75;
int tDelay = 100;

int turnSpeed = 100;
void loop (){
firstPartV2();
Serial.println(readSensor("middle"));
}
int counter = 0;

void firstPartV2(){
  if(readSensor("middle") == true && (readSensor("left") > readSensor("right") || readSensor("left") == 0)) turnLeftUntil(150, 100, "middle", true, 375);
 else if (readSensor("middle") == true && (readSensor("right") > readSensor("left") || readSensor("right") ==  0))turnRightUntil(150, 100, "middle", true, 375);
 else if (readSensor("left") > 0){
   stopAll();
   delay(300);
  turnRight(100);
 delay(100); 
 }
 else if (readSensor("right") > 0){
   stopAll();
   delay(300);
  turnLeft(100);
 delay(100); 
 }
 else{
 forward(100);
 delay(100);
 }
 
 
  
  
}






void firstPart(){
    if(readSensor("middle") == true){
      backwards(100);
      delay(100);
   while(readSensor("middle") == true){
     turnLeft(100);
     delay(100);
     counter++;
     if(counter > 10){
        while(counter > 0){
        
        delay(100);
        }
        break;        
     }
  }
    
  if(readSensor("left") == false){}
  else {
    while(readSensor("middle") == false){
        turnRight(100);
        delay(100);
    }
       while(readSensor("middle") == true){
     turnRight(100);
     delay(100);
  }
  
  }
    }else{
      forward(100); 
      delay(100);}
}

const int readSensor(String c){
  int reading = 0;
  if(c.equalsIgnoreCase("right")){
    reading = (r_Long)*(2076/(analogRead(rightSensor)-11)) + (1-r_Long)*(analogRead(rightSensor));
    if(reading < r_threshhold && reading > 0) return reading;
    else return 0;
    //return (r_Long)*(2076/(analogRead(rightSensor)-11)) - r_threshhold > 0 ? (r_Long)*(2076/(analogRead(rightSensor)-11)) : 0 + (1-r_Long)*(analogRead(rightSensor) > 400 ? 1 : 0);
  }else if(c.equalsIgnoreCase("left")){
    reading = (l_Long)*(2076/(analogRead(leftSensor)-11)) + (1-l_Long)*(analogRead(leftSensor));
    if(reading < l_threshhold && reading > 0) return reading;
    else return 0;
  }else if (c.equalsIgnoreCase("middle")){
    reading = (m_Long)*(2076/(analogRead(middleSensor)-11)) + (1-m_Long)*(1 - analogRead(middleSensor)/1000);
    if(reading < m_threshhold && reading > 0) return reading;
    else return 0;
  }
 }


void turnLeftUntil(int s, int t, String sensor, boolean condition, int timeout){
  int sTime = millis();
  int cTime = 0;
 while(readSensor(sensor) == condition){
   cTime = millis();
   if(readSensor("left") < 7 && readSensor("left") > 0) {
   turnRightUntil(s, t, "middle", true, timeout);
   break; 
   }
  else if(cTime - sTime > timeout) {
    turnRightUntil(s, t, "middle", true, timeout);
   break; 
  }else{
  turnLeft(s);
  delay(t);
   }
 } 
}

void turnRightUntil(int s, int t, String sensor, boolean condition, int timeout){
  int sTime = millis();
  int cTime = 0;
 while(readSensor(sensor) == condition){
  turnRight(s);
  delay(t);
  cTime = millis();
//  if(cTime - sTime > timeout) {
//    turnRightUntil(100, 100, "middle", true, timeout);
//   //turnLeft(s);
//    //delay(timeout);
//   break; 
//  }
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
