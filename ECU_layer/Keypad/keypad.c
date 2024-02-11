
#include "keypad.h"

const uint8 keypad_values[KEYPAD_ROWS_NUMBER][KEYPAD_COLUMNS_NUMBER] = {
        {'7' , '8' , '9' , '/'},
        {'4' , '5' , '6' , '*'},
        {'1' , '2' , '3' , '-'},
        {'#' , '0' , '=' , '+'}
};


/**
 * 
 * @param kpd
 * @return 
 */
Std_ReturnType keypad_initialize(const keypad_t* kpd)
{
    Std_ReturnType ret = E_OK;
    if(kpd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 i;
        for(i = 0; i < KEYPAD_ROWS_NUMBER; i++)
        {
            ret = gpio_pin_initialize(&(kpd->keypad_rows_pin[i]));
        }
        
        for(i = 0; i < KEYPAD_ROWS_NUMBER; i++)
        {
            ret = gpio_pin_direction_initialize(&(kpd->keypad_columns_pin[i]));
        }
        ret = E_OK;
    }
    return ret;
    }
#define ZERO_INIT 0
/**
 * 
 * @param kpd
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value(const keypad_t* _keypad_obj, uint8* value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_rows_counter = ZERO_INIT,l_columns_counter = ZERO_INIT,l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
    if(NULL == _keypad_obj || value == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(l_rows_counter = 0; l_rows_counter < KEYPAD_ROWS_NUMBER; l_rows_counter++)
        {
            for(l_counter = 0; l_counter < KEYPAD_ROWS_NUMBER; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pin[l_counter]), GPIO_LOW);
            }
            gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pin[l_rows_counter]), GPIO_HIGH);
            __delay_ms(10);
            for(l_columns_counter =ZERO_INIT; l_columns_counter < KEYPAD_COLUMNS_NUMBER; l_columns_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pin[l_columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = keypad_values[l_rows_counter][l_columns_counter];
                }
            }
        }
        
    }
    
            
            
    return ret;
}
