//This is an example of how you would control 1 stepper
 
#include <AccelStepper.h>
#include <NewPing.h>
 
#define TRIGGER_PIN  20  //A2
#define ECHO_PIN     21  //A3
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define motorEnablePin 7
#define motorDirPin 18
#define motorStepPin 19
#define endSwitchPin 16

#define btn_on 5
#define btn_on_gnd 6

#define btn_off 8
#define btn_off_gnd 9

#define motor_power 2

#define led_gnd 14
#define led 15
#define led_delay_fast 1000 //in pizza´s (yes, diy units)
#define led_delay_slow 10000 //in pizza´s (yes, diy units)

int motorSpeed = 500; //maximum steps per second
int motorAccel = 10000; //steps/second/second to accelerate
int stepwidth = 20; //set stepwidth in degrees
int currentposition = 0;
int distance = 0;
unsigned int uS = 0;
int led_state = 0;
int led_counter = 0;
int enabled = false;
 
volatile int state = LOW;  
 
//set up the accelStepper intance
//the "1" tells it we are using a motor controller
AccelStepper stepper(1, motorStepPin, motorDirPin); 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void blink(){
	if (led_state == 0){
		 		digitalWrite(led, HIGH);
				led_counter++;
				if (led_counter >= led_delay_fast){
				led_counter = 0;
				led_state = 1;
				}
		 	}
		 	else if (led_state == 1){
				digitalWrite(led, LOW);
		 		led_counter++;
		 		if (led_counter >= led_delay_fast){
				led_counter = 0;
				led_state = 2;
				}
		 	}
		 	else if (led_state == 2){
		 		digitalWrite(led, HIGH);
		 		led_counter++;
		 		if (led_counter >= led_delay_fast){
				led_counter = 0;
				led_state = 3;
				}
		 	}
		 	else if (led_state == 3){
				digitalWrite(led, LOW);
		 		led_counter++;
		 		if (led_counter >= led_delay_slow){
				led_counter = 0;
				led_state = 0;
				}
		 	}
}
 
void setup(){
 Serial.begin(9600);

 pinMode(endSwitchPin, INPUT_PULLUP);
 pinMode(10, OUTPUT);  
 digitalWrite(10, LOW);

 pinMode(led_gnd, OUTPUT);  
 digitalWrite(led_gnd, LOW);
 pinMode(led, OUTPUT);  

 pinMode(btn_off_gnd, OUTPUT);
 digitalWrite(btn_off_gnd, LOW);
 pinMode(btn_off, INPUT_PULLUP);

 pinMode(btn_on_gnd, OUTPUT);
 digitalWrite(btn_on_gnd, LOW);
 pinMode(btn_on, INPUT_PULLUP);

 pinMode(motor_power, INPUT);

 stepper.setMaxSpeed(motorSpeed);
 stepper.setSpeed(motorSpeed);
 stepper.setAcceleration(motorAccel);
 
 stepper.moveTo(2000); //go to the endswitch
}
 
void loop(){
	if (enabled){
		 //if stepper is at desired location
		 if (stepper.distanceToGo() == 0)
		 {
		  //go from -180deg to +180deg and from +180deg to -180deg
		  stepper.moveTo(-stepper.currentPosition()); 
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

		 	currentposition = stepper.currentPosition();
		 	if (((currentposition / 2 ) % stepwidth) == 0) //run if currentposition is on the stepwidth
		 	{
		 		uS = sonar.ping(); // Send ping, get ping time in microseconds (uS). 29ms should be the shortest delay between pings.
		 		//stepper.stop();
				//delay(20);
				//stepper.run();
				Serial.print("{");
				Serial.print( ( currentposition + 230 ) / 2); //send angle
				Serial.print(",");
				Serial.print(uS / US_ROUNDTRIP_CM); //send distance in cm (0 = outside set distance range)
				Serial.println("}");
		 	} 
		 }

		 if (digitalRead(btn_off) == LOW || digitalRead(motor_power) == LOW){
    		enabled = false;
    	}
    	blink();
    }
    else{
    	if (digitalRead(btn_on) == LOW && digitalRead(motor_power) == HIGH){
    		state = LOW;
    		enabled = true;
    		stepper.moveTo(2000); //go to the endswitch
    		digitalWrite(motorEnablePin, LOW);
    	}
    	else{
    		digitalWrite(motorEnablePin, HIGH);
    	}
    }
}