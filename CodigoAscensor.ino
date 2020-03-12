/*
----------------- Rutinas para Ascensor para casa Barbie de tres pisos ----------------------
| Plataforma: Arduino Nano
| Creado por: Armando Trout
| Creado en: Diciembre de 2017
|
---------------------------------------------------------------------------------------------
*/

// asignacion de pines del atmega

#define LED 13
#define MOTOR_STEP A2   // control de pasos - Pololu driver A4988 Stepper Motor Driver Carrier 
#define MOTOR_DIR A1    // Control de direccion - Pololu driver A4988 Stepper Motor Driver Carrier
#define P1 8            // Control pin pulsador primera planta 
#define P2 10           // Control pin pulsador segunda planta
#define P3 12           // Control pin pulsador tercera planta 
#define FIN_RUN 2       // fin de carrera - posicion HOME



// declaracion de variables y constantes

const int delay_pasos = 1500; // retardo de movimiento del motor em microsegundos  1000 us = 1ms
int pisoActual = 1; //definimos la planta actual donde comienza el ascensor



void setup(){

  // led de indicacion de funcionamiento
  pinMode( LED, OUTPUT);  

  // configuracion de pines que conectan con el driver del motor a pasos
  pinMode( MOTOR_DIR, OUTPUT);
  pinMode( MOTOR_STEP, OUTPUT);       


  // pulsadores en pisos
  pinMode(P1, INPUT); // pulsador del piso 1
  pinMode(P2, INPUT); // pulsador del piso 2
  pinMode(P3, INPUT); // pulsador del piso 3

  // Fin de carrera en el piso 1
  pinMode(FIN_RUN, INPUT); 

  
  // inicializo el sistema buscando la posicion inicial en el piso 1
  inicializacion();

}


void loop(){ 



  
  // ir al piso 1

  if( digitalRead(P1) == HIGH && pisoActual != 1 ){
     
            
    while( digitalRead(FIN_RUN) != HIGH ){

      moverMotor(1, LOW);

    } 

    pisoActual = 1;    
    
  }

  
   // ir al piso 2 
  
  if( digitalRead(P2) == HIGH && pisoActual != 2 ){  
     

    if(pisoActual == 1){

      moverMotor(1900, HIGH);            
    }

    if(pisoActual == 3){

      moverMotor(1980, LOW);      
    }

    pisoActual = 2;     

  }

  
  // ir al piso 3

  if( digitalRead(P3) == HIGH && pisoActual != 3){
   
    
    if(pisoActual == 1){

      moverMotor(3880, HIGH);
    }

    if(pisoActual == 2){

      moverMotor(1980, HIGH);
    } 

    pisoActual = 3;    

  }
  



}// fin loop







void inicializacion(){
  

  // verificar si el fin de carrera se encuentra pulsado de ser asi nos encontramos en el piso 1
  if ( digitalRead(FIN_RUN) == HIGH ){

    moverMotor(100, HIGH);

    delay(500);
   
    while( digitalRead(FIN_RUN) != HIGH ){

      moverMotor(10, LOW); 
    }

    pisoActual = 1; 
    

  }else{
    
          while( digitalRead(FIN_RUN) != HIGH ){
       
            moverMotor(1, LOW);
          } 

          pisoActual = 1;

      }

}



// rutina encargada de controlar el motor a pasos

void moverMotor(int pasos, int direccion){
  

  digitalWrite(MOTOR_DIR, direccion); // direccion tiene dos posibles valores si es HIGH el ascensor sube si es LOW el ascensor baja
 
  for(int x = 0; x < pasos; x++) {

    digitalWrite(MOTOR_STEP, HIGH);
    digitalWrite(LED, HIGH);
    delayMicroseconds(delay_pasos);
    digitalWrite(MOTOR_STEP, LOW);
    digitalWrite(LED, LOW);
    delayMicroseconds(delay_pasos);

  }

}  


   
    
    
  
