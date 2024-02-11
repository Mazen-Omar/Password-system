/* 
 * File:   LCD.h
 * Author: Mr_Alsaied
 *
 * Created on 08 February, 2024, 09:09 PM
 */

#ifndef LCD_H
#define	LCD_H


/* ------------------------- Includes -------------------------*/
#include "LCD_cnfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"


/* ------------------------- Macro declarations -------------------------*/
#define _LCD_CLEAR                          0X01
#define _LCD_RETURN_HOME                    0X02
#define _LCD_ENTRY_MODE                     0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON          0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF         0X08
#define _LCD_CURSOR_ON_BLINK_ON             0X0F
#define _LCD_CURSOR_ON_BLINK_OFF            0X0E
#define _LCD_DISPLAY_SHIFT_RIGHT            0X1C
#define _LCD_DISPLAY_SHIFT_LEFT             0X18
#define _LCD_8BIT_MODE_2_LINE               0X38
#define _LCD_4BIT_MODE_2_LINE               0X28
#define _LCD_CGRAM_START                    0X40
#define _LCD_DDRAM_START                    0X80

#define ROW1                                1
#define ROW2                                2
#define ROW3                                3   
#define ROW4                                4

#define ROW_NUMBER                          4
#define COLUMN_NUMBER                       20

/* ------------------------- Data types declaration -------------------------*/
typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;


/* ------------------------- Software interfaces -------------------------*/
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* lcd, uint8* str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t* lcd, uint8 row, uint8 column, uint8* str);
Std_ReturnType lcd_4bit_send_custom_character(const lcd_4bit_t* lcd, uint8 row, uint8 column,
                                              const uint8 chr[], uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t* lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t* lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t* lcd, uint8* str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t* lcd, uint8 row, uint8 column, uint8* str);
Std_ReturnType lcd_8bit_send_custom_character(const lcd_8bit_t* lcd, uint8 row, uint8 column,
                                              const uint8 chr[], uint8 mem_pos);

Std_ReturnType convert_uint8_to_string(uint8 value, uint8* str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8* str);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8* str);



#endif	/* LCD_H */

