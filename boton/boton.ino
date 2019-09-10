#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
MIDI_CREATE_DEFAULT_INSTANCE();

/**
Alvaro Lopez Revuelta para http://geekytheory.com/
http://alvarorevuelta.net/

Este ejemplo es para ver en el monitor serial los botones pulsados/despulsados
En el siguiente ejemplo veremos como enviar midi
Ojo con usar mas de 11 botones empleando la resistencia de pullup interna
Para el pin 13 debe usarse una resistencia de pullup externa
*/

int TRIG =10;
int ECO=9;
int LED=3;
int DURACION;
int DISTANCIA;
int COUNT=0;
int COUNT1=0;
const int numBotones=24;       // Definir aqui el numero de botones (11 max)
int valorLeido[numBotones];    // Array con los valores leidos de cada boton
int valorAnterior[numBotones]; // Array con el valor anterior leido
int octava=0;
void setup() {
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  pinMode(LED, OUTPUT);
  
  //Serial1.begin(9600);
  MIDI.begin();  
  Serial.begin(115200); //Cambiamos la velocidad del puerto serie
  for(int i=0; i<numBotones; i++){
    pinMode(i+22, INPUT);       // Recorremos cada pin y lo ponemos como entrada
    valorAnterior[i]=0;        // Inicializamos el valor anterior a 1 (no pulsado)
  }
}

void loop(){
  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  DURACION=pulseIn(ECO, HIGH);
  DISTANCIA=DURACION/58.2;
  //Serial.println(DISTANCIA);
if(DISTANCIA<50){
   MIDI.sendControlChange (1, DISTANCIA*2, 1);
  // COUNT=1;
   //COUNT1=0;
  //}else if(DISTANCIA>20&&(DISTANCIA<30)&&(COUNT1!=1)){
    //MIDI.sendControlChange (1, DISTANCIA*2, 1);
    //COUNT1=1;
    //COUNT=0;
  } 
   //delay(200);
  for(int i=0; i<numBotones; i++){
    valorLeido[i]=digitalRead(i+22); // Leer valor
    // Solo enviamos cuando ha existido un cambio, para no sobrecargar el puerto serial
    if((valorLeido[i]==1) && (valorLeido[i]!=valorAnterior[i])){
     
      if(i==17){
        octava=octava-8;
        
      }
      if(i==21){
        octava=octava+8;
      }
      if(i==18){
        MIDI.sendNoteOn(50+octava, 127, 1);
      }
      if(i==22){
        MIDI.sendNoteOn(51+octava, 127, 1);
      }
      if(i==19){
        MIDI.sendNoteOn(52+octava, 127, 1);
      }
      if(i==20){
        MIDI.sendNoteOn(53+octava, 127, 1);
      }
      if(i==23){
        MIDI.sendNoteOn(54+octava, 127, 1);
      }
      if(i==0){
        MIDI.sendNoteOn(55+octava, 127, 1);
      }
      if(i==4){
        MIDI.sendNoteOn(56+octava, 127, 1);
      }
      if(i==1){
        MIDI.sendNoteOn(57+octava, 127, 1);
      }
      if(i==5){
        MIDI.sendNoteOn(58+octava, 127, 1);
      }
      if(i==2){
        MIDI.sendNoteOn(59+octava, 127, 1);
      }
      if(i==3){
        MIDI.sendNoteOn(60+octava, 127, 1);
      }
      if(i==6){
        MIDI.sendNoteOn(61+octava, 127, 1);
      }
      if(i==8){
        MIDI.sendNoteOn(62+octava, 127, 1);
      }
      if(i==7){
        MIDI.sendNoteOn(63+octava, 127, 1);
      }
      if(i==9){
        MIDI.sendNoteOn(64+octava, 127, 1);
      }
      if(i==10){
        MIDI.sendNoteOn(65+octava, 127, 1);
      }
      if(i==12){
        MIDI.sendNoteOn(66+octava, 127, 1);
      }
      if(i==11){
        MIDI.sendNoteOn(67+octava, 127, 1);
      }
      if(i==13){
        MIDI.sendNoteOn(68+octava, 127, 1);
      }
      if(i==14){
        MIDI.sendNoteOn(69+octava, 127, 1);
      }
      if(i==16){
        MIDI.sendNoteOn(70+octava, 127, 1);
      }
      if(i==15){
        MIDI.sendNoteOn(71+octava, 127, 1);
      }
      
    }
    else if ((valorLeido[i]==0) && (valorLeido[i]!=valorAnterior[i])){

      if(i==17){
        MIDI.sendNoteOff(48+octava, 127, 1);
      }
      if(i==21){
        MIDI.sendNoteOff(49+octava, 127, 1);
      }
      if(i==18){
        MIDI.sendNoteOff(50+octava, 127, 1);
      }
      if(i==22){
        MIDI.sendNoteOff(51+octava, 127, 1);
      }
      if(i==19){
        MIDI.sendNoteOff(52+octava, 127, 1);
      }
      if(i==20){
        MIDI.sendNoteOff(53+octava, 127, 1);
      }
      if(i==23){
        MIDI.sendNoteOff(54+octava, 127, 1);
      }
      if(i==0){
        MIDI.sendNoteOff(55+octava, 127, 1);
      }
      if(i==4){
        MIDI.sendNoteOff(56+octava, 127, 1);
      }
      if(i==1){
        MIDI.sendNoteOff(57+octava, 127, 1);
      }
      if(i==5){
        MIDI.sendNoteOff(58+octava, 127, 1);
      }
      if(i==2){
        MIDI.sendNoteOff(59+octava, 127, 1);
      }
      if(i==3){
        MIDI.sendNoteOff(60+octava, 127, 1);
      }
      if(i==6){
        MIDI.sendNoteOff(61+octava, 127, 1);
      }
      if(i==8){
        MIDI.sendNoteOff(62+octava, 127, 1);
      }
      if(i==7){
        MIDI.sendNoteOff(63+octava, 127, 1);
      }
      if(i==9){
        MIDI.sendNoteOff(64+octava, 127, 1);
      }
      if(i==10){
        MIDI.sendNoteOff(65+octava, 127, 1);
      }
      if(i==12){
        MIDI.sendNoteOff(66+octava, 127, 1);
      }
      if(i==11){
        MIDI.sendNoteOff(67+octava, 127, 1);
      }
      if(i==13){
        MIDI.sendNoteOff(68+octava, 127, 1);
      }
      if(i==14){
        MIDI.sendNoteOff(69+octava, 127, 1);
      }
      if(i==16){
        MIDI.sendNoteOff(70+octava, 127, 1);
      }
      if(i==15){
        MIDI.sendNoteOff(71+octava, 127, 1);
      }
      
    }
    valorAnterior[i]=valorLeido[i]; // El valor anterior es el nuevo valor para la siguiente iteracion
  }

}
