/* 
 * File:   ecu_led.c
 * Author: Mr_Alsaied
 *
 * Created on November 15, 2023, 11:10 PM
 */

#include "ecu_led.h"

/**
 * @brief
 * @param led
 * @return 
 */

#if CONFIG_MODE==LED_CONFIG_ENABLE
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj = {.port = led->port, .pin = led->pin, 
                            .logic = led->status, .direction = GPIO_DIRECTION_OUTPUT};
        gpio_pin_initialize(&obj);
    }
    return ret;
}
#endif

/**
 * @brief
 * @param led
 * @return 
 */

#if CONFIG_MODE==LED_CONFIG_ENABLE
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj = {.port = led->port, .pin = led->pin, 
                            .logic = led->status, .direction = GPIO_DIRECTION_OUTPUT};
        gpio_pin_write_logic(&obj ,GPIO_HIGH);   
    }
    return ret;
}
#endif

/**
 * @brief
 * @param led
 * @return 
 */

#if CONFIG_MODE==LED_CONFIG_ENABLE
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t obj = {.port = led->port, .pin = led->pin, 
                            .logic = led->status, .direction = GPIO_DIRECTION_OUTPUT};
        gpio_pin_write_logic(&obj ,GPIO_LOW); 
    }
    return ret;
}
#endif

/**
 * @brief
 * @param led
 * @return 
 */

#if CONFIG_MODE==LED_CONFIG_ENABLE
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t obj = {.port = led->port, .pin = led->pin, 
                            .logic = led->status, .direction = GPIO_DIRECTION_OUTPUT};
        gpio_pin_toggle_logic(&obj);    
    }
    return ret;
}
#endif
