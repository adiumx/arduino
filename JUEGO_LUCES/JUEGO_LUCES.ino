int PULSADOR1=6;
int PULSADOR2=7;
int PULSADOR3=8;
int PULSADOR4=9;
int LED1=2;
int LED2=3;
int LED3=4;
int LED4=5;
int VALOR1=LOW;
int VALOR2=LOW;
int VALOR3=LOW;
int VALOR4=LOW;
boolean C1=false;
boolean C2=false;
boolean C3=false;
boolean C4=false;
int count=0;
void secuencia();
void reset();
void gO();
void revisar(int b);
int s[10],a=0,b=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PULSADOR1, INPUT);
  pinMode(PULSADOR2, INPUT);
  pinMode(PULSADOR3, INPUT);
  pinMode(PULSADOR4, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
   Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  count=0;
  for(int i=0;i<4;i++){
    secuencia();
    a++;
    delay(1000);
    
  }
  reset();
  
  
  while(digitalRead(PULSADOR1)!=HIGH && digitalRead(PULSADOR2)!=HIGH && digitalRead(PULSADOR3)!=HIGH && digitalRead(PULSADOR4)!=HIGH);
 
  do{
  
    if((digitalRead(PULSADOR1)==HIGH)){
      VALOR1=1;
    }
  
    if(VALOR1==HIGH && digitalRead(PULSADOR1)==LOW ){
    C1=!C1; 
    revisar(1);
      count++; 
      digitalWrite(LED1, C1);
      
      VALOR1=0;
    }
      
    
   
  
  
   if((digitalRead(PULSADOR2)==HIGH)){
      VALOR2=1;
    }
    if(VALOR2==HIGH && digitalRead(PULSADOR2)==LOW ){
      C2=!C2; 
      revisar(2);
        count++; 
        digitalWrite(LED2, C2);
        
        VALOR2=0;
      }
  
  if((digitalRead(PULSADOR3)==HIGH)){
    VALOR3=1;
  }
  if(VALOR3==HIGH && digitalRead(PULSADOR3)==LOW ){
    C3=!C3; 
    revisar(3);
      count++; 
      digitalWrite(LED3, C3);
      
      VALOR3=0;
    }
  
 if((digitalRead(PULSADOR4)==HIGH)){   
    VALOR4=1;  
  }
  if(VALOR4==HIGH && digitalRead(PULSADOR4)==LOW ){
    C4=!C4; 
    revisar(4);
      count++; 
      digitalWrite(LED4, C4);
      
      VALOR4=0;
    }
  
    
  }while(count<a);
  delay(2000);
  gO();
  reset();
  delay(500);
  gO();
  reset();
  a=0;
  delay(1000);
}
void secuencia(){
  int i;
    i = random(1,4);
    switch (i){
      case 1:
        digitalWrite(LED1, !C1);
        C1=!C1;
        s[a]=1;
        
        break;
      case 2:
        digitalWrite(LED2, !C2);
        C2=!C2;
        s[a]=2;
        
        break;
      case 3:
        digitalWrite(LED3, !C3);
        C3=!C3;
        s[a]=3;
        
        break;
      case 4:
        digitalWrite(LED4, !C4);
        C4=!C4;
        s[a]=4;
        
        break;
    }
}
void reset(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  C1=false;
  C2=false;
  C3=false;
  C4=false;
  
}
void gO(){
        
        digitalWrite(LED1, true);
       
        digitalWrite(LED2, true);
       
        digitalWrite(LED3, true);
        
        digitalWrite(LED4, true);
    delay(1000);
}
void revisar(int b){
  
    if(s[count]!=b){
      gO();
      count=a;
    }
  
}
