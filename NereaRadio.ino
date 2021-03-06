/*   Reloj despertador con dos alarmas, sensor de temperatura y reproductor mp3
 *   creado por gardav79 (davidgarant@gmail.com)
 *   
 *   ---- Enlaces ----------------------------------------------------------------------------------------------------------------
 *   Enlace a github: https://github.com/gardav79/RelojDespertadorMP3
 *   Enlace a los STL en thinkgiverse: https://www.thingiverse.com/thing:4627107
 *   
 *   ---- Versiones --------------------------------------------------------------------------------------------------------------
 *   
 *   24/10/2020 Versión 1.5
 *   
 *   **** Cambios introducidos v1.5 *******************
 *   
 *   · Corrección menor del problema de la barra de reproducción
 *   
 *   22/10/2020 Versión 1.4
 *   
 *   **** Cambios introducidos v1.4 *******************
 *   
 *   · Cambios en el modo de reproducción de la siguiente canción
 *   · He retirado la relectura que introduje anteriormente al no ser ya necesaria
 *   · Corregido problema en la barra de reproducción al cambiar de canción. Si el BY8001-16P tardaba en dar los valores de tiempo de la canción
 *     la barra de reproducción no se pintaba correctamente.
 *   
 *   19/10/2020 Versión 1.3
 *   
 *   **** Cambios introducidos v1.3 *******************
 *   
 *   · Relectura del valor tiempoTotal en el reproductor mp3 por un error en el pintal de la barra de progreso de mp3, 
 *     que en modo aleatorio no pintaba correctamente
 *   · Cambio en el tono de la chicharra, buscando un tono más corto y algo más grave
 *   
 *   18/10/2020 Versión 1.2
 *   
 *   **** Cambios introducidos v1.2 *******************
 *   
 *   · Creación de 2 arrays para indicar en el título de los ajustes de hora y fecha y alarmas el campo 
 *     que se está editando
 *   · Al mostrar la cadena "ano" muestra una línea encima de la "n" para simular una "ñ" (una virgulilla (~))
 *   
 *   
 *   13/10/2020 Versión 1.1
 *   
 *   **** Cambios introducidos v1.1 *******************
 *   
 *   · Posibilidad de ajustar la alarma y el reloj desde la pantalla del reproductor
 *   · Cambia canción automáticamente en caso de no estar en la ventana del reproductor
 *   · Se puede cambiar entre canciones y parar la reproducción en la ventana principal
 *   · Se puede cambiar el modo de reproducción y el ecualizador en la ventana principal
 *   · Optimización de parte del código
 * 
 *   04/10/2020 Versión 1.0       
 *   
 *   
 *   ------------------------------------------- Licencia / License -----------------------------------------------------------------
 *   Licencia Creative Commons  Atribución-NoComercial-CompartirIgual 
 *   License Creative Commons (CC BY-NC-SA 3.0))   
 *   https://creativecommons.org/licenses/by-nc-sa/4.0
 *   
 *   ------------------------------------------- Idea original ----------------------------------------------------------------------
 *   
 *   Idea original del usuario Dejan Nedelkovski (https://howtomechatronics.com/author/howtom12_wp/) 
 *   de la web www.howtomechatronics.com
 *   
 *   Post idea original: https://howtomechatronics.com/projects/arduino-touch-screen-music-player-alarm-clock-project/
 *   
 *   ------------------------------------------- Resumen y explicación breve del código --------------------------------------------
 *   
 *   La idea original está realizada con una pantalla de 3.2" táctil y una única alarma. Partiendo de esa idea, he sustituido la 
 *   pantalla de 3.2" táctil por una pantalla de 3.5" sin táctil (480x320px, ILI9486, 16bits) y 12 botones físicos para realizar 
 *   las funciones necesarias.
 *   
 *   Al encender, muestra un mensaje de bienvenida a "Nerea" (mi sobrina, que para ella lo hice). La placa DS3231 tiene la 
 *   posibilidad de guardar la fecha y hora con una pila de botón CR2032. El programa comprueba la fecha que la placa DS3231
 *   le da y si es la fecha por defecto (01/01/2000) le asigna la fecha de cumpleaños de mi sobrina, en caso contrario "pinta"
 *   la fecha correcta y la hora y muestra además el día en nombre en la fecha. La temperatura en la idea original muestra solo 
 *   unidades enteras, sin decimas. Lo he modificado para que muestre esas décimas y además, muestre un emoji dependiendo de la 
 *   temperatura (si hace frío, emoji de frío, mucho calor emoji sofocado, etc...). En el proyecto original se contemplaba una 
 *   alarma. En este código están incluidas dos alarmas que se guardan en la EEPROM del arduino, se muestran como notificación
 *   en la pantalla del reloj, y permiten reproducir dos tipos de tonos. Por un lado, reproducir mp3 (si no se está reproduciendo
 *   nada, cosa que comprueba) y por otro una "chicharra" (un buzzer, en inglés). Si se está reproduciendo mp3 aunque el tono  
 *   elegido para la alarma sea mp3 se reproducirá el tono por la chicharra. También está controlado que no se "pisen" las alarmas.
 *   Las alarmas con tono mp3 van subiendo de volumen 2 puntos cada 5 segundos (hasta un máximo de 30 puntos, que el volumen máximo) y 
 *   si la canción se acaba, reproduce la siguiente.
 *   
 *   El reproductor mp3 posibilita la opción de cambiar entre los ecualizadores predefinidos de la placa BY8001-16P y 
 *   los modos posibles de reproducción (aleatorio, repetir, etc..) El volumen se puede controlar tanto en la pantalla del reproductor
 *   como en la pantalla del reloj.
 *   
 *   El día del cumpleaños de mi sobrina, toca la melodia del cumpleaños feliz dos veces: A las 8h y las 20h siempre y cuando no haya 
 *   ninguna alarma reproduciendose.
 *   
 *   ---------------------------------------------- Modificación en la librería DS3231 -----------------------------------------------
 *   
 *   Para poder controlar que los días son los de un mes concreto (meses de 30, que no se pueda poner 31 por ejemplo) he modificado la 
 *   libería DS3231 incluyendo tres métodos que se encargan de realizar esa comprobación. Esos métodos son:
 *   
 *   bool bisiesto(unsigned int year); //para conocer si un año es bisiesto
 *   char  dias_mes(char mes, char ano, char siglo);
 *   char  dias_mes(char mes, int ano);
 *   
 *   Y pertenecen a Víctor Ventura (hola@victorventura.es) y su web https://victorventura.es
 *   
 *   Enlace al post de su web el que habla y lo explica en profundidad:
 *   
 *   https://victorventura.es/polaridad.es/ajustar-hora-rtc-reloj-ds3231-arduino/
 *   
 *   --------------------------------------------- Libreria BY8001 reproductor mp3 ---------------------------------------------------
 *   
 *    BY8001 MP3 Player Library creada por borland del foro Arduino, Released in public domain. 
 *    Enlace de descarga: https://github.com/r0ndL/BY8001 
 *   
 *   
 *   --------------------------------------------- Libreria UTFT, fuentes tipográficas y libreria DS3231 -----------------------------
 *   
 *   Tanto la libreria que controla el reloj DS3231, la libreria de la pantalla así como las fuentes pertenecen a Henning Karlsen y 
 *   su web https;//www.rinkydinkelectronicks.com
 *   
 *   Se pueden obtener aquí:
 *   
 *   Libreria UTFT: http://www.rinkydinkelectronics.com/library.php?id=51
 *   Libreria DS3231: http://www.rinkydinkelectronics.com/library.php?id=73
 *   Fuentes tipográficas usadas: http://www.rinkydinkelectronics.com/r_fonts.php
 * 
 *   
 *   -------------------------------------------- Método para obtener las décimas en la temperatura ----------------------------------
 *   
 *   Este método pertenece a la web http://www.trainelectronics.com/ (info@trainelectronics.com)
 *   
 *   Enlace al método: http://www.trainelectronics.com/Arduino/float-to-string/Float-to-string.htm
 *   
 *   
 *   -------------------------------------------- Melodía feliz cumpleaños -----------------------------------------------------------
 *   
 *   La melodía pertenece a sparkbuzzer (https://create.arduino.cc/projecthub/Sparkbuzzer)
 *   
 *   Enlace a su post: https://create.arduino.cc/projecthub/Sparkbuzzer/happy-birthday-tone-using-arduino-uno-fba4a8
 *   
 *   
 *   -------------------------------------------- Tono alarma ------------------------------------------------------------------------
 *   
 *   El tono de alarma está basado en el código siguiente: https://www.ardumotive.com/how-to-use-a-buzzer-en.html
 *   
 *   En el que que se explica como usar hacer que suenen diferentes frecuencias a través de la chicharra
 *   
 *   -------------------------------------------- Material necesario -----------------------------------------------------------------
 *   
 *   -. Arduino mega 2560 o similar
 *   -. Pantalla de 3.5" TFT (480x320px), controladora ILI9486, 16bits
 *   -. Placa BY8001-16P mp3 o similar
 *   -. Placa DS3231 reloj y temperatura
 *   -. Pila de botón CR2032 para la placa DS3231
 *   -. 12 pulsadores
 *   -. 12 resistencias de 10k 
 *   
 *   
 *  
 *   
 * 
 * 
 */

#include <SoftwareSerial.h>
#include <BY8001.h>
#include <DS3231.h>
#include <EEPROM.h>
#include <UTFT.h>

