#include <SharpIR.h>

// Telemetres_IR_AV
SharpIR telAv(SharpIR::GP2Y0A21YK0F, A1);

int Dist_AV;

void setup() {
  Serial.begin(115200);
}

void loop() 
{  
  Dist_AV = telAv.getDistance();
  Serial.println(Dist_AV);
  delay(100);
}

/*#define sensor A1 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  Read = analogRead(A0); // lectura del sensor 0
  cm = pow(3027.4 / Read, 1.2134);
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
    delay(300); // slow down serial port
   
  Serial.print("volts : ");
  Serial.println(volts);
  
  if (distance <= 30){
    Serial.print("distance");
    Serial.println(distance);   // print the distance
  }
}*/
