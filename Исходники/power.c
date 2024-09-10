void tmr0_init(void)
{
    // Select asynchronous timer 0 operation to use external 32.768 kHz crystal
    BIT_SET_HI(ASSR,AS0);

    // Reset time
    TCNT0 = 0;

    // Calculate and set period
    OCR0 = (uint16)DIV(((F_RTC/8)*TMR0_PERIOD_MS),1000) - 1;

    /* Start timer 0 with clock prescaler CLK/8 and CTC Mode ("Clear Timer on Compare")*/
    /* Resolution is 244.14 us */
    /* Maximum period is 62.5 ms */
    TCCR0 = TMR0_TCCR0_VALUE;

    // Wait for "update busy" flags to clear
    while(ASSR&((1<<TCN0UB)|(1<<OCR0UB)|(1<<TCR0UB)))
    {
        ;
    }

    // Enable interrupt on compare match
    BIT_SET_HI(TIMSK,OCIE0);
}