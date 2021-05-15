#include <wiringPi.h>
#include "U8g2lib.h"

u8g2_t u8g2;  //Creamos el objeto que representa la pantalla OLED

int main() {
  int x=0;   //Inicializamos  las coordenadas (x y) del texto a imprimir
  int y=10;
  u8g2_Setup_ssd1306_i2c_128x64_noname_f( &u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay); //Configuramos
  u8g2_InitDisplay(&u8g2); //Inicializamos el display
  u8g2_SetPowerSave(&u8g2, 0); //Encendemos la pantalla

  for(;;){  //Bucle infinito
        u8g2_ClearBuffer(&u8g2);  //Limpiamos el contenido de la pantalla
	u8g2_SetFont(&u8g2, u8g2_font_roentgen_nbp_tf);   //Ajustamos la fuente a u8g2_font_roentgen_nbp_tf
	u8g2_FirstPage(&u8g2); //Mostramos la primer pagina
	do {
           if(x==128) x=0;  //Si la coordenada x del texto llego al final de la pantalla, la volvemos al inicio
           u8g2_DrawStr(&u8g2, x++, y,"Hola UCEVA");  //Dibujamos en la pantalla el string Hola UCEVA en las coordenadas (x y)
	} while(u8g2_NextPage(&u8g2));  //Cambiamos a la siguiente pagina
	delay(50);  //Hacemos un retardo de 50ms para dar el efecto de desplazamiento del texto
  }

 return 0;
}
