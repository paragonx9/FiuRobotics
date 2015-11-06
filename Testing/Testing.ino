                                                                                         // Declarations
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

const char r = 'r';
const char l = 'l';

//Sets readSensor as an action
const int readSensor(String c){
  if(c.equalsIgnoreCase("right")){
    return (r_Long)*(2076/(analogRead(rightSensor)-11)) + (1-r_Long)*(analogRead(rightSensor) > 400 ? 1 : 0);
  }else if(c.equalsIgnoreCase("left")){
    return (l_Long)*(2076/(analogRead(leftSensor)-11)) + (1-l_Long)*(analogRead(leftSensor) > 400 ? 1 : 0);
  }else if (c.equalsIgnoreCase("middle")){
    return (m_Long)*(2076/(analogRead(middleSensor)-11)) + (1-m_Long)*(analogRead(middleSensor) > 400 ? 1 : 0);
  }
 }

const byte turnSpeed = 100;

//I don't know what this does...
void setup()
{
  Serial.begin(9600);
  for(int i = 4; i < 8; i++)
	{pinMode(i, OUTPUT);}
}




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                    // Voidloop Area



void loop()
{
  int sensorVal = readSensor("middle"); 
  if (sensorVal == 1)
  {
    followMyWall(100, "right");         // Used to be "forward(100);"
  }
  else if (sensorVal == 0)
  {
    stopAll();                         // Used to be "followMyWall(100, "right");"
  }      
}





//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                        // FollowMyWall Function 
void followMyWall(int v, String side)
{
  int distanceFromWall = 5;    // units in cm
  String oppSide = "";
  int rsensorVal = readSensor("right");
  int lsensorVal = readSensor("left");
  if(side.equalsIgnoreCase("right")) oppSide = "left";
  else oppSide = "right";
  
  
  if(rsensorVal - distanceFromWall - 1 < 0 && lsensorVal - distanceFromWall - 1 > 0)
  {
    setSpeed(oppSide, v ); 
    setSpeed(side, v + turnSpeed);  
  }
  else if (rsensorVal - distanceFromWall - 1 > 0 )
  {
    forward(100);  
  }
  
  
  if(lsensorVal - distanceFromWall - 1 < 0 && rsensorVal - distanceFromWall - 1 > 0)
  {
    setSpeed(oppSide, v + turnSpeed); 
    setSpeed(side, v );  
  }
  else if (lsensorVal - distanceFromWall - 1 > 0 )
  {
   forward(100);  
  }  
}  


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                        // Sensingfront Function
void sensingFront()
{
  int sensorVal = readSensor("middle"); 
  if (sensorVal == 1)
  {
    forward(150);
  }
  else (sensorVal == 0);
  {
    stopAll();
  }
} 



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                  // Turning Function
void turningFunction()
{
	int sensorVal = readSensor("middle");
	if (sensorVal == 0)
	{
		stopAll();

		//int rsensorVal = readSensor ("right");
		//int lsensorVal = readSensor ("left");
		//if (rsensorVal > lsensorVal)
		//{
			//turnRight(255);
			//while(readSensor("left") > 5)
			//{
				//followWall(5, 255, "left");
			//}
		}
		//else if (rsensorVal < lsensorVal)
		//{
			//turnLeft(255);
			//while(readSensor("left") > 5)
			//{
				//followWall(5, 255, "left");
			//}
		//} 

	//}
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                     // Basic Movement
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
  }
}
