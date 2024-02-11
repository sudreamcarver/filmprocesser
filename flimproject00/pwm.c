#include <at89x52.h>
/*in sdcc interrupt function should keep in void main*/
void Timer0_init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01; // T1设置模式1
    TH0 = 0xF8;
    TL0 = 0xCD;
    TF0 = 0; // T0置位标志
    TR0 = 1; // T0 enable
    EA = 1;  // global interrupt switch
    ET0 = 1; // T0 sw
    
}
