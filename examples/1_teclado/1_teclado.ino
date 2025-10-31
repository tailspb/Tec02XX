/*///////////////////////////pines por defecto:
pin 8   Dout
pin 9   SEL
pin 10  CLK
////////////////////////////cambiar pociciones
#define IN_TEC <no pin>
#define SET_TEC <no pin>
#define CLK_TEC <no pin>

*/
#include <Tec02XX.h>

Tec02XX nuevo_teclado;

void setup() {
  nuevo_teclado.tecladoIniciar();
  Serial.begin(9600);
}

void loop() {
  char a;
  char b[3];
  Serial.println("*******************************************");
  Serial.print("la lectura del teclado es: ");
  Serial.println((unsigned int)nuevo_teclado.valorTeclado());

  Serial.print("la primer tecla oprimida es: ");
  a=nuevo_teclado.primerCaracter();
  Serial.println(a);

  Serial.print("las otras teclas oprimidas son: ");
  nuevo_teclado.extraerCaracteres(b,3);
  Serial.print(b[1]);
  Serial.print(" y ");
  Serial.println(b[2]);

  Serial.print("el numero de teclas opriidas son: ");
  Serial.println(nuevo_teclado.numBotonesActivos());
  delay(1000);
}