//Definición de colores
#define ROSA 0xF80F
#define MORADO 0xF81E
#define TURQUESA 0x177D
#define AMARILLO 0xFFE0
#define  ROJO 0xF8C0
#define NEGRO 0x0000
#define BLANCO 0xFFFF
#define VERDEFOSFORITO 0x07E0
//ESTAS CONSTANTES DEFINEN LOS PINES PARA CADA BOTÓN
#define SUBIRVOLUMEN 46 //subir volumen
#define BAJARVOLUMEN 44 //bajar volumen
#define AJUSTARRELOJ 12 //ajustar reloj
#define AJUSTARALARMA 11 //ajustar alarma
#define CANCELARALARMA 10 //cancelar alarma
#define CAMBIARARELOJ 9 //cambiar a reloj (pantalla principal)
#define CAMBIARMODOREPRODUCCION 8 //cambiar a reproductor mp3
#define ACEPTARPLAYPAUSE 7 //play, pause, aceptar
#define AUMENTARHORACANCION 6 //siguiente canción, aumentar un digito
#define DISMINUYEHORACANCION 5 //anterior canción, disminuit un digito
#define CANCELARSTOP 4 //stop, cancelar
#define CAMBIARECUALIZADOR 3 //cambiar equalizador
//PIN DE LA CHICHARRA 
#define PINCHICHARRA 13

//==== Crea los objetos
UTFT utftGLCD(ILI9486, 38, 39, 40, 41); //Parametros para la pantalla
SoftwareSerial mp3Serial(62, 63);  // a9, a8 rx, tx
BY8001 mp3;  // crea una instancia de clase BY8001 y la llama 'mp3'
DS3231 rtc(SDA, SCL);

//definición de los tipos de letra
extern uint8_t SmallFont[]; //letra pequeña
extern uint8_t BigFont[]; //letra normal
extern uint8_t GroteskBold24x48[]; //letra de bienvenida y textos alarmas
extern uint8_t SixteenSegment48x72Num[]; //letra del reloj 
extern uint8_t Various_Symbols_32x32[]; //Símbolos de reproducción, volumen, etc...

//definición de los iconos
//emojis
extern unsigned short agustico_24px[]; 
extern unsigned short calor_24px[];
extern unsigned short frio_24px[];
extern unsigned short fresquito_24px[];
//iconos de alarmas
extern unsigned short chicharra_24px[];
extern unsigned short musica_24px[];
extern unsigned short alarma_36px[];

//variables reproductor mp3
byte mReproduccion = 0; // 0/1/2/3/4 All/Folder/Single/Random/Disabled 
byte ecualizador = 3; //0/1/2/3/4/5  Normal/Pop/Rock/Jazz/Classic/Bass
byte estadoReproduccion; //estado de la reproducción, siendo-> 0/1/2/3 parado/reproduciendo/pausado/alarma mp3 sonando
byte volumen = 14; //volumen por defecto (rango de volumen entre 0 y 30)

//variables tamaño pantalla
int tamanioPantallaAncho; //variable para el ancho de la pantalla
int tamanioPantallaAlto; //variable para el alto de la pantalla
int medio; //variable para el punto medio del ancho de pantalla
byte ejeX = 32; //variable para mostrar los iconos en la pantalla, eje X
byte ejeY = 0; //variable para mostrar los iconos en la pantalla, eje Y

//variable ventana
byte ventana = 0; // 0/1/2/3/4 principal con reloj/ajustar fecha y hora/ajustar alarmas/reproductor mp3/ventana de alarma con mensaje
byte ventanaAntesAlarma = 0; //variable para retornar a la ventana en la que se encontrara antes de mostrar la alarma
byte ventanaAlaQueVolver = 0; //variable para retornar a la ventana desde la que accedió al ajuste de las alarmas o el reloj
byte ponerEnHora = 0; //variable para cambiar entre digitos en la ventana de ajuste de la hora
byte ponerAlarma = 0; //variable para cambiar entre digitos en la ventana de ajuste de las alarmas
//variables alarma
byte alarma1Hora = 00; //variable para las horas de la alarma 1
byte alarma1Minutos = 00; //variable para los minutos de la alarma 1
byte alarma2Hora = 00; //variable para las horas de la alarma 2
byte alarma2Minutos = 00; //variable para los minuots de la alarma 2
bool alarma1OnOff; //verdadero -> on, falso -> off
bool alarma2OnOff; //verdadero -> on, falso -> off
bool alarma1TonoMp3; //verdadero -> tono, falso -> mp3
bool alarma2TonoMp3; //verdadero -> tono, falso -> mp3
bool alarma1Coincide = false; //verdadero si la hora coincide con la alarma 1
bool alarma2Coincide = false; //verdadero si la hora coincide con la alarma 2
const byte volumenAlarma = 18; //constante del volumen inicial para la alarma
bool dibujoAlarma = true; //variable para entrar en condicional de la alarma y borrar la pantalla
byte contador = 1; //contador en segundos de la alarma mp3
byte volAlarm = volumenAlarma; //volumen de la alarma variable, se utiliza para ir subiendo paulatinamente el volumen
bool tonoAlarmaReproduciendo = false; //define si se está reproduciendo una alarma, para que no se pisen ambas alarmas
bool dibujadoIcono = false;
         
//variable temperatura
float temperatura; //variable para obtener la temperatura. Tipo float para las décimas
//variables hora y fecha
byte digitosHora = 00; //variable que se pinta en la pantalla en las diferentes ventanas para las horas
byte digitosMinutos = 00; //variable que se pinta en la pantalla en las diferentes ventanas para los minutos
byte digitosSegundos = 00; //variable que se pinta en la pantalla en las diferentes ventanas para los segundos
byte digitosDia; //variable que se pinta en la pantalla en las diferentes ventanas para los dias (2 digitos)
byte digitosMes; //variable que se pinta en la pantalla en las diferentes ventanas para los meses (2 digitos)
int digitosAnio; //variable que se pinta en la pantalla en las diferentes ventanas para los años (4 digitos)

//variables para el reproductor mp3
static word tiempoTotal, tiempoTranscurrido, reproduccion, minutos, segundos, lastSeconds, minutosReproducidos, segundosReproducidos;
//variables para la hora y fecha actuales
String relojActual, horasActuales, minutosActuales, segundosActuales, fechaActual, fecha, dia, mes, anio;
String horasS, minutosS, segundosS, fechaS;
bool siguienteCanc = false; //variable para determinar si se ha cambiado a la siguiente canción

//Cadenas fijas para los textos
const String encendido = "Encend.";
const String apagado = "Apagada";
const String nombre = "Nerea";
const String sonLas = ", son las";
// 0 HORA ALARMA1/ 1 MINUTOS ALARMA1/ 2 ONOFF ALARMA1/ 3 TONO ALARMA 1
// 4 HORA ALARMA2/ 5 MINUTOS ALARMA2/ 6 ONOFF ALARMA2/ 7 TONO ALARMA 2
const String ajustarAlarmasArray[] = {
  "AJUSTAR HORA ALARMA 1   ", "AJUSTAR MINUTOS ALARMA 1", 
  "AJUSTAR ALARMA 1        ", "AJUSTAR TONO ALARMA 1   ",
  "AJUSTAR HORA ALARMA 2   ", "AJUSTAR MINUTOS ALARMA 2", 
  "AJUSTAR ALARMA 2        ", "AJUSTAR TONO ALARMA 2   ",
};
const String ajustarHoraArray[] = { // O HORA/ 1 MINUTOS/ 2 MES/ 3 AÑO/ 4 DIA
	"AJUSTAR HORA   ", "AJUSTAR MINUTOS", "AJUSTAR MES    ", 
	"AJUSTAR ANO     ", "AJUSTAR DIA     "
};
const String hoyes = ", hoy es "; 
const String de = " de ";
const String modoEcualizacion[] = {"Normal ", "Pop    ", "Rock   ", 
	                                 "Jazz   ", "Clasica", "Bass   "};
const String modoReproduccion[] = {"Todas      ", "Carpeta    ", 
	                                 "Repetir    ", "Aleatorio  ", 
	                                 "Desactivado"};

//variables referentes a tonos, melodia y fecha cumpleaños
int freq = 50;      // Frecuencia inicial
int length = 28; // Número de notas
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int tempo = 200;// Retraso en ms entre notas

//Variables de cumpleaños. El día indicado sonará dos veces el tono de cumpleaños, a las dos horas indicadas
int vueltaTonoCumpleanios = true;
const byte diaNacimiento = 11; //día de nacimiento. Si no tiene fecha actual, asigna este día
const byte mesNacimiento = 9; //mes de nacimiento. Si no tiene fecha actual, asigna este mes
const int anioNacimiento = 2011; //año de nacimiento. Si no tiene fecha actual, asigna ese año
const byte hora1DiaCumple = 8; //hora a la que sonará la primera vez tono cumpleaños feliz
const byte minuto1DiaCumple = 0; //minutos a los que sonará la primera vez tono cumpleaños feliz
const byte hora2DiaCumple = 20; //hora a la que sonará la segunda vez tono cumpleaños feliz
const byte minuto2DiaCumple = 0; //minutos a los que sonará la segunda vez tono cumpleaños feliz

