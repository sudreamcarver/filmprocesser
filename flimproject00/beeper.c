#include <at89x52.h>
void beeper(void)
{
    P3_2 = 1;
}

/// @brief turn off beeper
void beeper_off(void)
{
    P3_2 = 0;
}