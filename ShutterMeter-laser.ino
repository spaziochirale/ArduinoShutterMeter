/***************************************************
 *    SHUTTER METER PROTOTYPE
 *    
 *    Author: Spazio Chirale
 *    Version: 1.0
 *    Chinese cheap laser pointer always on and laser sensor on PIN 2 Arduino UNO
 *    
 */

volatile int shutterClose=0;
volatile int shutterOpen=0;
volatile unsigned long now, tOpen, tClose, elapsed;

// ISR
void shutterEvent(){
  now=micros();
  if(digitalRead(2)) shutterClose=1;
  else shutterOpen=1;
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), shutterEvent, CHANGE);

}

void loop() {
  if (shutterOpen) {
  tOpen=now;
  shutterOpen=0;
}
if (shutterClose) {
  tClose=now;
  shutterClose=0;
  elapsed = tClose - tOpen;
  Serial.print("Shutter fired, duration: ");
  Serial.println(elapsed);
  Serial.print("Shutter speed: ");
  if (elapsed < 1000000) {
    Serial.print("1/");
    Serial.print(1000000/elapsed);
  }
  else Serial.print(float(elapsed)/1000000);
  Serial.println("sec.");
    
  
}
  

}