void setup() {
  //Pines asignados a botones
  pinMode(46, OUTPUT); //subir volumen
  pinMode(44, OUTPUT); //bajar volumen
  pinMode(12, OUTPUT); //ajustar reloj
  pinMode(11, OUTPUT); //ajustar alarma
  pinMode(10, OUTPUT); //cancelar alarma
  pinMode(9, OUTPUT); //cambiar a reloj (pantalla principal)
  pinMode(8, OUTPUT); //cambiar a reproductor mp3
  pinMode(7, OUTPUT); //play, pause, aceptar
  pinMode(6, OUTPUT); //siguiente canción, aumentar un digito
  pinMode(5, OUTPUT); //anterior canción, disminuit un digito
  pinMode(4, OUTPUT); //stop, cancelar
  pinMode(3, OUTPUT); //cambiar equalizador
  //pin de la chicharra   
  pinMode(PINCHICHARRA, OUTPUT);
    
  //Inicializar la pantalla
  utftGLCD.InitLCD();
  utftGLCD.clrScr();
  tamanioPantallaAncho = utftGLCD.getDisplayXSize(); //obtiene y asigna el ancho de pantalla
  tamanioPantallaAlto = utftGLCD.getDisplayYSize(); //obtiene y asigna el alto de pantalla
  medio =  (tamanioPantallaAncho/2)-((16*10)/2); //obtiene y asigna el punto medio del ancho de pantalla
  
  rtc.begin(); //Inicializa el reloj
  leerAlarmas(); //lee las alarmas de la EEPROM 

  //Inicializa el mp3
  Serial.begin(9600);  // asigna el ratio en baudios al monitor serie
  mp3Serial.begin(9600);  // BY8001 set to 9600 baud (required)
  mp3.setup(mp3Serial); // tell BY8001 library which serial port to use.
  delay(800);  // allow time for BY8001 cold boot; may adjust depending on flash storage size

  obtenerFechaActual(); //llama al método para obtener la fecha actual
  saludo(); //Lanza el saludo de bienvenida (siempre cuando se enciende)
  dibujarPantallaInicio(); //dibuja la pantalla de inicio
  
  relojActual = rtc.getTimeStr(); //obtiene la hora actual
  horasActuales = relojActual.substring(0, 2); //alimenta la variable horas actuales
  minutosActuales = relojActual.substring(3, 5); //la de minutos
  segundosActuales = relojActual.substring(6, 8); //y la de segundos

  //fuerza a asignar las alarmas si los valores de las variables son 255 (son variables tipo byte). 
  if (alarma1Hora == 255 | alarma1Minutos == 255 | alarma2Hora == 255 | alarma2Minutos == 255) {
    asignarAlarmas();
  }
}

