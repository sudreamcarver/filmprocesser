unsigned char duty = 10;
__bit shift_flag = 0;
void speed_up(void)
{
    duty++;
    if (duty > 10)
        duty = 10;
}
void speed_down(void)
{
    duty--;
    if (duty < 1)
        duty = 1;
}
void shift_flag_turn(void)
{
    shift_flag = !shift_flag;
}