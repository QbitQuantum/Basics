void resetApplInd(void)
{
#ifdef NO_PRINTF_S
    PUTCHAR('X');
#else
    PRINTF("Application reset\n");
#endif
}