void loop() {
  // La ventana 0 es la ventana del reloj, en el que muestra el reloj en grande en el centro, la fecha completa y la temperatura
  if (ventana == 0) {
    leerAlarmas(); //lee las alarmas de la EEPROM
    pintarAlarmas(); //Si hay alguna alarma activa, la pinta
    compruebaAlarma(); //y la comprueba
    ventanaAlaQueVolver = 0;    
    if ( relojActual != rtc.getTimeStr()) { //actualiza la hora, minutos y segundos
      relojActual = rtc.getTimeStr();
      horasS = relojActual.substring(0, 2);
      minutosS = relojActual.substring(3, 5);
      segundosS = relojActual.substring(6, 8);
      utftGLCD.setFont(SixteenSegment48x72Num);
      utftGLCD.setColor(VERDEFOSFORITO);
      //actualiza los segundos
      utftGLCD.print(segundosS, 302, 120);
      //Si cambia el minuto, lo actualiza
      if ( minutosActuales != minutosS ) {
        utftGLCD.print(minutosS, 186, 120);
        minutosActuales = minutosS;
      }
      //Si cambia la hora, lo actualiza
      if ( horasActuales != horasS ) {
        utftGLCD.print(horasS, 70, 120);
        horasActuales = horasS;
      }
      //Comprueba si la fecha ha cambiado
      fechaS = rtc.getDateStr();
      delay(10);
      if ( fechaActual != fechaS){
        dibujaFecha();
      } 

      dibujaTemperatura(); //dibuja la temperatura
      delay(10);
      relojActual = rtc.getTimeStr(); 
    }
    if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa el botón play, lanza la ventana reproductor
      utftGLCD.clrScr();
      ventana = 3;
      drawTrackBar();
    } 
    
    botonesComunes(); //método que contiene el control de los botones comunes en todas las ventanas
    if (estadoReproduccion == 2) { //si está reproduciendo y se acaba la canción, pasa a la siguiente
    siguienteCancion();
    }       
  }//fin ventana 0 

  //La ventana 1, es la ventana de ajuste de fecha y hora 
  if (ventana == 1) {
    relojActual = rtc.getTimeStr(); //obtiene la hora actual
    horasActuales = relojActual.substring(0, 2);
    minutosActuales = relojActual.substring(3, 5);
    segundosActuales = relojActual.substring(6, 8);
    dibujaAjustarFechaYhora(); //dibuja los elementos de ajuste de fecha y hora
    if (estadoReproduccion == 2) { //si está reproduciendo y se acaba la canción, pasa a la siguiente
    siguienteCancion();
    }
       
    //bucle para ajustar cada objeto
    switch (ponerEnHora) {      
      case 0: //el caso 0 ajusta la hora
        utftGLCD.setColor(ROSA); 
        utftGLCD.drawRoundRect(67,78,168,153);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(digitosHora, 70,80,2,'0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, sube una hora
          digitosHora++;
        } 
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa disminuir, baja una hora
          digitosHora--;
        }
        if (digitosHora == 24) { //cambia las 24h a 00
          digitosHora = 00;
        }
        if (digitosHora == 255) { //si el digito es 255 (valor máximo de la variable) lo cambia a 23
          digitosHora = 23;
        }
        utftGLCD.printNumI(digitosHora, 70,80,2,'0');          
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(67,78,168,153); 
          ponerEnHora = 1;
        }
        compruebaBotonCancelar(0, ventanaAlaQueVolver);
      break; //fin caso 0

      case 1: //el caso 1 ajusta los minutos
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRoundRect(184,78,285,153);
        utftGLCD.setColor(VERDEFOSFORITO);        
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(digitosMinutos, 186,80,2,'0');          
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, aumenta un minuto
          digitosMinutos++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa cancelar, disminuye un minuto
          digitosMinutos--;
        }
        if (digitosMinutos == 60) { //si los minutos llegan a 60, cambia a 00
          digitosMinutos = 00;
        }
        if (digitosMinutos == 255) { //si el valor es 255, lo cambia a 59
          digitosMinutos = 59;
        }
        utftGLCD.printNumI(digitosMinutos, 186,80,2,'0');          
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(184,78,285,153);   
          ponerEnHora=2;
        }
        compruebaBotonCancelar(0, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 1
      
      case 2: //el caso 2 ajusta el mes
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRect(medio+51,159,medio+84,176);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(BigFont);
        utftGLCD.printNumI(digitosMes, medio+52, 160, 2, '0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta el mes
          digitosMes++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye el mes
          digitosMes--;
        }         
        if (digitosMes == 13) { //si el mes es 13, cambia a 01
          digitosMes = 01;
        }
        if (digitosMes == 255) { //si es 255, lo cambia a 12
          digitosMes = 12;
        }   
        utftGLCD.printNumI(digitosMes, medio+52, 160, 2,'0');        
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(medio+51,159,medio+84,176);
          ponerEnHora=3;
        }
        compruebaBotonCancelar(0, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio        
      break; //fin caso 2
      
      case 3: //el caso 3 ajusta el año
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRect(medio+103, 159, medio+168, 176);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(BigFont);
        utftGLCD.printNumI(digitosAnio, medio+104, 160, 2, '0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta los años
          digitosAnio++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye los años
          digitosAnio--;
        }          
        utftGLCD.printNumI(digitosAnio, medio+104, 160, 2,'0');
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(medio+103, 159, medio+168, 176);
          ponerEnHora=4;
        }
        compruebaBotonCancelar(0, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio        
      break; //fin caso 3
       
      case 4: //el caso 4 ajusta el día. Tiene en cuenta el mes y el año para determinar los días que tiene ese mes en concreto
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRect(medio-1, 159, medio+33, 176);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(BigFont);
        utftGLCD.printNumI(digitosDia, medio, 160, 2, '0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta el día
          digitosDia++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye el día
          digitosDia--;
        }        
        char diaMes = rtc.dias_mes(digitosMes, digitosAnio); //obtiene los días del mes y año fijados
        if (digitosDia == 255) { //si el valor es 255, ajusta valor a los días obtenidos de ese mes y año
           digitosDia = diaMes;
        } else if (digitosDia > diaMes) { //si el valor es mayor que el valor de los días obtenidos, lo cambia a 1
            digitosDia = 1;
        }      
        utftGLCD.printNumI(digitosDia, medio, 160, 2,'0'); 
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, actualiza la fecha y hora
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(medio-1, 159, medio+33, 176);
          ponerEnHora=0; //ha llegado a fin, la vuelve a 0
          rtc.setTime(digitosHora, digitosMinutos, digitosSegundos); //actualiza la hora
          rtc.setDate(digitosDia, digitosMes, digitosAnio); //y la fecha
          utftGLCD.clrScr(); //limpia la ventana
          if (ventanaAlaQueVolver == 0) {
          ventana=0; //vuelve a la ventana 0 (inicio)
          dibujarPantallaInicio(); //y la pinta
          } else if (ventanaAlaQueVolver == 3) {
            ventana=3;
          }
        }
        compruebaBotonCancelar(0, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio        
       break; //fin caso 4
     
    } //fin switch case ponerEnHora
  } //fin if ventana = 1

  //la ventana 2 muestra y controla las dos alarmas
  if (ventana==2) {
    dibujaAjustarAlarmas(); //dibuja las alarmas
    if (estadoReproduccion == 2) { //si está reproduciendo y se acaba la canción, pasa a la siguiente
    siguienteCancion();
    }
    //bucle para ajustar cada objeto
    switch (ponerAlarma) {
      case 0: //el caso 0 ajusta la hora de la alarma 1
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRoundRect(67,78,168,153);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(alarma1Hora, 70,80,2,'0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta la hora de la alarma 1
          alarma1Hora++;          
        }         
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye la hora de la alarma 1
          alarma1Hora--;
        }
        //controla que los digitos estén comprendidos entre 00 y 23, ambos incluidos
        if (alarma1Hora == 24) {  
          alarma1Hora = 00;
        } 
        if (alarma1Hora == 255) {
          alarma1Hora = 23;
        }        
        utftGLCD.printNumI(alarma1Hora, 70,80,2,'0');          
        
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(67,78,168,153);
          ponerAlarma = 1;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio      
      break; //fin caso 0
      
      case 1: //el caso 1 ajusta los minutos de la alarma 1
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRoundRect(184,78,285,153);
        utftGLCD.setColor(VERDEFOSFORITO);        
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(alarma1Minutos, 186,80,2,'0');          
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta los minutos de la alarma 1
          alarma1Minutos++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye los minutos de la alarma 1
          alarma1Minutos--;
        }
        //controla que los digitos de los minutos estén comprendidos entre 00 y 59, ambos incluidos
        if (alarma1Minutos == 60) {
          alarma1Minutos = 00;
        }
        if (alarma1Minutos == 255) {
          alarma1Minutos = 59;
        }          
        utftGLCD.printNumI(alarma1Minutos, 186,80,2,'0');        
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //Si se pulsa aceptar, cambia al siguiente campo
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(184,78,285,153);
          ponerAlarma=2;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 1

      case 2: //el caso 2 activa o desactiva la alarma 1
        utftGLCD.setColor(ROSA);
        utftGLCD.setFont(BigFont);
        utftGLCD.drawRect(312,88,446,106);
        utftGLCD.setColor(VERDEFOSFORITO);
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, la activa
          alarma1OnOff = true;
          utftGLCD.fillRect(314, 90, 330, 104);
          utftGLCD.print(encendido, 336, 90);
        }          
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa disminuir, la desactiva
          alarma1OnOff = false;
          utftGLCD.setColor(NEGRO);
          utftGLCD.fillRect(314, 90, 330, 104);
          utftGLCD.setColor(VERDEFOSFORITO);
          utftGLCD.drawRect(314, 90, 330, 104);
          utftGLCD.print(apagado,336, 90);
        }         
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente campo
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(312,88,446,106);
          ponerAlarma=3;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 2
      
      case 3: //el caso 3 selecciona entre el buzzer y el reproductor mp3
        utftGLCD.setColor(ROSA);
        if (alarma1TonoMp3) {
          utftGLCD.drawRect(313,114,339,140);
        } else {
          utftGLCD.drawRect(357,114,383,140);
        }
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, pone mp3 como tono de alarma
          alarma1TonoMp3 = false;
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(313,114,339,140);
          utftGLCD.setColor(ROSA);
          utftGLCD.drawRect(357,114,383,140);         
        }          
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa cancelar, pone la chicharra como tono de alarma
          alarma1TonoMp3 = true;
          utftGLCD.setColor(ROSA);
          utftGLCD.drawRect(313,114,339,140);
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(357,114,383,140);
        }         
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          ponerAlarma=4;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 3
      
      case 4: //el caso 4 ajusta la hora de la alarma 2
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRoundRect(67,188,168,263);
        utftGLCD.setColor(VERDEFOSFORITO);
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(alarma2Hora, 70,190,2,'0');
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta la hora de la alarma 2
          alarma2Hora++;
         }        
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye la hora de la alarma 2
          alarma2Hora--;
         }
        //controla que los digitos de la hora están entre 00 y 23, ambos incluidos
        if (alarma2Hora == 24) {
          alarma2Hora = 00;
        }
        if (alarma2Hora == 255) {
          alarma2Hora = 23;
        }        
        utftGLCD.printNumI(alarma2Hora, 70,190,2,'0');        
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente digito
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(67,188,168,263);
          ponerAlarma = 5;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break;
      
      case 5: //ajusta los minutos de la alarma 2
        utftGLCD.setColor(ROSA);
        utftGLCD.drawRoundRect(184,188,285,263);
        utftGLCD.setColor(VERDEFOSFORITO);        
        utftGLCD.setFont(SixteenSegment48x72Num);
        utftGLCD.printNumI(alarma2Minutos, 186,190,2,'0');          
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //aumenta los minutos de la alarma 2
          alarma2Minutos++;
        }
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //disminuye los minutos de la alarma 2
          alarma2Minutos--;
        }
        //controla que los digitos están comprendidos entre 00 y 59, ambos incluidos
        if (alarma2Minutos == 60) {
          alarma2Minutos = 00;
        }
        if (alarma2Minutos == 255) {
          alarma2Minutos = 59;
        }          
        utftGLCD.printNumI(alarma2Minutos, 186,190,2,'0');        
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente campo
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRoundRect(184,188,285,263);
          ponerAlarma=6;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio      
      break; //fin caso 5
      
      case 6: //el caso 6 activa o desactiva la alarma 2
        utftGLCD.setColor(ROSA);
        utftGLCD.setFont(BigFont);
        utftGLCD.drawRect(312,198,446,216);
        utftGLCD.setColor(VERDEFOSFORITO);
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, activa la alarma 2
          alarma2OnOff = true;
          utftGLCD.fillRect(314, 200, 330, 214);
          utftGLCD.print(encendido, 336, 200);
        }          
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa disminuir, desactiva la alarma 2
          alarma2OnOff = false;
          utftGLCD.setColor(NEGRO);
          utftGLCD.fillRect(314, 200, 330, 214);
          utftGLCD.setColor(VERDEFOSFORITO);
          utftGLCD.drawRect(314, 200, 330, 214);
          utftGLCD.print(apagado, 336, 200);
        }         
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, cambia al siguiente campo
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(312,198,446,216);
          ponerAlarma=7;
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 6
            
      case 7: //el caso 7 selecciona entre el tono y el mp3 para la alarma 2
        utftGLCD.setColor(ROSA);
        if (alarma2TonoMp3) { //lee el valor guardado en la EEPROM
          utftGLCD.drawRect(313,224,339,250);
        } else {
          utftGLCD.drawRect(357,224,383,250);
        }
        if (digitalRead(AUMENTARHORACANCION)==HIGH){ //si se pulsa aumentar, pone mp3 como tono de la alarma 2
          alarma2TonoMp3 = false;
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(313,224,339,250);
          utftGLCD.setColor(ROSA);
          utftGLCD.drawRect(357,224,383,250);
        }          
        if (digitalRead(DISMINUYEHORACANCION)==HIGH){ //si se pulsa disminuir, pone la chicharra como tono de la alarma 2
          alarma2TonoMp3 = true;
          utftGLCD.setColor(ROSA);
          utftGLCD.drawRect(313,224,339,250);
          utftGLCD.setColor(NEGRO);
          utftGLCD.drawRect(357,224,383,250);
        }         
        if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){ //si se pulsa aceptar, guarda las alarmas y vuelve a la pantalla de inicio
          utftGLCD.clrScr();
          ventana=0;
          ponerAlarma=0;
          asignarAlarmas();
          dibujarPantallaInicio();
        }
        compruebaBotonCancelar(1, ventanaAlaQueVolver); //si se pulsa cancelar, vuelve a la pantalla de inicio
      break; //fin caso 6*/
      
      } //fin switch case ponerAlarma
  } //fin if ventana = 2

  //ventana del reproductor mp3
  if (ventana == 3) {
    dibujaTemperatura(); //dibuja la temperatura
    dibujaRelojEnMP3(); //dibuja el reloj en el reproductor
    compruebaAlarma(); //comprueba si tiene que saltar alguna alarma
     ventanaAlaQueVolver = 3;    
    if (!alarma1Coincide | !alarma2Coincide) {  //si no hay alarma que tenga que saltar o este activa
      if (estadoReproduccion == 0) { //y el estado de la reproduccion es parado
        drawTrackBar(); //dibuja la barra de reproducción
      } else {
        mostrarTiempoReproduccion(); //en caso contrario, muestra el tiempo transcurrido
      }    
      mostrarModoReproduccion(); //dibuja el modo de reproducción
      mostrarModoEcualizador(); //dibuja el modo de ecualizador
      mp3.setVolume(volumen); //asigna el volumen al reproductor
      //Si se pulsa el boton play, comprueba el estado de la reproducción para iniciar o pausar la reproducción    
      if (digitalRead(ACEPTARPLAYPAUSE)==HIGH){
        //si no hay reproducción activa, empieza a reproducir
        if (estadoReproduccion == 0) {
          drawTrackBar();
          utftGLCD.setColor(AMARILLO);
          utftGLCD.setFont(Various_Symbols_32x32);
          utftGLCD.print("b", (tamanioPantallaAncho/2)-32,150);
          delay(500);
          utftGLCD.print(" ", (tamanioPantallaAncho/2)-32,150);
          if (mReproduccion == 3) { //Si el modo de reproducción es aleatorio
            mp3.playTrackByIndexNumber(random(1,10)); //elige una canción al azar entre la 1 y la 10            
          } else {
            mp3.playTrackByIndexNumber(1);
          }
          siguienteCanc = true; //cambia la variable para que pinte bien la barra de reproducción
          mostrarTiempoReproduccion(); //y llama al método que lo pinta
          estadoReproduccion = 2;
          return;    
        } else if (estadoReproduccion == 2) { //si está reproduciendo, pausa la reproducción
          utftGLCD.setColor(AMARILLO);
          utftGLCD.setFont(Various_Symbols_32x32);
          utftGLCD.print("i", (tamanioPantallaAncho/2)-32,150);
          delay(500);
          utftGLCD.print(" ", (tamanioPantallaAncho/2)-32,150);
          mp3.pause();          
          estadoReproduccion = 1;           
        } else if (estadoReproduccion == 1) { //si la reproducción está pausada, vuelve a reproducir          
          utftGLCD.setColor(AMARILLO);
          utftGLCD.setFont(Various_Symbols_32x32);
          utftGLCD.print("b", (tamanioPantallaAncho/2)-32,150);
          delay(500);
          utftGLCD.print(" ", (tamanioPantallaAncho/2)-32,150);
          mp3.play();
          estadoReproduccion = 2;  
        }
      }
      botonesComunes(); //función que controla los botones comunes a todas las ventanas
         
      //Botón para cambiar a la ventana del reloj desde la ventana del reproductor mp3
      if (digitalRead(CAMBIARARELOJ)==HIGH) {
        utftGLCD.clrScr();
        ventana=0;
        dibujarPantallaInicio();       
      }       
    } else {
      utftGLCD.clrScr();
      ventana = 4;
      return;      
    } //fin bucle alarmas no coinciden
  } //fin ventana 3

  //ventana que muestra los mensajes de las alarmas
  if (ventana == 4) {    
    tiempoTotal = mp3.getTotalTrackPlaybackTime();
    delay(10);
    tiempoTranscurrido = mp3.getElapsedTrackPlaybackTime();
    delay(10);
    if (dibujoAlarma) { //si es verdadero, limpia la pantalla y cambia el valor para no volver a limpiarla
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect(0,0, 480,320);
    dibujoAlarma = false;
    }
    byte segAumentaVol = 5; //5 segundos
    if (alarma1Coincide) { //si la alarma 1 coincide
      utftGLCD.setFont(GroteskBold24x48);
      utftGLCD.setColor(MORADO);
      utftGLCD.print(nombre, 20, 60);
      utftGLCD.setColor(AMARILLO);
      utftGLCD.print(sonLas, 142, 60);
      if (relojActual != rtc.getTimeStr()) {
        utftGLCD.print(rtc.getTimeStr(), (tamanioPantallaAncho/2)-96, 110);
        relojActual = rtc.getTimeStr();
      }
      if (alarma1TonoMp3 & tonoAlarmaReproduciendo == false) { //si el tono es la chicharra y no se está reproduciendo alarma
        while (!cancelarAlarma(1)){ //mientras no se pulse el botón cancelar alarma (le pasa la alarma a cancelar)
          tonoAlarma(); //reproduce la alarma
          tonoAlarmaReproduciendo = true; //indica que está reproduciendo
        }
      } else if (!alarma1TonoMp3) { //si es tono mp3 lo que tiene que reproducir
         if(estadoReproduccion == 2) { //y se está reproduciendo mp3, tocar tono 
           while (!cancelarAlarma(1)){ //minetras no se pulse el botón cancelar alarma
             tonoAlarma(); //reproduce la alarma
             tonoAlarmaReproduciendo = true; //indica que está reproduciendo
           }  
         } else { //si no se está reproduciendo mp3, lo reproduce
           if (tiempoTranscurrido == (segAumentaVol*contador)) { //aumenta cada 5 segundos el volumen un punto, para perezosos
             volAlarm++;
             mp3.setVolume(volAlarm);
             contador++;
           }
           if (estadoReproduccion == 0) { //si no está reproduciendo mp3, pone la primera canción
             mp3.playTrackByIndexNumber(random(1,10)); //elige una canción al azar entre la 1 y la 10            
             estadoReproduccion = 3; //indica el estado actual de reproducción mp3
           }           
           siguienteCancion();
         }
       } //fin if reproducción mp3 alarma 1       
       cancelarAlarma(1); //llama al metodo para cancelar la alarma 1
    }//fin alarma 1 coincide

    if (alarma2Coincide) { //si la alarma 2 coincide con la hora
      utftGLCD.setFont(GroteskBold24x48);
      utftGLCD.setColor(MORADO);
      utftGLCD.print(nombre, 20, 135);
      utftGLCD.setColor(AMARILLO);
      utftGLCD.print(sonLas, 142, 135);
      if (relojActual != rtc.getTimeStr()) {
        utftGLCD.print(rtc.getTimeStr(), (tamanioPantallaAncho/2)-96, 185);
        relojActual = rtc.getTimeStr();
      }
      if (alarma2TonoMp3 & tonoAlarmaReproduciendo == false) { //si el tono es la chicharra y no se está reproduciendo alarma
        while (!cancelarAlarma(2)){ //mientras no se pulse el botón cancelar alarma (le pasa la alarma a cancelar)
          tonoAlarma(); //reproduce el tono de alarma
          tonoAlarmaReproduciendo = true; //indica que está reproduciendo
        }
      } else if (!alarma2TonoMp3) { //si es tono mp3 lo que tiene que reproducir
         if(estadoReproduccion == 2) { //y se está reproduciendo mp3, tocar tono 
           while (!cancelarAlarma(2)){ //mientras no se pulse el botón cancelar alarma
             tonoAlarma(); //reproduce la alarma 
             tonoAlarmaReproduciendo = true; //indica que está reproduciendo
           }  
         } else { //si no se está reproduciendo mp3, lo reproduce
           if (tiempoTranscurrido == (segAumentaVol*contador)) { //aumenta cada 5 segundos el volumen un punto, para perezosos
             volAlarm++;
             mp3.setVolume(volAlarm);
             contador++;
           }
           if (estadoReproduccion == 0) { //si no está reproduciendo mp3, pone la primera canción
             mp3.playTrackByIndexNumber(random(1,10)); //elige una canción al azar entre la 1 y la 10            
             estadoReproduccion = 3; //indica el estado actual de reproducción mp3
           }
           siguienteCancion();
         }
       }//fin if reproducción mp3 alarma 2
       cancelarAlarma(2); //llama al método para cancelar la alarma 2
    }//fin alarma 2 coincide    
  } //fin ventana 4
  
} //fin loop

