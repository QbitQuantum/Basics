/*..........................................................................*/
void BSP_init(void) {
    /* NOTE: SystemInit() already called from startup_TM4C123GH6PM.s
    *  but SystemCoreClock needs to be updated
    */
    SystemCoreClockUpdate();

    SYSCTL->RCGC2 |= (1 << 5); /* enable clock to GPIOF (User and Eth LEDs)*/
    __NOP();
    __NOP();

    /* configure the pin driving the Ethernet LED */
    GPIOF->DIR   &= ~(ETH0_LED | ETH1_LED); /* set direction: hardware */
    GPIOF->AFSEL |=  (ETH0_LED | ETH1_LED);
    GPIOF->DR2R  |=  (ETH0_LED | ETH1_LED);
    GPIOF->ODR   &= ~(ETH0_LED | ETH1_LED);
    GPIOF->PUR   |=  (ETH0_LED | ETH1_LED);
    GPIOF->PDR   &= ~(ETH0_LED | ETH1_LED);
    GPIOF->DEN   |=  (ETH0_LED | ETH1_LED);
    GPIOF->AMSEL &= ~(ETH0_LED | ETH1_LED);

    /* configure the pin driving the User LED */
    GPIOF->DIR   |=  USER_LED;  /* set direction: output */
    GPIOF->DR2R  |=  USER_LED;
    GPIOF->DEN   |=  USER_LED;
    GPIOF->AMSEL &= ~USER_LED;
    GPIOF->DATA_Bits[USER_LED] = 0; /* turn the LED off */

    /* configure the pin connected to the Buttons */
    GPIOF->DIR   &= ~USER_BTN;  /* set direction: input */
    GPIOF->DR2R  |=  USER_BTN;
    GPIOF->ODR   &= ~USER_BTN;
    GPIOF->PUR   |=  USER_BTN;
    GPIOF->PDR   &= ~USER_BTN;
    GPIOF->DEN   |=  USER_BTN;
    GPIOF->AMSEL &= ~USER_BTN;

    /* NOTE:
    * The OLED display is encapsulated inside the Table AO, so the
    * initialization of the OLED display happens in the top-most initial
    * transition of the Table AO (see Table_displayInit()).
    */

    if (QS_INIT((void *)0) == 0) {  /* initialize the QS software tracing */
        Q_ERROR();
    }
    QS_OBJ_DICTIONARY(&l_SysTick_Handler);
}