
int RedLedPin =12;
int GreenLedPin =13; 
const int SpeakerPin =11;
int inPin = 2; 
int reading;
void setup() {
  pinMode (inPin,INPUT);
  pinMode (GreenLedPin,OUTPUT);
  pinMode (RedLedPin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  reading = digitalRead(inPin);
  if (reading == 1){
  digitalWrite(RedLedPin,HIGH);
  digitalWrite(GreenLedPin,LOW);
  tone(SpeakerPin, 392, 1000);
  delay(500); 
  tone(SpeakerPin, 440, 500);
  delay(500); 
  tone(SpeakerPin, 392, 500);
  delay(500); 
  tone(SpeakerPin, 329  , 1000);
  delay(1000);
  tone(SpeakerPin, 392, 500);
  delay(500); 
  tone(SpeakerPin, 440, 500);
  delay(500); 
  tone(SpeakerPin, 392, 500);
  delay(500); 
  tone(SpeakerPin, 329  , 1000);
  delay(1000);
  tone(SpeakerPin, 587  , 500);
  delay(500); 
  tone(SpeakerPin, 587, 500);
  delay(500); 
  tone(SpeakerPin, 493, 1000);
  delay(1000); 

  tone(SpeakerPin, 523  , 500);
  delay(500); 
  tone(SpeakerPin, 523, 500);
  delay(500); 
  tone(SpeakerPin, 392, 1000);
  delay(1000); 

  tone(SpeakerPin, 440  , 500);
  delay(500); 
  tone(SpeakerPin, 440, 500);
  delay(500); 
  tone(SpeakerPin, 523, 500);
  delay(500);
  tone(SpeakerPin, 493  , 500);
  delay(500); 
  tone(SpeakerPin, 440, 500);
  delay(500); 

  tone(SpeakerPin, 392, 1000);
  delay(500); 
  tone(SpeakerPin, 440, 500);
  delay(500); 
  tone(SpeakerPin, 392, 500);
  delay(500); 
  tone(SpeakerPin, 329  , 1000);
  delay(1000);    
  }else{
    digitalWrite(RedLedPin,LOW);
    digitalWrite(GreenLedPin,HIGH);
  }
  Serial.println(reading);
  delay(200);
}
