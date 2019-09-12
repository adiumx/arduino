int RED=9;
int GREEN=10;
int BLUE=11;

void setup() {
  // put your setup code here, to run once:
pinMode(RED,OUTPUT);
pinMode(GREEN,OUTPUT);
pinMode(BLUE,OUTPUT);

}

void loop() {
  for(int i=0;i<500;i++){
    digitalWrite(RED,HIGH);
    delay(.25);
    digitalWrite(RED,LOW);
    delay(1.75);
  }
 delay(500);
}
