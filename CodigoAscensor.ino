/*
----------------- Elevator Barbie doll House with Arduino nano - 3 floors ----------------------
| platform: Arduino Nano
| Created by : Armando Trout
| Created at: December 2017
|
---------------------------------------------------------------------------------------------
*/

//pins Nano

#define LED 13
#define MOTOR_STEP A2   // Pololu driver A4988 Stepper Motor Driver Carrier 
#define MOTOR_DIR A1    // Pololu driver A4988 Stepper Motor Driver Carrier
#define P1 8            // pulls button first floor 
#define P2 10           // pulls button second floor
#define P3 12           // pulls button third floor 
#define FIN_RUN 2       // HOME position



// vars and const

const int delay_pasos = 1500; // delay moving  1000 us = 1ms
int pisoActual = 1; //initial floor


void setup(){

  // run led
  pinMode( LED, OUTPUT);  

  // pins to driver motor Polulu
  pinMode( MOTOR_DIR, OUTPUT);
  pinMode( MOTOR_STEP, OUTPUT);       


  // pulls buttons of  floors
  pinMode(P1, INPUT); // floor one
  pinMode(P2, INPUT); // floor two
  pinMode(P3, INPUT); // floor three

  // home
  pinMode(FIN_RUN, INPUT); 

  
  // subrutine of inicialization
  inicializacion();

}


void loop(){ 



  
  // goto floor 1

  if( digitalRead(P1) == HIGH && pisoActual != 1 ){
     
            
    while( digitalRead(FIN_RUN) != HIGH ){

      moverMotor(1, LOW);

    } 

    pisoActual = 1;    
    
  }

  
   // goto floor 2 
  
  if( digitalRead(P2) == HIGH && pisoActual != 2 ){  
     

    if(pisoActual == 1){

      moverMotor(1900, HIGH);            
    }

    if(pisoActual == 3){

      moverMotor(1980, LOW);      
    }

    pisoActual = 2;     

  }

  
  // goto floor 3

  if( digitalRead(P3) == HIGH && pisoActual != 3){
   
    
    if(pisoActual == 1){

      moverMotor(3880, HIGH);
    }

    if(pisoActual == 2){

      moverMotor(1980, HIGH);
    } 

    pisoActual = 3;    

  }
  



}// end loop







void inicializacion(){
  

  
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





void moverMotor(int pasos, int direccion){
  

  digitalWrite(MOTOR_DIR, direccion); // if direccion == HIGH -> elevetor goes up 
 
  for(int x = 0; x < pasos; x++) {

    digitalWrite(MOTOR_STEP, HIGH);
    digitalWrite(LED, HIGH);
    delayMicroseconds(delay_pasos);
    digitalWrite(MOTOR_STEP, LOW);
    digitalWrite(LED, LOW);
    delayMicroseconds(delay_pasos);

  }

}  


   
    
    
  
