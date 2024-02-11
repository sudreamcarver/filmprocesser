#include <at89x52.h>
/*in sdcc interrupt function should keep in void main*/
void Timer2_ini();
{
    TMOD &= 0xF0;
}