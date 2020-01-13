#include <C:\Users\Joshua Hooks\Documents\Arduino\libraries\Pixy2\Pixy2.h> 
#include <Servo.h>

Pixy2 cam; 
Servo servo;
int timeout = 0;
bool toggled = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Serial Communication...");
  pinMode(52,INPUT_PULLUP);
  cam.init();

  int8_t result = cam.changeProg("line");

  if (result == 0) {Serial.println("Pixy program successfully changed to \"line\".");}
  else             {Serial.println("ERROR: Could not change Pixy program to \"line\"!");}

  servo.attach(2); 
  servo.write(90);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  uint8_t x;
  uint8_t y;
 
  
  cam.line.getAllFeatures();
  if(digitalRead(52) == LOW && !toggled){
     servo.write(10);
     timeout =0; 
     toggled = true;
  }
  if(toggled&&digitalRead(52) == HIGH){  
    toggled = false;
    servo.write(90);
  }
  
  if(cam.line.barcodes){
    Serial.println("Barcode Detected");

    x = cam.line.barcodes->m_x;
    y = cam.line.barcodes->m_y;

    
    if(( abs((cam.frameWidth/2)-x)< 5  && abs((cam.frameHeight/2)-y)< 5)){

      Serial.println("In Target Area");

      if(timeout >= 3) {  
       servo.write(10);
       timeout = 0;

       while (1) {
         digitalWrite(11,HIGH);
         delay(100);
         digitalWrite(11,LOW);
         delay(100);
         digitalWrite(13,HIGH);
         delay(100);
         digitalWrite(13,LOW);
         delay(100);
       }
      }
      else {
        timeout++;
      }
    }
  }
  else {
    Serial.println("No Barcodes Detected"); 
  }
 
  delay(1000);
}
