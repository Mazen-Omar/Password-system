/* 
 * File:   DC_motor.c
 * Author: Mr_Alsaied
 *
 * Created on 01 January, 2024, 12:07 AM
 */

#include "DC_motor.h"

/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType dc_motor_intitialize(const DC_motor_t* motor)
{
    Std_ReturnType ret = E_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj1 = {.port = motor->DC_motor[0].motor_port , .pin = motor->DC_motor[0].motor_pin,
                             .logic = motor->DC_motor[0].motor_status, .direction = GPIO_DIRECTION_OUTPUT};
        pin_config_t obj2 = {.port = motor->DC_motor[1].motor_port , .pin = motor->DC_motor[1].motor_pin,
                             .logic = motor->DC_motor[1].motor_status, .direction = GPIO_DIRECTION_OUTPUT};
        gpio_pin_initialize(&obj1);
        gpio_pin_initialize(&obj2);
        
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return 
 */
Std_ReturnType dc_motor_move_right(const DC_motor_t* motor)
{
    Std_ReturnType ret = E_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t obj1 = {.port = motor->DC_motor[0].motor_port , .pin = motor->DC_motor[0].motor_pin,
                             .logic = motor->DC_motor[0].motor_status, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t obj2 = {.port = motor->DC_motor[1].motor_port , .pin = motor->DC_motor[1].motor_pin,
                             .logic = motor->DC_motor[1].motor_status, .direction = GPIO_DIRECTION_INPUT};
        gpio_pin_write_logic(&obj1 ,GPIO_HIGH);
        gpio_pin_write_logic(&obj2 ,GPIO_LOW);
        
        ret = E_NOT_OK;
    }
    return ret;
    
}
/**
 * 
 * @param motro
 * @return 
 */
Std_ReturnType dc_motor_move_left(const DC_motor_t* motor)
{
    Std_ReturnType ret = E_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj1 = {.port = motor->DC_motor[0].motor_port , .pin = motor->DC_motor[0].motor_pin,
                             .logic = motor->DC_motor[0].motor_status, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t obj2 = {.port = motor->DC_motor[1].motor_port , .pin = motor->DC_motor[1].motor_pin,
                             .logic = motor->DC_motor[1].motor_status, .direction = GPIO_DIRECTION_INPUT};
        gpio_pin_write_logic(&obj1 ,GPIO_LOW);
        gpio_pin_write_logic(&obj2 ,GPIO_HIGH);
        
        
        ret = E_NOT_OK;
    }
    return ret;
    
}

/**
 * 
 * @param motro
 * @return 
 */
Std_ReturnType dc_motor_stop(const DC_motor_t* motor)
{
    Std_ReturnType ret = E_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj1 = {.port = motor->DC_motor[0].motor_port , .pin = motor->DC_motor[0].motor_pin,
                             .logic = motor->DC_motor[0].motor_status, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t obj2 = {.port = motor->DC_motor[1].motor_port , .pin = motor->DC_motor[1].motor_pin,
                             .logic = motor->DC_motor[1].motor_status, .direction = GPIO_DIRECTION_INPUT};
        gpio_pin_write_logic(&obj1 ,GPIO_HIGH);
        gpio_pin_write_logic(&obj2 ,GPIO_HIGH);
        
        ret = E_NOT_OK;
    }
    return ret;
    
}