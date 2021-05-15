#include "U8g2lib.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

u8g2_t u8g2;

// Requerido para imprimirBannerText()
static const char* scroll_text = "UG82 ejecutandose en Raspberry Pi!"; //Mensaje del banner
static u8g2_uint_t scroll_start_x = 255; //X inicial del desplazamiento
static u8g2_uint_t scroll_step_x = 5; //Paso de desplazamiento inicial
static u8g2_uint_t scroll_y = 32; //Desplazamiento en Y
static unsigned int scroll_delay = 500;  //Retardo de desplazamiento


void dibujarU8G2Logo(u8g2_t *u8g2) {
    u8g2_ClearBuffer(u8g2);  //Borramos el contenido de la pantalla
    u8g2_SetFontMode(u8g2, 1);  //Ajustamos la fuente

    u8g2_SetFontDirection(u8g2, 0);  //Ajustamos la direccion de escritura de la fuente
    u8g2_SetFont(u8g2, u8g2_font_inb16_mf);  //Ajustamos la fuente
    u8g2_DrawStr(u8g2, 0, 22, "U"); //Imprimimos el caracter U 

    u8g2_SetFontDirection(u8g2, 1);  //Cambiamos la direccion de escritura a vertical
    u8g2_SetFont(u8g2, u8g2_font_inb19_mn); //Ajustamos la fuente
    u8g2_DrawStr(u8g2, 14, 8, "8");  //Imprimimos el 8 en direccion vertical

    u8g2_SetFontDirection(u8g2, 0); //Normalizamos la direccion de la impresion
    u8g2_SetFont(u8g2, u8g2_font_inb16_mf);  //Cambiamos la fuenta
    u8g2_DrawStr(u8g2, 36, 22, "g");  //Imprimimos el caracter g
    u8g2_DrawStr(u8g2, 48, 22, "\xb2");  //Imprimimos el caracter hexadecimal b2

    u8g2_DrawHLine(u8g2, 2, 25, 34);  //Dibujamos  una linea horizontal
    u8g2_DrawHLine(u8g2, 3, 26, 34);  //Dibujamos otra linea horizontal
    u8g2_DrawVLine(u8g2, 32, 22, 12); //Dibujamos una linea vertical
    u8g2_DrawVLine(u8g2, 33, 23, 12); //Dibujamos otra linea vertical
    u8g2_SendBuffer(u8g2);  //Mostramos en la pantalla lo dibujado en la memoria
}



void imprimirBannerText(u8g2_t *u8g2, uint32_t durationSecs) {

    u8g2_uint_t x = scroll_start_x; //Coordenada X inicial
    uint32_t prevMillis = 0;

    //Ajusta la fuente
    u8g2_SetFont(u8g2, u8g2_font_7x13B_mf);
    uint32_t transcurrido = 0;

    while (transcurrido != durationSecs) {

        uint32_t curMillis = millis();  //Captura el tiempo actual

        //Cuenta el numero de segundos transcurridos
        if ((curMillis - prevMillis) >= 1000) {
            prevMillis = curMillis;
            transcurrido++;
        }

        u8g2_ClearBuffer(u8g2);  //Borra la pantalla
        u8g2_DrawStr(u8g2, x, scroll_y, scroll_text); //Imprime el tecto
        u8g2_SendBuffer(u8g2);  //Muestra lo dibujado en pantalla

        if (x >= scroll_step_x) {  //Si X es mayor o igual que 5
            x -= scroll_step_x;  //Decrementamos en 5 la posicion horizontal del texto
        }
        else {
            x = scroll_start_x; //Ajustamos la posicion X a 255
        }
        delay(scroll_delay);  //Esperamos un tiempo
    }
}


int main(int argc, char* argv[]) {
    //Inicializa Wiring Pi
    wiringPiSetup();

    // Inicializa la pantalla OLED I2C
    u8g2_Setup_ssd1306_i2c_128x64_noname_f( &u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    // Para mejorar el rendimiento de U8g2, puedes cambiar la velocidad del bus I2C a 400 kb/s con la siguiente configuracion.
    // /boot/config.txt: `dtparam=i2c_arm=on,i2c_arm_baudrate=400000`

    // Para imprimirBannerText()
    scroll_text = "Raspberry Pi I2C";
    scroll_start_x = 128;
    scroll_step_x = 8;
    scroll_delay = 100;

    //Inicializa el display
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
    u8g2_ClearDisplay(&u8g2);

    printf("Ejecutando la prueba del display...");

    //Bucle infinito
    while (1) {
        ///Dibuja el logo de U8G2
        dibujarU8G2Logo(&u8g2);
        delay(5000);

        //Ejecutar la animacion del banner de texto
        imprimirBannerText(&u8g2, 20);
    }
    u8g2_ClearDisplay(&u8g2);
}
