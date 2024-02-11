#include <at89x52.h>
#include "minsconts.h"
// #include "beeper.h"
#include "LCD1602.h"
#include "DS18b20.h"
#include "pwm.h"
#include "motor.h"
#include "keyfun.h"

//unsigned char out1, out2;
#define out1 P3_0
#define out2 P3_1
float T;
unsigned char l = 20;
unsigned char seconds = 0;
unsigned char target_min = 10;
unsigned char spend_min = 0;
extern unsigned char duty;
extern __bit shift_flag;
#define keycol_0 P1_2 /*io bank*/
#define keycol_1 P1_3 /*io bank*/
#define keycol_2 P1_4 /*io bank*/

#define keyline_0 P1_5 /*io bank*/
#define keyline_1 P1_6 /*io bank*/
#define keyline_2 P1_7 /*io bank*/
unsigned char keyfunmap[3][3] = {
    {0x00, 0x01, 0x02}, {0x03, 0x04, 0x05}, {0x06, 0x07, 0x08}};
unsigned char KeyStatu[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}};

void main(void)
{
    keycol_0 = 1;
    keycol_1 = 1;
    keycol_2 = 1;
    keyline_0 = 0;
    keyline_1 = 0;
    keyline_2 = 0;
    unsigned char i, j;
    unsigned char backup[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};

    LCD_Init();
    Timer0_init();
    LCD_ShowString(1, 11, "min");
    LCD_ShowChar(1, 14, ':');
    LCD_ShowChar(1, 8, '.');
    LCD_ShowString(1, 1, "tem:");
    LCD_ShowString(2, 1, "sec:");
    Timer1_ini();

    while (1)
    {
        /*--------------------------------------------------------------------------------------*/
        for (i = 0; i < 3; i++) // key scan
        {
            for (j = 0; j < 3; j++)
            {
                if (backup[i][j] != KeyStatu[i][j])
                {
                    if (backup[i][j] != 0)
                    {
                        keyfunction(keyfunmap[i][j]);
                    }
                }
            }
        }
        /*--------------------------------------------------------------------------------------*/
        // tempreture put out
        DS18b20_convert_T();  // why dont do this in steps?
        T = DS18b20_read_T(); // whatever,who care.

        if (T > 1)
        {
            LCD_ShowNum(1, 6, T, 2);
            LCD_ShowNum(1, 9, ((unsigned char)(T * 10) % 10), 1);
        }
        /*----------------------------------------------------------------------------------------*/
        LCD_ShowNum(1, 15, target_min, 2);
        LCD_ShowNum(2, 8, l, 2);
        LCD_ShowNum(2, 5, seconds, 2);
    }
}

void Timer0_fun(void) __interrupt 1
{
    unsigned char i;
    static unsigned char keyscannum = 0;
    static unsigned char keybuf[3][3] = {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF}};
    static unsigned char cont; // cont initial to 0
    cont++;
    // 检查键值
    keybuf[keyscannum][0] = (keybuf[keyscannum][0] << 1) | keycol_0;
    keybuf[keyscannum][1] = (keybuf[keyscannum][1] << 1) | keycol_1;
    keybuf[keyscannum][2] = (keybuf[keyscannum][2] << 1) | keycol_2;
    // update keystatu
    for (i = 0; i < 4; i++)
    {
        if ((keybuf[keyscannum][i] & 0x07) == 0x00)
        {
            KeyStatu[keyscannum][i] = 0;
        }
        else if ((keybuf[keyscannum][i] & 0x07) == 0x07)
        {
            KeyStatu[keyscannum][i] = 1;
        }
    }
    keyscannum++;
    if (keyscannum == 3)
        keyscannum = 0;

    switch (keyscannum)
    {
    case 0:
        keyline_0= 1;
        keyline_1= 0;
        break;
    case 1:
        keyline_1 = 1;
        keyline_2 = 0;
        break;
    case 2:
        keyline_2 = 1;
        keyline_0 = 0;
    default:
        break;
    }

    if (cont > 9)
        cont = 0;
    if (shift_flag == 0)
    {

        if (cont < duty)
        {
            out1 = 1;
            out2 = 0;
        }
        else
        {
            out1 = 0;
            out2 = 0;
        }
    }
    else
    {
        if (cont < duty)
        {
            out1 = 0;
            out2 = 1;
        }
        else
        {
            out1 = 0;
            out2 = 0;
        }
    }
    TH0 = 0xF8;
    TL0 = 0xCD;
}
void Timer1_fun(void) __interrupt 3
{
    l--;
    if (l == 0)
    {
        seconds++;
        l = 20;
    }
    if (seconds == 60)
    {
        spend_min++;
        seconds = 0;
    }
    if ((spend_min - 1) == target_min)
    {
        // beeper();
    }
    TL1 = 0x00;
    TH1 = 0x4c; // 50ms
}
