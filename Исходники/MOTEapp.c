static uint8_t moteApp_GoToSleep(void)
{
    uint8_t status = 0;
    while (SWITCH_2_PORT == 0);     // Hold for Button Release
    modemSleep();
    oled_displayOff(true); 
    ADCON0bits.ADON = 0;       // ADC Off
    INTCONbits.GIE = 0;
    GIE = 0;
    PEIE = 0;
    // Prepare USB Detect
    USB_DET_ANSEL = 1;
    // Prepare IOC to wake us up
    USB_DET_EN = 1;      // Enables CMP1 interrupt.
    SWITCH_1_IOC = 1;
    SWITCH_2_IOC = 1;
    MODEM_WAKE_IOC = 1;
    IOC_ENABLE = 1;
    // Dummy Reads to Establish IOC level
    status = SWITCH_1_PORT;
    status = SWITCH_2_PORT;
    status = MODEM_WAKE_PORT;
    if (periodicState)
    {
        //WDTCONbits.SWDTEN = 1;
    }
    IOC_FLAG = 0;
    USB_DET_FLAG = 0;
    NOP();
    SLEEP();
    NOP();
    // Reconfigure Critical peripherals
    //WDTCONbits.SWDTEN = 0;
    EUSART_FlushBuffer();
    // Disable IOC
    IOC_ENABLE = 0;
    SWITCH_1_IOC = 0;
    SWITCH_2_IOC = 0;
    MODEM_WAKE_IOC = 0;
    PIE2bits.C1IE = 0;
    GIE = 1;

    PIN_MANAGER_Initialize();
    EUSART_Initialize();
    // Process Wake Up Event
    if (IOC_FLAG)
    {   // PushButton or Module IOC woke us
        IOC_FLAG = 0;
        status = 1;
    }
// TODO:
//    else if (Comparator)    // USB EVENT
//    {
//        status = 2;
//    }
    else
    {   // Time woke us. Reload; so wake from sleep is short
        secTicker = 10;
        status = 0;
    }
    USB_DET_ANSEL = 0;
    oled_displayOff(false);
    oled_init();         // Dispaly

    modemResync();
    return status;
}