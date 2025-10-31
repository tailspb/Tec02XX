/******************************************************************************
  * @file Tec02XX.cpp
  * @author Diego Portilla B. (industrias manigser)
  * @date 2025-10-17
  * @mainpage controlador de teclado matricial 
  * @section author Author
  * escrito por Diego Portilla de industrias MANIGSER
  * @section HISTORY
  * 
  * v1.0  - primer lanzamiento
  * 
  * @copyright
  * Copyright (c) 2025, Diego Portilla B.
  * Todos los derechos reservados.
  *
  * @section license License
  * Se permite la redistribución y el uso en formas de código fuente y binario,
  * con o sin modificaciones, siempre que se cumplan las siguientes
  * condiciones:
  *
  * 1. Las redistribuciones del código fuente deben conservar el aviso de
  * copyright anterior, esta lista de condiciones y el siguiente descargo de
  * responsabilidad.
  *
  * 2. Las redistribuciones en formato binario deben reproducir el aviso de
  * copyright anterior, esta lista de condiciones y el siguiente descargo de
  * responsabilidad en la documentación y/o en otros materiales proporcionados
  * con la distribución.
  *
  * 3. Ni el nombre de Diego Ares ni los nombres de sus colaboradores pueden
  * ser utilizados para respaldar o promocionar productos derivados de este 
  * software sin permiso previo y por escrito.
  *
  * ESTE SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍAS DE NINGÚN TIPO,
  * EXPRESAS O IMPLÍCITAS, INCLUYENDO, PERO NO LIMITÁNDOSE A, GARANTÍAS DE
  * COMERCIALIZACIÓN E IDONEIDAD PARA UN PROPÓSITO PARTICULAR. EN NINGÚN CASO
  * LOS AUTORES O TITULARES DEL COPYRIGHT SERÁN RESPONSABLES POR NINGÚN DAÑO
  * DIRECTO, INDIRECTO, INCIDENTAL, ESPECIAL, EJEMPLAR O CONSECUENTE 
  * (INCLUYENDO, PERO NO LIMITÁNDOSE A, LA ADQUISICIÓN DE BIENES O SERVICIOS
  * SUSTITUTOS; LA PÉRDIDA DE USO, DATOS O BENEFICIOS; O LA INTERRUPCIÓN DE LA
  * ACTIVIDAD COMERCIAL), SEA CUAL SEA LA CAUSA Y BAJO CUALQUIER TEORÍA DE
  * RESPONSABILIDAD, YA SEA POR CONTRATO,RESPONSABILIDAD ESTRICTA O AGRAVIO
  * (INCLUYENDO NEGLIGENCIA U OTRO), QUE SURJA DE CUALQUIER MANERA DEL USO DE
  * ESTE SOFTWARE, INCLUSO SI SE HA ADVERTIDO DE LA POSIBILIDAD DE TALES DAÑOS.
  * 
******************************************************************************/
#include "Tec02XX.h"
/**
  * @brief Lee el teclado seleccionado.
  * Se encarga de realizar la lectura del teclado convirtiendo los estados de
  * los botones en un int16 indicando en cada bit el estado del botón.
  * @param noTeclado Indica el teclado que se leerá, el rango admisible es 
  *                  1 ≤ noTeclado ≤ numeroTeclados.
  * @note Al ser una lectura en serie, se va a realizar un barrido por cada uno
  * de los teclados hasta llegar al teclado que se leerá.
  * @note Función privada.
*/
void Tec02XX::leerTeclado(uint8_t noTeclado){
  digitalWrite(setTec,LOW);
  digitalWrite(clkTec,LOW);
  digitalWrite(setTec,HIGH);
  for(uint8_t i=(varianteTeclado*noTeclado);i;i--){
    lecturaTeclado<<=1;
    if(digitalRead(inTec)){
      lecturaTeclado++;
    }
    digitalWrite(clkTec,HIGH);
    //delay(5);
    digitalWrite(clkTec,LOW);
    //delay(5);
  }
  digitalWrite(setTec,LOW);
  digitalWrite(clkTec,LOW);
}
/**
  * @brief Traduce la lectura del teclado en caracteres comprensibles.
  * Traduce la lectura del teclado en 1->"longitud" caracteres almacenando las
  * letras en el espacio de memoria donde se compartió el apuntador.
  * @param caracteres Puntero al vector o variable donde se almacenaran los 
  *                   caracteres de la decodificación del valor del teclado, 
  *                   esta debe ser de tipo char.
  * @param longitud Longitud del vector donde se almacenaran los caracteres.
  * @note Se escribirán los caracteres de las teclas oprimidas hasta completar
  * la longitud del vector, el resto de teclas oprimidas serán despreciadas, 
  * ejemplo: longitud=3 y se oprimen los botones 1,3,5,7, solo se traducirán 
  * las lecturas de los botones 1,3,5. 
  * @note La función borrará toda la información que se tenga en el vector, si
  * no se oprimen la cantidad de botones indicada en "longitud" los espacios de 
  * memoria conservarán con valor 0.
  * @note Al finalizar la función el puntero tendrá el valor de la última 
  * posición del arreglo. 
  * @note el valor máximo de "longitud" será de "varianteTeclado", si se pasa un
  * valor mayor, se tomará por defecto el valor máximo.
  * @note Función privada.
  * @warning El parámetro "longitud" debe ser menor o igual al tamaño del
  * arreglo, de otro modo se sobreescribirá en partes de la memoria de otras
  * funciones, pudiendo provocar problemas de código en tiempo de ejecución.
*/
void Tec02XX::decodificarCaracteres(char* caracteres,uint8_t longitud){
  uint16_t aux_0=1;
  char* aux_1=caracteres;
  if(longitud>varianteTeclado)
    longitud=varianteTeclado;
  for(uint8_t i=longitud;i;i--)
    *aux_1++=0;
  for(uint8_t i=varianteTeclado;i && longitud;i--){
    if(lecturaTeclado & aux_0){
      *caracteres++=caracteresSalida[16-i];
      longitud--;
    }
    aux_0<<=1;
  }
}
/**
  * @brief Regresa el número de botones oprimidos.
  * @return Regresa el número de botones oprimidos en el teclado.
  * @note Función privada.
*/
uint8_t Tec02XX::NumBotAct(){
  uint8_t a=0;
  uint16_t b=1;
  for(uint8_t i=VARIANTE_TECLADO;i;i--){
    if(lecturaTeclado&b)
      a++;
    b<<=1;
  }
  return a;
}
/**
  * @brief Configura los pines de comunicación.
  * @note Para cambiar los pines de comunicación se deben definir al principio
  * del programa antes de incluir la biblioteca de la siguiente forma:
  * #define IN_TEC <pin>    <-es un pin de entrada de datos del MCU
  * #define SET_TEC <pin>   <-es un pin de salida de datos del MCU
  * #define CLK_TEC <pin>   <-es un pin de salida de datos del MCU
  * #include <el_nombre_de_la_biblioteca.h>
 */
