/* 
 * File:   ecu_layer_init.c
 * Author: Mr_Alsaied
 * https://www.linkedin.com/in/mazen-omar-7610a9234/
 * Created on 08 February, 2024, 09:13 PM
 */

#include "ecu_layer_init.h"

lcd_4bit_t lcd = 
{
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTD_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};

    
keypad_t keypad = {
    .keypad_rows_pin[0].port = PORTC_INDEX,
    .keypad_rows_pin[0].pin = GPIO_PIN0,
    .keypad_rows_pin[0].logic = GPIO_LOW,
    .keypad_rows_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[1].port = PORTC_INDEX,
    .keypad_rows_pin[1].pin = GPIO_PIN1,
    .keypad_rows_pin[1].logic = GPIO_LOW,
    .keypad_rows_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[2].port = PORTC_INDEX,
    .keypad_rows_pin[2].pin = GPIO_PIN2,
    .keypad_rows_pin[2].logic = GPIO_LOW,
    .keypad_rows_pin[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[3].port = PORTC_INDEX,
    .keypad_rows_pin[3].pin = GPIO_PIN3,
    .keypad_rows_pin[3].logic = GPIO_LOW,
    .keypad_rows_pin[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_columns_pin[0].port = PORTC_INDEX,
    .keypad_columns_pin[0].pin = GPIO_PIN4,
    .keypad_columns_pin[0].logic = GPIO_LOW,
    .keypad_columns_pin[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[1].port = PORTC_INDEX,
    .keypad_columns_pin[1].pin = GPIO_PIN5,
    .keypad_columns_pin[1].logic = GPIO_LOW,
    .keypad_columns_pin[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[2].port = PORTC_INDEX,
    .keypad_columns_pin[2].pin = GPIO_PIN6,
    .keypad_columns_pin[2].logic = GPIO_LOW,
    .keypad_columns_pin[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[3].port = PORTC_INDEX,
    .keypad_columns_pin[3].pin = GPIO_PIN7,
    .keypad_columns_pin[3].logic = GPIO_LOW,
    .keypad_columns_pin[3].direction = GPIO_DIRECTION_INPUT,
};


led_t led1 = {.port = PORTD_INDEX, .pin = GPIO_PIN6, .status = LED_OFF};
led_t led2 = {.port = PORTD_INDEX, .pin = GPIO_PIN7, .status = LED_OFF};

Button_t start_button = 
{
    .button.port = PORTB_INDEX, 
    .button.pin = GPIO_PIN0,
    .button.logic = GPIO_LOW,
    .button.direction = GPIO_DIRECTION_INPUT,
    .active = BUTTON_ACTIVE_HIGH,
    .state = BUTTON_RELEASED
};


void ecu_layer_initailize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd);
    ret = keypad_initialize(&keypad);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = Button_initialize(&start_button);
}
