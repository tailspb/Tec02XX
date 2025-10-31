/******************************************************************************
  * @file Tec02XX.h
  * @brief libreria para uso de teclado matricial 4X4 por 3 hilos
  * Este archivo contiene la lógica de escaneo, inicialización y lectura
  * de multiples teclados matriciales 4X4 o 4X2 modelo Tec02"XX" a traves de 3 
  * hilos delvolviendo sus valores, caracteres o teclas oprimidas.
  * @author Diego Portilla B.
  * 
  * Agradezco por el uso de esta "libreria de código libre" para esta familia
  * de dispositivos, espero que les sea de ayuda para proyectos no solo de uso
  * estudiantil sino que pueda ser aplicada en ámbitos industriales, espero 
  * que puedan apoyar obteniendo más productos que vaya desarrollando para
  * poder seguir con más proyectos. Les deseo mucho éxito y cualquier duda o 
  * sugerencia, estoy atento a sus comentarios y sugerencias.
  * "MANIGSER 2025"
  * 
  * La licencia BSD de 3 cláusulas completa se encuentra en Tec02XX.cpp
  * y debe incluirse en cualquier redistribución.

******************************************************************************/
#ifndef TEC02XX_H
#define TEC02XX_H

  #include <Arduino.h>

  //definiciones de los pines que se usaran para comunicarse
/** 
  * @def IN_TEC
  * @brief Pin 8 por default de entrada de datos.
  * Este valor define el pin físico utilizado para recibir datos del teclado,
  * redefinir en el programa principal si se requiere.
*/
  #ifndef IN_TEC
  #define IN_TEC    8 //pin de entrada de datos  
  #endif
/** 
  * @def SET_TEC
  * @brief Pin 9 por default de salida de datos.
  * Este valor define el pin físico utilizado para habilitar la lectura,
  * redefinir en el programa principal si se requiere.
*/
  #ifndef SET_TEC
  #define SET_TEC   9 //conjelar la lectura actual del teclado
  #endif
/** 
  * @def CLK_TEC
  * @brief Pin 10 por default de salida de datos.
  * Este valor define el pin físico utilizado para reloj de datos del teclado,
  * redefinir en el programa principal si se requiere.
*/
  #ifndef CLK_TEC
  #define CLK_TEC   10  //señal de reloj del teclado
  #endif
/** 
  * @def NUMERO_TECLADOS
  * @brief Numero de teclados que se usaran.
  * Este valor define la cantidad de teclados que seran conectados en el controlador,
  * por default esta configurado un unico teclado.
*/
  #ifndef NUMERO_TECLADOS
    #define NUMERO_TECLADOS     1
  #endif
  //cantidad de teclados que se recomiendan manejar, por la naturaleza del
  //programa puede manejar mas de 10 teclados, pero no se recomienda para
  //poder tener mas memoria para otras aplicaciones o debido a limitaciones
  //de ciertos microcontroladores, en caso de necesitar manejar mas se puede
  //modificar la variable unicamente cuidando la memoria del microcontrolador
  #define NO_TECLADOS_MAX   15
  //caracteres de salida ordenados en funcion de la dispocicion
  //de los botones del teclado
/** 
  * @def caracteresSalida
  * @brief Caracteres que se plasmaran en las lecturas comprendidos entre A->p.
*/
  const char caracteresSalida[16] ={'A','B','C','D',
                                    'E','F','G','H',
                                    'I','J','K','L',
                                    'M','N','O','P'};

  //estas son las dos variantes que soportaria el programa, en el armado
  //fisico no se recomienda combinar ambas variantes utilizando el mismo
  //objeto, asi como los pines, la transmicion de datos es serial
  #define VARIANTE_4X4  16
  #define VARIANTE_4X2  8

/** 
  * @def VARIANTE_TECLADO
  * @brief variante de teclado 4X4 o 4X2.
  * Este valor define el que tipo de teclado se implementara,
  * definirlo con "VARIANTE_4X4" o "VARIANTE_4X2_" dependiento el caos,
  * default "VARIANTE_4X4".
*/
  #ifndef VARIANTE_TECLADO
    #define VARIANTE_TECLADO  VARIANTE_4X4
  #endif
  #if NUMERO_TECLADOS>=1 && NUMERO_TECLADOS<=NO_TECLADOS_MAX

/**
    @brief  clase para el manejo del teclado matricial.
*/
    class Tec02XX{
    private:
      const uint8_t inTec=IN_TEC;
      const uint8_t setTec=SET_TEC;
      const uint8_t clkTec=CLK_TEC;
      const uint8_t numeroTeclados=NUMERO_TECLADOS;
      const uint8_t varianteTeclado=VARIANTE_TECLADO;
      uint16_t lecturaTeclado;
      void leerTeclado(uint8_t noTeclado);
      void decodificarCaracteres(char* caracteres,uint8_t longitud);
      uint8_t NumBotAct();
    public:
      void tecladoIniciar(void);
      void extraerCaracteres(char* caracteres,uint8_t longitud);
      void extraerCaracteres(char* caracteres,uint8_t longitud,uint8_t noTeclado);
      char primerCaracter(void);
      char primerCaracter(uint8_t noTeclado);
      uint8_t numBotonesActivos(void);
      uint8_t numBotonesActivos(uint8_t noTeclado);
      uint16_t valorTeclado(void);
      uint16_t valorTeclado(uint8_t noTeclado);
    };
  #else
    #error "numero de teclados invalido"
  #endif
#endif