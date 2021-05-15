#include <stdio.h>
#include "U8g2lib.h"

int main(void)
{
    u8g2_t u8g2;

    // Initializacion
    u8g2_Setup_ssd1306_i2c_128x64_noname_f( &u8g2, U8G2_R0, u8x8_byte_arm_linux_hw_i2c, u8x8_arm_linux_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    // Dibujar
    /* Ejemplo full buffer */
    u8g2_ClearBuffer(&u8g2);

    //Escribimos en la pantalla un texto
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
    u8g2_DrawStr(&u8g2, 1, 18, "Hola Mundo!!");

    //Cambiamos la fuente por una de simbolos e imprimimos uno de ellos
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    u8g2_DrawGlyph(&u8g2, 112, 56, 0x2603 );

    //Mostramos el buffer
    u8g2_SendBuffer(&u8g2);

    printf("Inicializado ...\n");

    return 0;
}
