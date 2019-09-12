int RED=2;
int YELLOW=3;
int GREEN=4;
void setup() {
  pinMode(RED,OUTPUT);
  digitalWrite(RED,LOW);
  pinMode(YELLOW,OUTPUT);
  digitalWrite(YELLOW,LOW);
  pinMode(GREEN,OUTPUT);
  digitalWrite(GREEN,LOW);
  // put your setup code here, to run once:

}

void loop() {
  
  digitalWrite(RED,HIGH);
  delay(2000);
  digitalWrite(RED,LOW);
  
  digitalWrite(GREEN,HIGH);
  delay(2000);
  digitalWrite(GREEN,LOW);
  
  digitalWrite(YELLOW,HIGH);
  delay(2000);
  digitalWrite(YELLOW,LOW);
  
  // put your main code here, to run repeatedly:

}
