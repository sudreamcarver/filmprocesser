#include <at89x52.h>
/*in sdcc interrupt function should keep in void main*/
void Timer1_ini(void)
{
    TMOD &= 0x0F;
    TMOD |= 0x10; // work in mode1(16bit timer)
    TL1 = 0x00;
    TH1 = 0x4c; // 50ms
    TF1 = 0;    // T1 flag
    TR1 = 1;    // turn off timer1,key push then turn on timer1
    ET1 = 1;    // enable interrupt1
    EA = 1;     // global interrupt enable
}