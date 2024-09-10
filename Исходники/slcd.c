static void SLCD_TimeDelay(uint32_t count)
{
    while (count--)
    {
        __NOP();
    }
}