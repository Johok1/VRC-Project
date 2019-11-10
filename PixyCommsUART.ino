
/*
 * The goal of this program is to simply establish and verify communication with the Pixy2 camera via UART 
 * 
 * @author Joshua Hooks
 */

#include <C:\Users\joshua hooks\Documents\Arduino\libraries\Pixy2\Pixy2UART.h>

Pixy2UART cam;


void setup() {
  Serial.begin(115200);
  Serial.print("Starting...\n");
  cam.init();

}

//To run repeatedly
void loop() {
 cam.ccc.getBlocks();
 if(cam.ccc.numBlocks){
  Serial.print("Detected "); 
  Serial.println(cam.ccc.getBlocks());
 }
  delay(2000);
} 
