//send (emulated) radar data to pc

 int delay_ms = 50; //delay after each step
 int step_size = 72; //steps in 360deg

void setup()
{
	Serial.begin(9600);
}

void loop()
{
   for (int deg=0; deg <= 360-(360/step_size); deg=deg+(360/step_size))
   {
      Serial.print("{"); //object at a distance of 50cm
      Serial.print(deg); //object at a distance of 50cm
      Serial.println(",50}"); //object at a distance of 50cm
      delay(delay_ms);
   } 
   for (int deg=360; deg >= 360/step_size; deg=deg-(360/step_size))
   {
      Serial.print("{"); //object at a distance of 50cm
      Serial.print(deg); //object at a distance of 50cm
      Serial.println(",100}"); //object at a distance of 50cm
      delay(delay_ms);
   } 
} 