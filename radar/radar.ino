//This is an example of how you would control 1 stepper
 
#include <AccelStepper.h>
 
int motorSpeed = 500; //maximum steps per second
int motorAccel = 10000; //steps/second/second to accelerate
 
int motorDirPin = 14;
int motorStepPin = 15;
int endSwitchPin = 16;
volatile int state = LOW;  
 
//set up the accelStepper intance
//the "1" tells it we are using a motor controller
AccelStepper stepper(1, motorStepPin, motorDirPin); 
 
 
 
void setup(){
 pinMode(10, OUTPUT);  
 pinMode(endSwitchPin, INPUT_PULLUP);
 digitalWrite(10, LOW); //use pin 10 as ground
 stepper.setMaxSpeed(motorSpeed);
 stepper.setSpeed(motorSpeed);
 stepper.setAcceleration(motorAccel);
 
 stepper.moveTo(2000); //go to the endswitch
}
 
void loop(){
	if (1){
		 //if stepper is at desired location
		 if (stepper.distanceToGo() == 0)
		 {
		  //go from -180deg to +180deg and from +180deg to -180deg
		  stepper.moveTo(-stepper.currentPosition()); 
		 }
		}
	 if (digitalRead(endSwitchPin) == LOW && state==LOW) //if stepper is at endswitch
	 {
	 	stepper.stop();
	 	stepper.setCurrentPosition(0);
	 	stepper.moveTo(-430); //
	 	while(stepper.distanceToGo() != 0)
	 	{
	 		stepper.run();
	 	}
	 	stepper.setCurrentPosition(0); //set new null position
	 	stepper.moveTo(-360); //rotate 360 steps to left (180deg)
	 	state=HIGH;
	 }
	 else
	 {
	 	stepper.run(); //these must be called as often as possible to ensure smooth operation any delay will cause jerky motion
	 }
}