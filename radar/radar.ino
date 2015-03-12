//This is an example of how you would control 1 stepper
 
#include <AccelStepper.h>
 
#define TRIGGER_PIN  20  //A2
#define ECHO_PIN     21  //A3
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define motorDirPin = 14;
#define motorStepPin = 15;
#define endSwitchPin = 16;

int motorSpeed = 500; //maximum steps per second
int motorAccel = 10000; //steps/second/second to accelerate
int stepwidth = 5; //set stepwidth in degrees
int currentposition = 0;
int distance = 0;
 
volatile int state = LOW;  
 
//set up the accelStepper intance
//the "1" tells it we are using a motor controller
AccelStepper stepper(1, motorStepPin, motorDirPin); 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
 
void setup(){
 Serial.begin(9600);
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

	 	currentposition = mystepper.currentPosition();
	 	if ((currentposition % stepwidth) == 0) //run if currentposition is on the stepwidth
	 	{
	 		unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS). 29ms should be the shortest delay between pings.
			Serial.print("{");
			Serial.print(currentposition); //send angle
			Serial.println(",");
			Serial.println(uS / US_ROUNDTRIP_CM); //send distance in cm (0 = outside set distance range)
			Serial.println("}");
	 	}
	 }
}