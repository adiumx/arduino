int RED=9;
int GREEN=10;
int BLUE=11;
int i=0;
void setup() {
  // put your setup code here, to run once:
pinMode(RED,OUTPUT);
pinMode(GREEN,OUTPUT);
pinMode(BLUE,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //naranja
  analogWrite(RED,255);
  analogWrite(GREEN,124);
  analogWrite(BLUE,0);
  delay(2000);
  //amarillo
  analogWrite(RED,255);
  analogWrite(GREEN,255);
  analogWrite(BLUE,0);
  delay(2000);
  
}
