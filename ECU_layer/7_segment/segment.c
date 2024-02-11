/* 
 * File:   segment.c
 * Author: Mr_Alsaied
 *
 * Created on 02 February, 2024, 08:45 PM
 */

#include "segment.h"


Std_ReturnType segment_inititalize(const segment_t* seg)
{
    Std_ReturnType ret = E_OK;
    if(seg == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(seg->segment_pin[0]));
        ret = gpio_pin_initialize(&(seg->segment_pin[1]));
        ret = gpio_pin_initialize(&(seg->segment_pin[2]));
        ret = gpio_pin_initialize(&(seg->segment_pin[3]));
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType segment_write_number(const segment_t* seg, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if(seg == NULL  || number > 9)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(seg->segment_pin[0]), ((number >> 0) & 0x01));
        gpio_pin_write_logic(&(seg->segment_pin[1]), ((number >> 1) & 0x01));
        gpio_pin_write_logic(&(seg->segment_pin[2]), ((number >> 2) & 0x01));
        gpio_pin_write_logic(&(seg->segment_pin[3]), ((number >> 3) & 0x01));
        ret = E_OK;
    }
    return ret;
}
    
    