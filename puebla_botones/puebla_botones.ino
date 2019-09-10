

const int numBotones=24;       // Definir aqui el numero de botones (11 max)
int valorLeido[numBotones];    // Array con los valores leidos de cada boton
int valorAnterior[numBotones]; // Array con el valor anterior leido

void setup() {
  Serial.begin(9600);          // Inicializamos la comunicacion serial
  for(int i=22; i<numBotones; i++){
    pinMode(i, INPUT);       // Recorremos cada pin y lo ponemos como entrada
    valorAnterior[i]=1;        // Inicializamos el valor anterior a 1 (no pulsado)
  }
}

void loop(){
  for(int i=22; i<numBotones; i++){
    valorLeido[i]=digitalRead(i); // Leer valor
    // Solo enviamos cuando ha existido un cambio, para no sobrecargar el puerto serial
    if((valorLeido[i]==0) && (valorLeido[i]!=valorAnterior[i])){
      Serial.print("Pulsado el boton: ");
      Serial.println(i);
      Serial.println("------------");
    }
    else if ((valorLeido[i]==1) && (valorLeido[i]!=valorAnterior[i])){
      Serial.print("Ya no el boton: ");
      Serial.println(i);
      Serial.println("------------");
    }
    valorAnterior[i]=valorLeido[i]; // El valor anterior es el nuevo valor para la siguiente iteracion
  }

}