//Método que controla los botones comunes en las ventanas 0 y 3
void botonesComunes() {
  (ventana==0) ? ejeY=200 : ejeY=150; //Si la ventana es la 0 (reloj) asigna ejeY = 200px, si no, ejeY = 150
  //Si se pulsa el botón stop, muestra un icono de stop en pantalla y para la reproduccion
  if (digitalRead(CANCELARSTOP)==HIGH){
    if (estadoReproduccion == 2 | estadoReproduccion == 1) { //si está reproduciendo o está pausada la reproducción
      utftGLCD.setColor(AMARILLO);
      utftGLCD.setFont(Various_Symbols_32x32);
      utftGLCD.print("j", (tamanioPantallaAncho/2)-ejeX,ejeY);
      dibujadoIcono = true; 
      mp3.stopPlayback();
      estadoReproduccion = 0;            
      if (ventana == 3) { //Si está en la ventana del reproductor
        mostrarTiempoReproduccion(); //cambia los tiempos a 0
      }
      return;      
    } 
    estadoReproduccion = 0;
  }
  //Si se pulsa el botón aumentar cambia a la siguiente canción
  if (digitalRead(AUMENTARHORACANCION)==HIGH){
    mp3.nextTrack();    
    utftGLCD.setColor(AMARILLO);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("h", (tamanioPantallaAncho/2)-ejeX,ejeY);
    dibujadoIcono = true;     
    if (ventana == 3) {     
      siguienteCanc = true; //cambia el valor de la variable para que pinte correctamente la barra
      mostrarTiempoReproduccion(); //y llama al método
    }    
    estadoReproduccion = 2;
  }
  //Si el pulsa el botón disminuir cambia a la canción anterior 
  if (digitalRead(DISMINUYEHORACANCION)==HIGH){
    mp3.previousTrack();
    utftGLCD.setColor(AMARILLO);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("g", (tamanioPantallaAncho/2)-ejeX,ejeY);
    dibujadoIcono = true;    
    if (ventana == 3) {      
      siguienteCanc = true; //cambia el valor de la variable para que pinte correctamente la barra
      mostrarTiempoReproduccion(); //y llama al método
    }
    estadoReproduccion = 2;
  }
  //Este botón se encarga de cambiar entre los diferentes modos de ecualización
  if (digitalRead(CAMBIARECUALIZADOR)==HIGH){
    if (ecualizador <=5) {
      ecualizador++;
      if (ecualizador == 6) {
        ecualizador = 0; 
      }
      mostrarModoEcualizador();
      mp3.setEqualizerProfile(ecualizador); // 0/1/2/3/4/5  Normal/Pop/Rock/Jazz/Classic/Bass
    }
  }
  //Este botón se encarga de los modos de reproducción
  if (digitalRead(CAMBIARMODOREPRODUCCION)==HIGH) {
    if (mReproduccion <= 4) {
      mReproduccion++;
      if (mReproduccion == 5) {
        mReproduccion = 0;
      }
      mostrarModoReproduccion();
      mp3.setLoopPlaybackMode(mReproduccion); // 0/1/2/3/4 All/Folder/Single/Random/Disabled 
    } 
  }
  //Botón para subir el volumen
  if (digitalRead(SUBIRVOLUMEN)==HIGH) { //si se pulsa subir volumen, sube el volumen 2 puntos
    volumen = volumen + 2;
    if(volumen >= 30) { //si el valor de la variable volumen es mayor de 30, le fuerza a 30
      volumen = 30;
    }
    utftGLCD.setColor(AMARILLO);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("o", (tamanioPantallaAncho/2)-ejeX,ejeY);
    dibujadoIcono = true; 
    mp3.setVolume(volumen);
  }
  //Botón para bajar el volumen
  if (digitalRead(BAJARVOLUMEN)==HIGH) { //si se pulsa bajar el volumen, baja el volumen 2 puntos
    volumen = volumen - 2;
    if (volumen == 255 || volumen == 254) { //si el valor de la variable baja de 0 (pasaría a 255) le fuerza a 0
      volumen = 0;
    }
    utftGLCD.setColor(AMARILLO);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("n", (tamanioPantallaAncho/2)-ejeX,ejeY);
    dibujadoIcono = true; 
    mp3.setVolume(volumen);
  } 
  if (digitalRead(AJUSTARRELOJ)==HIGH) { //si se pulsa ajustar el reloj, lanza la ventana de ajuste del reloj
    utftGLCD.clrScr();
    ventana = 1;
  }
  if (digitalRead(AJUSTARALARMA)==HIGH) { //si se pulsa ajustar alarmas, lanza la ventana de ajuste del reloj
    utftGLCD.clrScr();
    ventana = 2;      
  }
  if (dibujadoIcono == true) { //limpiar el icono 
    delay(500);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print(" ", (tamanioPantallaAncho/2)-ejeX,ejeY); 
    dibujadoIcono = false;
  }
}

