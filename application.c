/* 
 * File:   application.c
 * Author: Mr_Alsaied
 *
 * Created on November 16, 2023, 12:24 AM
 */
#include "application.h"


/* ------------------------- Global variables -------------------------*/
#define _CURSOR             2
#define PASSWORD_LENGTH     5

/* ------------------------- Global variables -------------------------*/
uint8 password[PASSWORD_LENGTH+1];
uint8 input[PASSWORD_LENGTH+1];
uint8 flag[4] = {0};
uint8 tries = 3;
uint8 tries_txt[4];
uint8 i = _CURSOR;

/* ------------------------- Function declarations -------------------------*/
void set_password(void);
void enter_password(void);
static void read_input(uint8* input,uint8* flag);
void read_inputs(void);
void clear_lcd(void);
uint8 compare(uint8* _input, uint8* _password);


int main() 
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 cmpr_ret = 0;
    application_initialize();
    if(tries==3) set_password();
    
    while(tries--)
    {
        clear_lcd();
        enter_password();
        cmpr_ret = compare(input, password);
        __delay_ms(750);
        ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
        if(cmpr_ret == 0)
        {
            ret = lcd_4bit_send_string_pos(&lcd, 2, 7, "Tries :");
            ret = convert_uint8_to_string(tries, tries_txt);
            ret = lcd_4bit_send_string_pos(&lcd, 2, 15, tries_txt);
            __delay_ms(750);
            clear_lcd();
        }
        else
        {
            break;
        }
    }
    return (EXIT_SUCCESS);
}


void application_initialize(void) {
    ecu_layer_initailize();
}

static void read_input(uint8* input,uint8* flag)
{
    *flag = 0;
    while(1)
        {
            keypad_get_value(&keypad, input);
            if(*input != 0)
            {
                *flag = 1;
                lcd_4bit_send_char_data_pos(&lcd, 3, i, *input);
                i++;
                break;
            }
        }
}

void read_inputs(void)
{
    while (1) 
    {
        uint8 l_counter;
        for(l_counter = 0; l_counter < PASSWORD_LENGTH; ++l_counter)
        {
            read_input(&input[l_counter] ,&flag[l_counter]);
            __delay_ms(200);
        }
        
            if(flag[0] && flag[1]  && flag[2] && flag[3]) break;
    }
    flag[0], flag[1], flag[2], flag[3] = 0;
}

uint8 compare(uint8* _input, uint8* _password)
{
    uint8 flag = 1;                                
    uint8 l_counter = 0;
    for(l_counter = 0; l_counter < PASSWORD_LENGTH; ++l_counter)
    {
        if(_input[l_counter] != _password[l_counter]) 
        {
            flag = 0; 
            break;    
        }
    }
    if(flag == 1)
    {
        clear_lcd();
        lcd_4bit_send_string_pos(&lcd, 2, 7, "Correct");
    }
    else
    {
        clear_lcd();
        lcd_4bit_send_string_pos(&lcd, 2, 9, "Wrong");
        lcd_4bit_send_string_pos(&lcd, 3, 6, "Try again!");
    }
    return flag;
}


void set_password(void)
{
    i = _CURSOR;
    lcd_4bit_send_string(&lcd, "Set Password : ");
    while(1)
    {
        uint8 l_counter;
        for(l_counter = 0; l_counter < PASSWORD_LENGTH; ++l_counter)
        {
            read_input(&password[l_counter] ,&flag[l_counter]);
            __delay_ms(200);
        }
             
        if(flag[0] && flag[1]  && flag[2] && flag[3]) break;
        flag[0], flag[1], flag[2], flag[3] = 0;
    }
    clear_lcd();
    lcd_4bit_send_string(&lcd, "Password done!");
    __delay_ms(750);
}

void enter_password(void)
{
    i = _CURSOR;
    lcd_4bit_send_string(&lcd, "Enter Password : ");
    memset(input, '\0', 5);     //Clearing output buffer
    read_inputs();
}

void clear_lcd(void)
{
    lcd_4bit_send_command(&lcd, _LCD_CLEAR);
    __delay_us(100);
}