void Tec02XX::tecladoIniciar(void){
  pinMode(inTec,INPUT);
  pinMode(clkTec,OUTPUT);
  pinMode(setTec,OUTPUT);
}
/**
  * @brief Traduce la lectura del teclado 1 en caracteres comprensibles.
  * @param caracteres Puntero al vector o variable donde se almacenaran los 
  *                   caracteres de la decodificación del valor del teclado, 
  *                   está debe ser de tipo char.
  * @param longitud Longitud del vector donde se almacenaran los caracteres.
  * @note Esta función tiene la misma nota que la función 
  * "decodificarCaracteres()".
  * @warning Esta función tiene la misma advertencia que la función
  * "decodificarCaracteres()".
 */
void Tec02XX::extraerCaracteres(char* caracteres,uint8_t longitud){
  leerTeclado(1);
  decodificarCaracteres(caracteres,longitud);
}
/**
  * @brief Traduce la lectura del teclado "n" en caracteres comprensibles.
  * @param caracteres Puntero al vector o variable donde se almacenaran los 
  *                   caracteres de la decodificación del valor del teclado, 
  *                   esta debe ser de tipo char.
  * @param longitud Longitud del vector.
  * @param noTeclado Se indica el teclado con el cual se trabajará, debe estar
  *                  en un rango de 1 ≤ noTeclado ≤ numeroTeclados.
  * @note Si "noTeclado" está fuera de rango, no realizará nada la función.
  * @note Esta función tiene la misma nota que la función 
  * "decodificarCaracteres()"
  * @warning Esta función tiene la misma advertencia que la función
  * "decodificarCaracteres()".
*/
void Tec02XX::extraerCaracteres(char* caracteres,uint8_t longitud,uint8_t noTeclado){
  if(noTeclado>=1 && noTeclado<=numeroTeclados){
    leerTeclado(noTeclado);
    decodificarCaracteres(caracteres,longitud);
  }
}
/**
  * @brief Devuelve el primer carácter qué está oprimido del teclado 1.
  * @return Devuelve una letra entre A->P.
  * @note Realiza un barrido de los botones que están oprimidos, y el primer
  * botón qué esté oprimido devolverá su valor correspondiente.
*/
char Tec02XX::primerCaracter(void){
  char a;
  leerTeclado(1);
  decodificarCaracteres(&a,1);
  return a;
}
/**
  * @brief Devuelve el primer carácter qué está oprimido del teclado "n".
  * @param noTeclado Se indica el teclado con el cual se trabajará, debe estar
  *                  en un rango de 1 ≤ noTeclado ≤ numeroTeclados.
  * @return Devuelve una letra entre A->P.
  * @note Realiza un barrido de los botones que están oprimidos, y el primer
  * botón qué esté oprimido devolverá su valor correspondiente.
  * @note Si "noTeclado" está fuera del rango, devolverá 0
*/
char Tec02XX::primerCaracter(uint8_t noTeclado){
  if(noTeclado>=1 && noTeclado<=numeroTeclados){
    char a;
    leerTeclado(noTeclado);
    decodificarCaracteres(&a,1);
    return a;
  }
  else
    return 0;
}
/**
  * @brief Devuelve el número de botones oprimidos del teclado 1.
  * @return Regresa el número de botones oprimidos en el teclado.
*/
uint8_t Tec02XX::numBotonesActivos(void){
  leerTeclado(1);
  return NumBotAct();
}
/**
  * @brief Devuelve el número de botones oprimidos del teclado "n".
  * @param noTeclado Se indica el teclado con el cual se trabajará, debe estar
  *                  en un rango de 1 ≤ noTeclado ≤ numeroTeclados.
  * @return Regresa el número de botones oprimidos en el teclado.
  * @note si "noTeclado" está fuera del rango devuelve 0
*/
uint8_t Tec02XX::numBotonesActivos(uint8_t noTeclado){
  if(noTeclado>=1 && noTeclado<=numeroTeclados){
    leerTeclado(noTeclado);
    return NumBotAct();
  }
  else
  return 0;
}
/**
  * @brief Devuelve el valor decimal del teclado 1.
  * @return Regresa el valor decimal del teclado en un uint16.
*/
uint16_t Tec02XX::valorTeclado(void){
  leerTeclado(1);
  return lecturaTeclado;
}
/**
  * @brief Devuelve el valor decimal del teclado "n".
  * @param noTeclado Se indica el teclado con el cual se trabajará, debe estar
  *                  en un rango de 1 ≤ noTeclado ≤ numeroTeclados.
  * @return Regresa el valor decimal del teclado en un uint16.
  * @note si "noTeclado" está fuera del rango, devolvera 0
*/
uint16_t Tec02XX::valorTeclado(uint8_t noTeclado){
  if(noTeclado>=1 && noTeclado<=numeroTeclados){
    leerTeclado(noTeclado);
    return lecturaTeclado;
  }
  else
    return 0;
}