/* 
 * File:   application.c
 * Author: Mr_Alsaied
 * https://www.linkedin.com/in/mazen-omar-7610a9234/
 * Created on November 16, 2023, 12:24 AM
 */
#include "application.h"


/* ------------------------- Macro declarations ----------------------------*/
#define PASSWORD_LENGTH             3       
#define TRIES_NUMBER                3
#define FAILURE_TIMER               15
#define RESTART_TIMER               3

/* ------------------------- Global variables ------------------------------*/
uint8 password[PASSWORD_LENGTH+1];
uint8 input[PASSWORD_LENGTH+1];
uint8 tries = TRIES_NUMBER;
uint8 select = 0;
uint8 set_flag = 0;
uint8 button_state = BUTTON_RELEASED;
uint8 button_flag = 0;

/* ------------------------- Function declarations -------------------------*/
Std_ReturnType start_system(lcd_4bit_t* LCD, keypad_t* *key);
Std_ReturnType set_password(lcd_4bit_t* LCD, keypad_t* key);
Std_ReturnType enter_password(lcd_4bit_t* LCD, keypad_t* key); 
uint8 compare(uint8* _input, uint8* _password);
void clear_lcd(void);
void clear_buffer(uint8* in);


int main() 
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 cmpr_ret = 0;
    uint8 i = 0;
    application_initialize();
    ret = Button_read(&start_button, &button_state);
    if(button_state == BUTTON_PRESSED)
    {
        button_flag = 1;
    }
    if(button_flag == 1)
    {
        begin : start_system(&lcd, &keypad);
        switch(select)
        {
            case 1 : 
                clear_lcd();
                set_password(&lcd, &keypad);
                select = 0;
                clear_lcd();
                goto begin;
                break;
            case 2 : 
                if(set_flag == 0)
                {
                    clear_lcd();
                    ret = lcd_4bit_send_string(&lcd, "Please set password");
                    ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "first");
                    __delay_ms(1000);
                    clear_lcd();
                    while(set_flag != 1)
                    {
                        start_system(&lcd, &keypad);
                        select = 0;
                        goto begin;
                    }
                }
                else
                {/* nothing */}
                break;
            case 3 :
                
                    clear_buffer(password);
                    clear_lcd();
                    ret = lcd_4bit_send_string(&lcd, "Password cleared");
                    __delay_ms(500);
                    ret = lcd_4bit_send_string_pos(&lcd, 3, 1,  "               ");
                    select = 0;
                    set_flag = 0;
                    goto begin;
                break;
            default : 
                clear_lcd();
                lcd_4bit_send_string(&lcd, "Select again!");
                __delay_ms(1000);
                clear_lcd();
                select = 0;
                led_turn_off(&led1);
                goto begin;
        }
        while(1)
        {
            if(tries == 0)
            {
                uint8 timer = FAILURE_TIMER;
                uint8 timer_str[3];
                clear_lcd();
                lcd_4bit_send_string(&lcd, "Try agian after    s"); 
                while(timer)
                {
                    convert_uint8_to_string(timer ,timer_str);
                    lcd_4bit_send_string_pos(&lcd, 1, 18, timer_str);
                    __delay_ms(1000);
                    timer--;
                    if(timer < 10)
                    {
                        lcd_4bit_send_string_pos(&lcd,1, 19,  "s  ");
                    }
                }                
                tries == TRIES_NUMBER;
            }
            clear_lcd();
            ret = enter_password(&lcd, &keypad);
            cmpr_ret = compare(input, password);
            __delay_ms(1000);
            clear_lcd();
            if(cmpr_ret == 0)
            {
                clear_buffer(input);
                ret = lcd_4bit_send_string_pos(&lcd, 2, 1, "Remaining tries :");
                ret = lcd_4bit_send_char_data_pos(&lcd, 2, 19, tries+47);
                __delay_ms(1000);
                ret = led_turn_off(&led2);
                clear_lcd();
            }
            else
            {
                lcd_4bit_send_string_pos(&lcd, 1 , 8, "Hello!");
                select = 0;
                __delay_ms(RESTART_TIMER*1000);
                goto begin;
            }
            tries--;
    }
    }
    
    return (EXIT_SUCCESS);
}


void application_initialize(void) 
{
    ecu_layer_initailize();
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
        led_turn_on(&led1);
        led_turn_off(&led2);
    }
    else
    {
        clear_lcd();
        lcd_4bit_send_string_pos(&lcd, 2, 9, "Wrong");
        lcd_4bit_send_string_pos(&lcd, 3, 6, "Try again!");
        led_turn_off(&led1);
        led_turn_on(&led2);
    }
    return flag;
}

Std_ReturnType set_password(lcd_4bit_t* LCD, keypad_t* key)
{
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(NULL == LCD || NULL == key)
    {
        ret = E_NOT_OK;
    }
    else
    {
        set_flag = 1;
        ret = lcd_4bit_send_string_pos(LCD, 1, 1, "Set password : ");
        __delay_us(100);
            while(password[l_counter] == 0 && l_counter < PASSWORD_LENGTH)
            {
                ret = keypad_get_value(key, &password[l_counter]);
                if(password[l_counter] != 0)
                {
                    ret = lcd_4bit_send_char_data_pos(LCD, 2, l_counter+1, password[l_counter]);
                    __delay_ms(200);
                    ret = lcd_4bit_send_char_data_pos(LCD, 2, l_counter+1, '*');
                    l_counter++;
                    __delay_ms(200);    
                }
                
            }
         clear_lcd();
        ret = lcd_4bit_send_string(&lcd, "Password done!");
        __delay_ms(750);
        }
    return ret;
}

Std_ReturnType enter_password(lcd_4bit_t* LCD, keypad_t* key)
{
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(NULL == LCD || NULL == key)
    {
        ret = E_NOT_OK;
    }
    else
    {
        clear_buffer(input);
        ret = lcd_4bit_send_string_pos(LCD, 1, 1, "Enter password : ");
        __delay_us(100);
            while(input[l_counter] == 0 && l_counter < PASSWORD_LENGTH)
            {
                ret = keypad_get_value(key, &input[l_counter]);
                if(input[l_counter] != 0)
                {
                    ret = lcd_4bit_send_char_data_pos(LCD, 2, l_counter+1, input[l_counter]);
                    __delay_ms(200);
                    ret = lcd_4bit_send_char_data_pos(LCD, 2, l_counter+1, '*');
                    l_counter++;
                    __delay_ms(200);    
                }
                
            }
        __delay_ms(500);
        }
    return ret;
}

void clear_lcd(void)
{
    lcd_4bit_send_command(&lcd, _LCD_CLEAR);
    __delay_us(100);
}

void clear_buffer(uint8* in)
{
    uint8 j;
    for(j = 0; j < PASSWORD_LENGTH; j++)
    {
        in[j] = 0;
    }
}

Std_ReturnType start_system(lcd_4bit_t* LCD, keypad_t* *key)
{
    Std_ReturnType ret = E_OK;
    if(key == NULL || LCD == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(set_flag == 1)
        {
            ret = lcd_4bit_send_string_pos(&lcd, 3, 1,  "3) Clear password");
        }
        lcd_4bit_send_string_pos(LCD, 1, 1, "1) Set password");
        lcd_4bit_send_string_pos(LCD, 2, 1, "2) Enter password");
        while(!select)
        {
            ret = keypad_get_value(key, &select);
        }
        select = select - 48;
        __delay_ms(150);
    }
    return ret;
}
