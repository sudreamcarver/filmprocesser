unsigned char duty = 7;
__bit shift_flag = 0;
void speed_up(void)
{
    duty++;
    if (duty > 9)
        duty = 9;
}
void speed_down(void)
{
    duty--;
    if (duty < 5)
        duty = 5;
}
void shift_flag_turn(void)
{
    shift_flag = !shift_flag;
}