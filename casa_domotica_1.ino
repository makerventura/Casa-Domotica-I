/* Autor : Santiago Ventura Gomez . 2017
Curso Experto Universitario en Robótica , Programación e Impresión 3D
Asignatura : Robótica
Profesor : Alberto Valero
Actividad 1 : Construcción de una Casa Domótica Fase I
*/
/*
Objetivo : Primera Parte de la Construcción de una Casa Domótica . En esta fase pretendemos implementar un programa que encienda / apague las luces de la casa
de forma automática según la luz recibida por el sensor ldr , y/o de forma manual mediante la pulsación de un botón
*/
/* La casa dispone en esta primera fase , de la siguiente iluminación :

*  Dormitorio planta superior : led_cama ( PIN No. 12 ) , led_escritorio ( PIN No. 11 )
*  Modulo_Entrada , planta inferior : led_cocina ( PIN No. 10 )
*  Porche de la entrada , zona jardín : led_porche ( PIN No. 9 )
*/
/*
Descripción de la Máquina :

Estados :
* S0 : Luces Apagadas + DIA
* S1 : Luces Apagadas + NOCHE
* S2 : Luces Encendidas + DIA
* S3 : Luces Encendidas + NOCHE

Eventos  :
* E0 : Boton pulsar y soltar
* E1 : Nivel de Luz Ambiente >= 200
* E2 : Nivel de lUz Ambiente <  200
*/

/*
NOTA : Por la construcción de nuestro sistema , no podremos nunca mantener más de 24 horas seguidas 
        encendidas las luces porque el sistema automático las apaga al llegar el día si no se pulsa
        el botón .También hay que tener en cuenta que en caso de ausencia prolongada de la casa , se
        producirían gastos innecesarios de luz
*/



/***   Global variables and function definition  ***/

int estado = 0;                  // Variable que guarda el estado de mi máquina
const int led_cama = 12;         //Pin al que conectamos el Led del dormitorio , zona cama
const int led_escritorio = 11;  //Pin al que conectamos el Led del dormitorio , zona escritorio
const int led_cocina = 10;      //Pin al que conectamos el led de la entrada , zona cocina
const int led_porche = 9;       //Pin al que conectamos el led del jardin , zona porche
const int boton = 2;            //Pin al que conectamos el botón pulsador que controla el encendido-apagado de los leds
const int ldr = A0;             // Pin analógico al que conectamos el sensor de luz


/***   Setup  ***/

void setup(){
  
pinMode(led_cama, OUTPUT);         // Declaramos led_cama como salida
pinMode(led_escritorio, OUTPUT);   // Declaramos led_escritorio como salida
pinMode(led_cocina, OUTPUT);       // Declaramos led_cocina como salida
pinMode(led_porche, OUTPUT);       // Declaramos led_porche como salida
pinMode(boton, INPUT);             // Declaramos boton como entrada          
pinMode(ldr, INPUT);               // Declaramos ldr como entrada

/*
Iniciamos el programa colocando a la máquina en estado S0 : Todos los leds apagados
*/
digitalWrite(led_cama,LOW);            // Apagamos la luz de la cama
digitalWrite(led_escritorio,LOW);      // Apagamos la luz del escritorio
digitalWrite(led_cocina,LOW);          // Apagamos la luz de la cocina
digitalWrite(led_porche,LOW);          // Apagamos la luz del porche

}


/***   Loop  ***/

void loop(){
  
/*****        Programacion de la LOGICA DE LA MAQUINA DE ESTADOS     *****/

if (estado == 0 && digitalRead(boton) == 1){  // Si estado = 0 y pulsamos el boton ...
  while (digitalRead(boton) == 1){  // Bucle para evitar efecto rebote del boton
    delay(10);
    }
  estado = 2;  // Cambiamos a estado = 2
  }
else if ( estado == 0 && analogRead(ldr) < 200){  // Si estado = 0 y se hace de noche ....
  estado = 3;  // Cambiamos a estado = 3
  }  
else if (estado == 1 && digitalRead(boton) == 1){  // Si estado = 1 y pulsamos el boton ...
  while (digitalRead(boton) == 1){  // Bucle para evitar efecto rebote del boton
    delay(10);
    }
  estado = 3;  // Cambiamos a estado = 3
  }
else if (estado == 1 && analogRead(ldr) >= 200){  // Si estado = 1 y se hace de dia ...
  estado = 0;  // Cambiamos a estado = 0
  }
else if (estado == 2 && digitalRead(boton) == 1){  // Si estado = 2 y pulsamos el boton ...
  while (digitalRead(boton) == 1){  // Bucle para evitar efecto rebote del boton
    delay(10);
    } 
  estado = 0;  // Cambiamos a estado = 0
  }
else if ( estado == 2 && analogRead(ldr) < 200){  // Si estado = 2 y se hace de noche ...
  estado = 3;  // Cambiamos a estado = 3
  }
else if (estado == 3 && digitalRead(boton) == 1){  // Si estado = 3 y pulsamos el boton ...
  while (digitalRead(boton) == 1){  // Bucle para evitar efecto rebote del boton
    delay(10);
    }
  estado = 1;  // Cambiamos a estado = 1
  }  
else if (estado == 3 && analogRead(ldr) >= 200){  // Si estado = 3 y se hace de día ...
  estado = 0;  // Cambiamos a estado = 0
  }
  
 /*****  FIN DE LA PROGRAMACION DE LA LOGICA DE LA MAQUINA DE ESTADOS  *****/
 
 
 /*****  COMIENZO DE LA PROGRAMACION DE LAS ACCIONES DE LA MAQUINA DE ESTADOS  *****/
 
 if (estado == 0){
    digitalWrite(led_cama,LOW);           // Apagamos la luz de la cama
    digitalWrite(led_escritorio,LOW);     // Apagamos la luz del escritorio
    digitalWrite(led_cocina,LOW);         // Apagamos la luz de la cocina
    digitalWrite(led_porche,LOW);         // Apagamos la luz del porche
 }
 else if (estado == 1){
    digitalWrite(led_cama,LOW);           // Apagamos la luz de la cama
    digitalWrite(led_escritorio,LOW);     // Apagamos la luz del escritorio
    digitalWrite(led_cocina,LOW);         // Apagamos la luz de la cocina
    digitalWrite(led_porche,LOW);         // Apagamos la luz del porche
 }
 else if (estado == 2){
    digitalWrite(led_cama,HIGH);           // Encendemos la luz de la cama
    digitalWrite(led_escritorio,HIGH);     // Encendemos la luz del escritorio
    digitalWrite(led_cocina,HIGH);         // Encendemos la luz de la cocina
    digitalWrite(led_porche,HIGH);         // Encendemos la luz del porche
 }
 else if (estado == 3){
    digitalWrite(led_cama,HIGH);           // Encendemos la luz de la cama
    digitalWrite(led_escritorio,HIGH);     // Encendemos la luz del escritorio
    digitalWrite(led_cocina,HIGH);         // Encendemos la luz de la cocina
    digitalWrite(led_porche,HIGH);         // Encendemos la luz del porche
 }
 
 /*****  FIN DE LA PROGRAMACION DE LAS ACCIONES DE LA MAQUINA DE ESTADOS  *****/
 
/***********************      Fin del Programa       **************************/

}