//A este método se le llama al ajustar la hora o la alarma. Si se le pasa 0, está ajustando la hora. Si se le pasa 1, está ajustando las alarmas
void compruebaBotonCancelar(byte horaOalarma, byte ventanica) {
  if (digitalRead(CANCELARSTOP)==HIGH){ //si se pulsa cancelar, vuelve a la pantalla de inicio
    if (horaOalarma == 0) { //si está en la ventana de ajustar la hora y fecha
      ponerEnHora=0; //inicializa la variable
    } else if (horaOalarma == 1) { //si está en la ventana de ajustar las alarmas
      ponerAlarma=0; //inicaliza la variable
    }
    utftGLCD.clrScr();
    if (ventanica == 0) { //volver a la ventana principal
    ventana=0;
    dibujarPantallaInicio();
    } else if (ventanica == 3) { //volver a la ventana del reproductor
      ventana = 3;
      drawTrackBar();      
    }
  }
}

void obtenerFechaActual() { //método para obtener la fecha actual y asignarla a variables
  fechaActual = rtc.getDateStr(); //obtiene la fecha actual
  //Si la fecha es la fecha por defecto del reloj, asigna la fecha de nacimiento de Nerea como dia
  if (fechaActual == "01.01.2000") {
    rtc.setDate(diaNacimiento, mesNacimiento, anioNacimiento); //asigna la fecha de nacimimiento de Nerea
    fechaActual = rtc.getDateStr();
  }
  dia = fechaActual.substring(0, 2); 
  mes = fechaActual.substring(3, 5);
  anio = fechaActual.substring(6, 10);  
}

//método para cancelar la alarma indicada
bool cancelarAlarma(byte alarma) {
  if (digitalRead(CANCELARALARMA)==HIGH){
      noTone(PINCHICHARRA); // para el sonido de la chicharra
      if (alarma1Coincide & alarma2Coincide) {
        alarma1Coincide = false;
        alarma1OnOff = false;
        alarma2Coincide = false;
        alarma2OnOff = false;
      } else if (alarma == 1) {
        alarma1Coincide = false;
        alarma1OnOff = false;
      } else if (alarma == 2) {
        alarma2Coincide = false;
        alarma2OnOff = false;
      }
      dibujoAlarma = true;
      tonoAlarmaReproduciendo = false;
      contador = 0;
      volAlarm = volumenAlarma;
      actualizarAlarmas();
      if (estadoReproduccion == 0 | estadoReproduccion == 3) {
        mp3.stopPlayback();
      }
      utftGLCD.clrScr();
      if (ventanaAntesAlarma == 3) {
        ventana = 3;
        drawTrackBar();
      } else {
        dibujarPantallaInicio();
        ventana=0;
      }
      return true;
   } else {
     return false; 
   }
}

//Este método muestra el modo en el reproductor mp3 del ecualizador que está activo
void mostrarModoEcualizador() {
  if (ventana == 3) { //Si es la ventana del reproductor
    utftGLCD.setColor(TURQUESA);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("p", 14,282);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(AMARILLO);
    utftGLCD.print(modoEcualizacion[ecualizador], 48, 290); //pinta el texto del modo indicado por la variable ecualizador
  } else if (ventana == 0) { //si es la ventana reloj
    utftGLCD.setColor(TURQUESA);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("p", (tamanioPantallaAncho/2)-ejeX-32,200);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(AMARILLO);
    utftGLCD.print(modoEcualizacion[ecualizador], ((tamanioPantallaAncho/2)-ejeX-32)+34, 208); //pinta el texto del modo indicado por la variable ecualiador
    delay(500);
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect((tamanioPantallaAncho/2)-ejeX-32,200,(tamanioPantallaAncho/2)+(16*10),230); //y lo limpia al medio segundo
  }
}

//Este método muestra el modo de reproducción en el reproductor mp3 que está activo
void mostrarModoReproduccion() {
  if (ventana == 3) { //Si es la ventana del reproductor
    utftGLCD.setColor(TURQUESA);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("_", 262,282);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(AMARILLO);
    utftGLCD.print(modoReproduccion[mReproduccion], 294, 290); //pinta el texto del modo indicado por la variable mReproduccion
  } else if (ventana == 0) { //Si es la ventana del reloj
    utftGLCD.setColor(TURQUESA);
    utftGLCD.setFont(Various_Symbols_32x32);
    utftGLCD.print("p", (tamanioPantallaAncho/2)-ejeX-32,200);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(AMARILLO);
    utftGLCD.print(modoReproduccion[mReproduccion], ((tamanioPantallaAncho/2)-ejeX-32)+34, 208); //pinta el texto del modo indicado por la variable mReproduccion
    delay(500);
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect((tamanioPantallaAncho/2)-ejeX-32,200,(tamanioPantallaAncho/2)+(16*10),230); //y lo limpia al medio segundo
  }
}

//Método para dibujar la barra de reproducción completa en el reproductor mp3
void drawTrackBar() {
  utftGLCD.setColor(TURQUESA);
  utftGLCD.fillRect (48, 100, 428, 125);
}

//Método que comprueba si está reproduciendo. Si se acaba la canción, pone la siguiente
void siguienteCancion() {
  if (ventana != 3) {    
    tiempoTotal = mp3.getTotalTrackPlaybackTime();
    delay(20);
    tiempoTranscurrido = mp3.getElapsedTrackPlaybackTime();
    delay(20);
    tiempoTotal = mp3.getTotalTrackPlaybackTime();
    tiempoTranscurrido = mp3.getElapsedTrackPlaybackTime();
  }  
  //Si la canción llega a fin, dibuja la barra a 0 y lanza la siguiente canción
  if ((estadoReproduccion == 2 & ventana == 3 & ((int)minutosReproducidos == 0 & (int)segundosReproducidos <= 1)) | 
      tiempoTranscurrido == tiempoTotal | 
      tiempoTranscurrido > tiempoTotal) {
    mp3.nextTrack();        
    if (ventana == 3) {
      drawTrackBar();
      tiempoTranscurrido = 0;
      minutosReproducidos = 0;
      segundosReproducidos = 0;
      siguienteCanc = true;
    }    
  }  
}

//Método para mostrar los tiempos de reproducción y el avance en la barra de reproducción
//del reproductor mp3
void mostrarTiempoReproduccion() {
  if (estadoReproduccion == 0) { //Si la reproducción es parada
    minutos = 00;
    segundos = 00;
    reproduccion = 0;
    minutosReproducidos = 0;
    segundosReproducidos = 0;  
  } else { //por el contrario, sino es así
    tiempoTotal = mp3.getTotalTrackPlaybackTime();
    delay(20);
    if (siguienteCanc) {    
      tiempoTranscurrido = 0;
      drawTrackBar();
      siguienteCanc = false;
    } else {  
      tiempoTranscurrido = mp3.getElapsedTrackPlaybackTime();
      delay(20);
    }  
    minutos = (int)tiempoTranscurrido / 60;
    segundos = (((float)tiempoTranscurrido / 60) - minutos) * 60;
    reproduccion = tiempoTotal - tiempoTranscurrido;
    minutosReproducidos = (int)reproduccion / 60;
    segundosReproducidos = (((float)reproduccion / 60) - minutosReproducidos) * 60;    
  }
  utftGLCD.setFont(GroteskBold24x48);
  utftGLCD.setColor(AMARILLO);      
  utftGLCD.printNumI((int)minutos, 48, 48, 2, '0');
  utftGLCD.print(":", 98, 48);
  utftGLCD.printNumI((int)segundos, 124, 48, 2, '0');
  utftGLCD.setFont(Various_Symbols_32x32);
  utftGLCD.print("F", 202, 56);
  utftGLCD.setFont(GroteskBold24x48);
  utftGLCD.print("-", 278, 48);
  utftGLCD.printNumI((int)minutosReproducidos, 304, 48, 2, '0');
  utftGLCD.print(":", 354, 48);
  utftGLCD.printNumI((int)segundosReproducidos, 380, 48, 2, '0');  
  int trackBarX = map(tiempoTranscurrido, 0, tiempoTotal, 0, 380);
  utftGLCD.setColor(ROSA);
  utftGLCD.fillRect(48, 100, 48 + trackBarX, 100 + 25);    
  siguienteCancion(); 
}

