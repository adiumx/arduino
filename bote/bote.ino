#include <Servo.h>
Servo servoInstance;
int ang;
int increasing=1;

int TRIG =10;
int ECO=9;
int LED=3;
int DURACION;
int DISTANCIA;
void setup() {
  //servoInstance.attach(3);
  //Serial.begin(9600);
  

  

  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  pinMode(LED, OUTPUT);
  
}

void loop() {
  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  DURACION=pulseIn(ECO, HIGH);
  DISTANCIA=DURACION/58.2;
  //Serial1.println(DISTANCIA);
  if(DISTANCIA<10){
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
  
  //servoInstance.write(170);
  
  
  
  delay(200);
  /*if(DISTANCIA<=20&&DISTANCIA>0){ 
    servoInstance.write(180);
    delay(200);
  }
  if(DISTANCIA>20){
    servoInstance.write(1);
    delay(200);
  }*/
  
  //delay(10);
}
