# RelojDespertadorMP3
Código fuente del reloj con alarmas, sensor de temperatura y reproductor mp3 que he realizado para mi sobrina. Muestra Hora en formato 24h, fecha con indicación del día en texto (Lunes, Martes...), emojis que cambian según la temperatura recogida, dos alarmas con posibilidad de reproducir mp3 o una melodia, reproductor mp3 y tono de cumpleaños el día del cumpleaños de mi sobrina

Circuitos necesarios:

arduino mega 2560
pantalla de 3.5" tft
placa BY8001-16P reproductor mp3
placa DS3231 reloj con sensor de temperatura



/*   Reloj despertador con dos alarmas, sensor de temperatura y reproductor mp3
 *   creado gardav79 (davidgarant@gmail.com)
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
 *   pantalla de 3.2" táctil por una pantalla de 3.5" sin táctil y 12 botones físicos para realizar las funciones necesarias.
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
 *   libería DS3231 incluyendo tre métodos que se encargan de realizar esa comprobación. Esos métodos son 
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
