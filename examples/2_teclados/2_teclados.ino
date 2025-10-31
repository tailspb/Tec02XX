#define NUMERO_TECLADOS 2
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
  for(char i=0;i<2;i++){
    Serial.print("***lectura del teclado ");
    Serial.print(i+1);
    Serial.println(" ****************");
  Serial.print("la lectura del teclado es: ");
  Serial.println((unsigned int)nuevo_teclado.valorTeclado(i+1));

  Serial.print("la primer tecla oprimida es: ");
  a=nuevo_teclado.primerCaracter(i+1);
  Serial.println(a);

  Serial.print("las otras teclas oprimidas son: ");
  nuevo_teclado.extraerCaracteres(b,3,i+1);
  Serial.print(b[1]);
  Serial.print(" y ");
  Serial.println(b[2]);
  delay(2000);
  }
}

