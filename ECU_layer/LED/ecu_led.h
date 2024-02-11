/* 
 * File:   ecu_led.h
 * Author: Mr_Alsaied
 *
 * Created on November 16, 2023, 12:19 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : includes  */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "led_cfg.h"


/* Section : Macro Declaration */
#define CONFIG_MODE             LED_CONFIG_ENABLE


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */
typedef enum
{
    LED_OFF = 0,
    LED_ON
}led_status_t;

typedef struct 
{
    uint8 port   : 3;
    uint8 pin    : 3;
    uint8 status : 1;
}led_t;


/* Section : Function Declaration */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);



#endif	/* ECU_LED_H */

