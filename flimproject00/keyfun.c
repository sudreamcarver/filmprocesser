#include "motor.h"
#include <at89x52.h>
#include "LCD1602.h"
#include "beeper.h"
extern unsigned char l;
extern unsigned char target_min;
extern char seconds;
extern unsigned char spend_min;
void keyfunction(unsigned char map)
{
    if (map == 0x00) // rotational speed high
    {
        speed_up();
    }
    else if (map == 0x01) // rotational speed down
    {
        speed_down();
    }
    else if (map == 0x02) // motor reverse
    {
        shift_flag_turn();
    }
    else if (map == 0x03)
    {
        TH1 = !TH1; // turn on timer1
    }
    else if (map == 0x04) // spend time reset,turn off beeper
    {
        l = 20;
        seconds = 0;
        spend_min = 0;
        beeper_off();
    }
    else if (map == 0x05) // process time up
    {
        target_min++;
    }
    else if (map == 0x06) // process time down
    {
        target_min--;
    }
}
