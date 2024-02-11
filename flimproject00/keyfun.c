#include "motor.h"
#include <at89x52.h>
#include "LCD1602.h"
extern unsigned char l;
extern unsigned char seconds;
extern unsigned char spend_min;
void keyfunction(unsigned char map)
{
    if (map == 0x00) // rotational speed high
    {
        speed_up();
        LCD_ShowNum(2, 12, map, 1);
    }
    else if (map == 0x01) // rotational speed down
    {
        speed_down();
        LCD_ShowNum(2, 13, map, 1);
    }
    else if (map == 0x02) // motor reverse
    {
        shift_flag_turn();
        LCD_ShowNum(2, 14, map, 1);
    }
    else if (map == 0x03)
    {
        TH1 = !TH1; // turn on timer1
        LCD_ShowNum(2, 15, map, 1);
    }
    else if (map == 0x04) // spend time reset
    {
        // l = 20;
        //seconds = 0;
        //spend_min = 0;
        //LCD_ShowNum(2, 11, map, 1);
    }
}
