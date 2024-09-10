/*!
 * @brief Delay function used to wait FLL stable.
 */
static void APP_FllStableDelay(void)
{
    volatile uint32_t i = 30000U;
    while (i--)
    {
        __NOP();
    }
}