//Este método dibuja el reloj en el reproductor mp3
void dibujaRelojEnMP3() {
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.setFont(BigFont);
  if (relojActual != rtc.getTimeStr()) {
    utftGLCD.print(rtc.getTimeStr(), medio, 7);
    relojActual = rtc.getTimeStr();
    horasS = relojActual.substring(0, 2);
    minutosS = relojActual.substring(3, 5);
    segundosS = relojActual.substring(6, 8);
  }     
}

//Método para guardar en la EEPROM las alarmas
void asignarAlarmas() {
  EEPROM.write(0, alarma1Hora); 
  EEPROM.write(1, alarma1Minutos);
  EEPROM.write(2, alarma2Hora);
  EEPROM.write(3, alarma2Minutos);
  EEPROM.write(4, alarma1OnOff);
  EEPROM.write(5, alarma2OnOff);
  EEPROM.write(6, alarma1TonoMp3);
  EEPROM.write(7, alarma2TonoMp3);     
}

//Método para actualizar las alarmas en la EEPROM
void actualizarAlarmas() { 
  EEPROM.update(0, alarma1Hora); 
  EEPROM.update(1, alarma1Minutos);
  EEPROM.update(2, alarma2Hora);
  EEPROM.update(3, alarma2Minutos);
  EEPROM.update(4, alarma1OnOff);
  EEPROM.update(5, alarma2OnOff);
  EEPROM.update(6, alarma1TonoMp3);
  EEPROM.update(7, alarma2TonoMp3);    
}

//Para leer las alarmas y sus estados de la EEPROM
void leerAlarmas() { 
  alarma1Hora = EEPROM.read(0); 
  alarma1Minutos = EEPROM.read(1);
  alarma2Hora = EEPROM.read(2);
  alarma2Minutos = EEPROM.read(3);
  alarma1OnOff = EEPROM.read(4);
  alarma2OnOff = EEPROM.read(5);
  alarma1TonoMp3 = EEPROM.read(6);
  alarma2TonoMp3 = EEPROM.read(7);
}

//Método para pintar las alarmas en la pantalla principal
void pintarAlarmas() {
 if (alarma1OnOff == 1) {
    utftGLCD.drawBitmap(360,10,36,36, alarma_36px);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(TURQUESA);
    utftGLCD.print("1",346,12);
    utftGLCD.printNumI(alarma1Hora,398,25, 2, '0');
    utftGLCD.print(":",428,25);
    utftGLCD.printNumI(alarma1Minutos,442,25, 2, '0');
  } else {
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect(399,9,480,26);    
  }
  if (alarma2OnOff == 1) {
    utftGLCD.drawBitmap(360,50,36,36, alarma_36px);
    utftGLCD.setFont(BigFont);
    utftGLCD.setColor(TURQUESA);
    utftGLCD.print("2",346,52);  
    utftGLCD.printNumI(alarma2Hora,398,65, 2, '0');
    utftGLCD.print(":",428,65);
    utftGLCD.printNumI(alarma2Minutos,442,65, 2, '0');  
  } else {
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect(399,49,480,66);    
  }
}

//Método que comprueba la alarma. Si hay alguna alarma, lanza la ventana de alarma
void compruebaAlarma() {
  leerAlarmas();
  ventanaAntesAlarma = ventana;
  if (alarma1OnOff) {
   if (horasS.toInt() == alarma1Hora && minutosS.toInt() == alarma1Minutos) {
      alarma1Coincide = true;      
      utftGLCD.clrScr();
      utftGLCD.setColor(NEGRO);
      utftGLCD.fillRect(0,0,480,320);      
      ventana = 4;     
    }
  } 
  if (alarma2OnOff) {
   if (horasS.toInt() == alarma2Hora && minutosS.toInt() == alarma2Minutos) {
      alarma2Coincide = true;      
      utftGLCD.clrScr();
      utftGLCD.setColor(NEGRO);
      utftGLCD.fillRect(0,0,480,320);                  
      ventana = 4;     
    }
  }
  obtenerFechaActual();  
  //en caso de ser la fecha de cumpleaños de Nerea, toca el tono de cumpleaños mientras no se esté reproduciendo nada
  //11.09 del año que sea, a las 08:00 y a las 20:00
  if (dia.toInt() == diaNacimiento & mes.toInt() == mesNacimiento & 
      (horasActuales.toInt() == hora1DiaCumple & minutosActuales.toInt() == minuto1DiaCumple | 
       horasActuales.toInt() == hora2DiaCumple & minutosActuales.toInt() == minuto2DiaCumple) 
       & tonoAlarmaReproduciendo == false) {
      tonoAlarmaReproduciendo = true;
      tonoCumpleanios();    
  } else {    
    vueltaTonoCumpleanios = true;
  }   
}

//Este método es para reproducir la melodia de cumpleaños
void tonoCumpleanios(){
  if (vueltaTonoCumpleanios) {
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // delay between notes
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      // time delay between notes
      delay(tempo);
    }
    vueltaTonoCumpleanios = false;    
  } 
  tonoAlarmaReproduciendo = false;
  
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PINCHICHARRA, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PINCHICHARRA, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           
                  'c', 'd', 'e', 'f', 'g', 'a', 'b',
                  'x', 'y' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                  956,  834,  765,  593,  468,  346,  224,
                  655 , 715 };
  int SPEE = 5;

  // play the tone corresponding to the note name
  for (int i = 0; i < 17; i++) {
    if (names[i] == note) {
      int newduration = duration/SPEE;
      playTone(tones[i], newduration);
    }
  }
}

//Método para dibujar la fecha y hora en la ventana de reloj
void dibujaAjustarFechaYhora() {
  utftGLCD.setColor(ROSA);
  utftGLCD.setFont(BigFont);  
  //Cambia el texto del título según en el objeto que se encuentre
  // O HORA/ 1 MINUTOS/ 2 MES/ 3 AÑO/ 4 DIA
  utftGLCD.print(ajustarHoraArray[ponerEnHora], ((tamanioPantallaAncho/2)-((ajustarHoraArray[ponerEnHora].length()*16)/2)), 40);
  //Para dibujar la virgulilla (~) de la ñ en la n de la cadena "ano"
  if (ponerEnHora == 3) {
    utftGLCD.setColor(ROSA);
    utftGLCD.drawLine(medio+100,38, medio+106, 39);
  } else {
    utftGLCD.setColor(NEGRO);
    utftGLCD.drawLine(medio+100,38, medio+106, 39);
  }
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.setFont(SixteenSegment48x72Num);
  utftGLCD.printNumI(digitosHora, 70, 80, 2, '0');
  dibujarPuntosReloj(176, 100, VERDEFOSFORITO);    
  utftGLCD.printNumI(digitosMinutos, 186, 80, 2, '0');
  utftGLCD.printNumI(digitosSegundos, 302, 80, 2, '0');
  utftGLCD.setFont(BigFont);
  utftGLCD.printNumI(digitosDia, medio, 160, 2, '0');
  utftGLCD.print("/",medio+34,160);
  utftGLCD.printNumI(digitosMes, medio+52, 160, 2, '0');
  utftGLCD.print("/",medio+34+18+34,160);
  utftGLCD.printNumI(digitosAnio, medio+104, 160);

}

//Método para dibujar la ventana de ajuste de alarmas
void dibujaAjustarAlarmas() {
  utftGLCD.setColor(ROSA);
  utftGLCD.setFont(BigFont);  
  //Cambia el texto del título según en el objeto que se encuentre
  // 0 HORA ALARMA1/ 1 MINUTOS ALARMA1/ 2 ONOFF ALARMA1/ 3 TONO ALARMA 1
  // 4 HORA ALARMA2/ 5 MINUTOS ALARMA2/ 6 ONOFF ALARMA2/ 7 TONO ALARMA 2
  utftGLCD.print(ajustarAlarmasArray[ponerAlarma], ((tamanioPantallaAncho/2)-((ajustarAlarmasArray[ponerAlarma].length()*16)/2)), 40);
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.setFont(SixteenSegment48x72Num);
  //digitos alarma 1
  utftGLCD.printNumI(alarma1Hora, 70, 80, 2, '0');
  dibujar2PuntosReloj(176, 100, VERDEFOSFORITO);    
  utftGLCD.printNumI(alarma1Minutos, 186, 80, 2, '0');
  //digitos alarma 2
  utftGLCD.printNumI(alarma2Hora, 70, 190, 2, '0');
  dibujar2PuntosReloj(176, 210, VERDEFOSFORITO);    
  utftGLCD.printNumI(alarma2Minutos, 186, 190, 2, '0');
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.setFont(BigFont);
  //iconos y texto alarma 1  
  if (alarma1OnOff) {
    utftGLCD.fillRect(314, 90, 330, 104);
    utftGLCD.print(encendido, 336, 90);
  } else {
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect(314, 90, 330, 104);
    utftGLCD.setColor(VERDEFOSFORITO);
    utftGLCD.drawRect(314, 90, 330, 104);
    utftGLCD.print(apagado,336, 90);
  }
  utftGLCD.drawBitmap(314,115,24,24, chicharra_24px);
  utftGLCD.print("/", 340, 121);
  utftGLCD.drawBitmap(358,115,24,24, musica_24px);
  if (alarma1TonoMp3) {
    utftGLCD.drawRect(313,114,339,140);
  } else {
    utftGLCD.drawRect(357,114,383,140);
  }
  //iconos y texto alarma 2
  if (alarma2OnOff) {
    utftGLCD.fillRect(314, 200, 330, 214);
    utftGLCD.print(encendido, 336, 200);
  } else {
    utftGLCD.setColor(NEGRO);
    utftGLCD.fillRect(314, 200, 330, 214);
    utftGLCD.setColor(VERDEFOSFORITO);
    utftGLCD.drawRect(314, 200, 330, 214);
    utftGLCD.print(apagado,336, 200);
  }
  utftGLCD.drawBitmap(314,225,24,24, chicharra_24px);
  utftGLCD.print("/", 340, 231);
  utftGLCD.drawBitmap(358,225,24,24, musica_24px);
  if (alarma2TonoMp3) {
    utftGLCD.drawRect(313,224,339,250);
  } else {
    utftGLCD.drawRect(357,224,383,250);
  }
}

