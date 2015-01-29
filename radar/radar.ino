//This is an example of how you would control 1 stepper
 
#include <AccelStepper.h>
 
int motorSpeed = 600; //maximum steps per second (about 3rps / at 16 microsteps)
int motorAccel = 10000; //steps/second/second to accelerate
 
int motorDirPin = 14;
int motorStepPin = 15;
int endSwitchPin = 16;
volatile int state = LOW;  
 
//set up the accelStepper intance
//the "1" tells it we are using a driver
AccelStepper stepper(1, motorStepPin, motorDirPin); 
 
 
 
void setup(){
 pinMode(10, OUTPUT);  
 pinMode(endSwitchPin, INPUT_PULLUP);
 digitalWrite(10, LOW); //use pin 10 as ground
 stepper.setMaxSpeed(motorSpeed);
 stepper.setSpeed(motorSpeed);
 stepper.setAcceleration(motorAccel);
 
 stepper.moveTo(2000); //move 32000 steps (should be 10 rev)
}
 
void loop(){
	if (1){
		 //if stepper is at desired location
		 if (stepper.distanceToGo() == 0)
		 {
		  //go the other way the same amount of steps
		  //so if current position is 400 steps out, go position -400
		  stepper.moveTo(-stepper.currentPosition()); 
		 }
		}
	 if (digitalRead(endSwitchPin) == LOW && state==LOW)
	 {
	 	stepper.stop();
	 	stepper.setCurrentPosition(0);
	 	stepper.moveTo(-450); //-730 steps is 360deg  140 steps up/down
	 	while(stepper.distanceToGo() != 0)
	 	{
	 		stepper.run();
	 	}
	 	stepper.setCurrentPosition(0);
	 	stepper.moveTo(-140);
	 	state=HIGH;
	 }
	 else
	 {
	 	stepper.run(); //these must be called as often as possible to ensure smooth operation any delay will cause jerky motion
	 }
}