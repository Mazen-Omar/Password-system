/* 
 * File:   LCD.c
 * Author: Mr_Alsaied
 *
 * Created on 08 February, 2024, 09:09 PM
 */

#include "LCD.h"


static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* lcd ,uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* lcd, uint8 row, uint8 column); 


/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    { 
        uint8 i;
        ret = gpio_pin_initialize(&(lcd->lcd_rs));              //Initialization of RS pin
        ret = gpio_pin_initialize(&(lcd->lcd_en));              //Initialization of RS pin
        for(i = 0; i < 4; i++)                                  
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[i]));          //Initialization of the Data pins
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);                         //To validate the place of the first letter.
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);         // RS = 0, To select instruction register
        ret = lcd_send_4bits(lcd, (command >> 4));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);         // RS = 1, To select data register
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t* lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
       
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* lcd, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t* lcd, uint8 row, uint8 column, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || str == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_string(lcd, str);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_character(const lcd_4bit_t* lcd, uint8 row, uint8 column,
                                              const uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 i;
        ret = lcd_4bit_send_command(lcd, ((_LCD_CGRAM_START)+(mem_pos*8)));  //Determining  the address where the chr will be store
        for(i = 0; i <= 7; i++)
        {
            ret = lcd_4bit_send_char_data(lcd, chr[i]);         //Sending the data to the CGRAM.
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/* ------------------------------------------------------ 8bit -------------------------------------------------------*/
/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 i;
        ret = gpio_pin_initialize(&(lcd->lcd_rs));              //Initialization of RS pin
        ret = gpio_pin_initialize(&(lcd->lcd_en));              //Initialization of EN pin
        for(i = 0; i < 8; i++)                          
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[i]));     //Initialization of the Data pins
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);             //To validate the place of the first letter.
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 i = 0;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);           //To select the instruction register
        for(i = 0; i < 8; i++)                  
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[i]), (command >> i) & (uint8)0x01);      //Sending the data
        }
        ret = lcd_8bit_send_enable_signal(lcd);                                                 //Sending enable signal
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t* lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 i;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);                              //To select the data register
        for(i = 0; i < 8; i++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[i]), (data >> i) & (uint8)0x01);     //Sending the data
        }
        ret = lcd_8bit_send_enable_signal(lcd);                                             //Sending enable signal
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t* lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t* lcd, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t* lcd, uint8 row, uint8 column, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL || str == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_string(lcd, str);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_character(const lcd_8bit_t* lcd, uint8 row, uint8 column,
                                              const uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 i = 0;
    if(lcd == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER  || chr == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));       //Determining the address of the letter in CGRAM
        for(i = 0; i <= 7; ++i)
        {
            lcd_8bit_send_char_data(lcd, chr[i]);                               //Sending the data to the 
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 4);       //The maximum number of digits is 3 + null termination, we set null termination to the whole string.
        sprintf(str, "%i", value);  // This function will convert the value into the string and stores it in str.
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 5);       //The max value is 65,*** + null termination . So, the max number of digits is 6
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8* str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 11);  // Max number is 10 digits + null termination, the max number of digits is 11
        sprintf(str, "%i", value);
    }
    return ret;
}

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* lcd ,uint8 data_command)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data_command >> 0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data_command >> 1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data_command >> 2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data_command >> 3) & (uint8)0x01);
    }
    return ret;
}
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
                         /* Triggering */
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
                         /* Triggering */
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(lcd == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80 + column)); break;   //0x80 is the begging address of row 1
            case ROW2:  ret = lcd_8bit_send_command(lcd, (0xC0 + column)); break;   //0xC0 is the begging address of row 2
            case ROW3 : ret = lcd_8bit_send_command(lcd, (0x94 + column)); break;   //0x94 is the begging address of row 3
            case ROW4 : ret = lcd_8bit_send_command(lcd, (0xd4 + column)); break;   //0xd4 is the begging address of row 4
            default : break;
        }
    }
    
    return ret;
}


static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
    if(lcd == NULL || row > ROW_NUMBER || column > COLUMN_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(row)
        {
            case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;   //0x80 is the begging address of row 1
            case ROW2:  ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;   //0xC0 is the begging address of row 2
            case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;   //0x94 is the begging address of row 3
            case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + column)); break;   //0xd4 is the begging address of row 4
            default : break;
        }
    }
    
    return ret;
}