//Método para dibujar la pantalla de reloj, ventana 0
void dibujarPantallaInicio() {  
  dibujarReloj();
  dibujaFecha();
  dibujaTemperatura();
}

//Métodos para dibujar los puntos del reloj
void dibujarPuntosReloj(int coordX, int coordY, word color) { //dibuja 2 puntos entre hora y minutos y otros 2 entre minutos y segundos
  utftGLCD.setColor(color);
  utftGLCD.fillCircle(coordX, coordY, 4);
  utftGLCD.setColor(color);
  utftGLCD.fillCircle (coordX, coordY+30, 4);
  utftGLCD.setColor(color);
  utftGLCD.fillCircle (coordX+116, coordY, 4);
  utftGLCD.setColor(color);
  utftGLCD.fillCircle (coordX+116, coordY+30, 4);
}


void dibujar2PuntosReloj(int coordX, int coordY, word color) { //dibuja solo dos puntos entre hora y minutos
  utftGLCD.setColor(color);
  utftGLCD.fillCircle(coordX, coordY, 4);
  utftGLCD.setColor(color);
  utftGLCD.fillCircle (coordX, coordY+30, 4);
} 

//Método que dibuja el reloj en la ventana 0
void dibujarReloj() {
  relojActual = rtc.getTimeStr();
  horasActuales = relojActual.substring(0, 2);
  minutosActuales = relojActual.substring(3, 5);
  segundosActuales = relojActual.substring(6, 8);
  utftGLCD.setFont(SixteenSegment48x72Num);
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.print(segundosActuales, 302, 120);
  utftGLCD.print(minutosActuales, 186, 120);
  utftGLCD.print(horasActuales, 70, 120);
  dibujarPuntosReloj(176, 140, VERDEFOSFORITO);
  digitosHora = horasActuales.toInt();
  digitosMinutos = minutosActuales.toInt();
  digitosSegundos = segundosActuales.toInt();  
}

//Dibuja la temperatura en la ventana 0
void dibujaTemperatura() {
  temperatura = rtc.getTemp();
  utftGLCD.setColor(AMARILLO);
  utftGLCD.setFont(BigFont); 
  String stringTemperatura = "";
  stringTemperatura+=String(int(temperatura))+ "."+String(getDecimal(temperatura)); //Convierte el float temperatura a string para mostrar los decimales
  utftGLCD.print(stringTemperatura, 30, 7);
  int sumaStringTemperatura = 30 + (stringTemperatura.length()*16);
  utftGLCD.setBackColor(NEGRO); 
  utftGLCD.setColor(VERDEFOSFORITO); 
  utftGLCD.setFont(BigFont); 
  utftGLCD.print("C", sumaStringTemperatura+2+8, 7);
  utftGLCD.setFont(SmallFont);
  utftGLCD.print("o", sumaStringTemperatura+2, 5); 
  //Emojis según temperatura 
  if (temperatura >= 28.00) {
    utftGLCD.drawBitmap(4,4,24,24, calor_24px);
  } else if (temperatura <= 12.00) {
    utftGLCD.drawBitmap(4,4,24,24, frio_24px);            
  } else if (temperatura > 12.00 && temperatura <= 20.00) {
    utftGLCD.drawBitmap(4,4,24,24, fresquito_24px);
  } else {
    utftGLCD.drawBitmap(4,4,24,24, agustico_24px);
  }
}

//Dibuja la fecha en la ventana 0
void dibujaFecha() {
  obtenerFechaActual();
  rtc.setDOW();  
  //constantes que indican las coordenadas de las dos líneas de la fecha
  //COORDENADAS CONSTANTES X HORIZONTAL Y VERTICAL
  const int ejexlinea1 = 40;
  const int ejeylinea1 = 260;
  const int ejeylinea2 = 280;  
  String mestexto = rtc.getMonthStr(FORMAT_LONG);  
  utftGLCD.setColor(ROSA);
  utftGLCD.setFont(BigFont);
  utftGLCD.setBackColor(NEGRO);
  utftGLCD.print(nombre, ejexlinea1, ejeylinea1);
  utftGLCD.setColor(AMARILLO);
  utftGLCD.setBackColor(NEGRO); 
  int sumhoyes = hoyes.length()*16;
  utftGLCD.print(hoyes,ejexlinea1+(nombre.length()*16),ejeylinea1);
  utftGLCD.print(rtc.getDOWStr(FORMAT_LONG), ejexlinea1+(nombre.length()*16)+2+(hoyes.length()*16)+2, ejeylinea1);             
  utftGLCD.print(dia, ejexlinea1, ejeylinea2);          
  utftGLCD.print(de, ejexlinea1+((dia.length()*16)+2),ejeylinea2);
  utftGLCD.print("                      ", ejexlinea1+((dia.length()*16)+2+(de.length()*16)+2),ejeylinea2);
  utftGLCD.print(mestexto, ejexlinea1+((dia.length()*16)+2+(de.length()*16)+2),ejeylinea2);
  utftGLCD.print(de, ejexlinea1+((dia.length()*16)+2+(de.length()*16)+2+(mestexto.length()*16)+2),ejeylinea2);
  utftGLCD.print(anio, ejexlinea1+((dia.length()*16)+2+(de.length()*16)+2+(mestexto.length()*16)+2+(de.length()*16)+2),ejeylinea2); 
  digitosDia = dia.toInt();
  digitosMes = mes.toInt();
  digitosAnio = anio.toInt();  
}

//Saludo al inicio de encender el parato
void saludo() {
  //Escribe el texto, letra a letra
  utftGLCD.setColor(TURQUESA);
  utftGLCD.setFont(GroteskBold24x48);
  utftGLCD.print("H", 100, 120);
  delay(100);
  utftGLCD.print("o", 124, 120);
  delay(100);
  utftGLCD.print("l", 148, 120);
  delay(100);
  utftGLCD.print("a", 172, 120);
  delay(800);
  //La N en color rosa
  utftGLCD.setColor(ROSA); 
  utftGLCD.print("N", 220, 120);
  delay(100); 
  //resto del nombre en turquesa
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("e", 244, 120);
  delay(100);
  utftGLCD.print("r", 268, 120);
  delay(100);
  utftGLCD.print("e", 292, 120);
  delay(100);
  utftGLCD.print("a", 316, 120);
  delay(500); 
  //empieza el desplazamiento de color desde la "N" a la "a"
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(ROSA); //nerea
  utftGLCD.print("e", 244, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("e", 244, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("r", 268, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("r", 268, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("e", 292, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("e", 292, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("a", 316, 120); //a en rosa
  delay(100);
  //hasta aquí la a en ROSA
  utftGLCD.setColor(ROSA);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA);
  utftGLCD.print("N", 220, 120);
  utftGLCD.setColor(ROSA); //nerea
  utftGLCD.print("e", 244, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("e", 244, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("r", 268, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("r", 268, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("e", 292, 120);
  //hasta aquí ea en ROSA
  utftGLCD.setColor(ROSA);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA);
  utftGLCD.print("N", 220, 120);
  utftGLCD.setColor(ROSA); //nerea
  utftGLCD.print("e", 244, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA); 
  utftGLCD.print("e", 244, 120);
  utftGLCD.setColor(ROSA); //rosa
  utftGLCD.print("r", 268, 120);
  delay(100);
  //hasta aquí rea en ROSA
  utftGLCD.setColor(ROSA);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(TURQUESA);
  utftGLCD.print("N", 220, 120);
  utftGLCD.setColor(ROSA); //nerea
  utftGLCD.print("e", 244, 120);
  delay(100);
  //hasta aquí la  erea en ROSA
  //a partir de aquí cambia de color la letra "N" varias veces
  utftGLCD.setColor(AMARILLO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(NEGRO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(VERDEFOSFORITO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(NEGRO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(ROJO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(NEGRO);
  utftGLCD.print("N", 220, 120);
  delay(100);
  utftGLCD.setColor(MORADO);
  utftGLCD.print("N", 220, 120); 
  delay(1500);
  utftGLCD.setColor(AMARILLO);  
  utftGLCD.setFont(Various_Symbols_32x32); 
  utftGLCD.print("L", 348, 130); //Dibuja emoji sonriendo
  delay(3000);
  utftGLCD.clrScr();
}

//Tono de alarma para el buzzer
void tonoAlarma() {      
  tone(PINCHICHARRA, 4500,2000); 
  delay(100);
  tone(PINCHICHARRA, 3000,200);
  delay(100);
}

//Clase hija para obtener la parte decimal de la temperatura
long getDecimal(float val) {
  int intPart = int(val);
  long decPart = 10 *(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places
                                   //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}
