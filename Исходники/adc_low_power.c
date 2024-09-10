/*!
 * @brief main function
 */
int main(void)
{
    int32_t currentTemperature = 0;
    uint32_t updateBoundariesCounter = 0;
    int32_t tempArray[UPDATE_BOUNDARIES_TIME * 2];
    lowPowerAdcBoundaries_t boundaries;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Init using Led in Demo app */
    LED1_INIT();
    LED2_INIT();

    /* Set to allow entering vlps mode */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeVlp);

    /* Calibrate param Temperature sensor */
    ADC16_CalibrateParams(DEMO_ADC16_BASEADDR);

    /* Initialize Demo ADC */
    if (!ADC16_InitHardwareTrigger(DEMO_ADC16_BASEADDR))
    {
        PRINTF("Failed to do the ADC init\r\n");
        return -1;
    }

    PRINTF("\n\r ADC LOW POWER DEMO\n");
    PRINTF("\r The Low Power ADC project is designed to work with the Tower System or in a stand alone setting\n\n");
    PRINTF("\r 1. Set your target board in a place where the temperature is constant.\n");
    PRINTF("\r 2. Wait until two Led light turns on.\n");
    PRINTF("\r 3. Increment or decrement the temperature to see the changes.\n");
    PRINTF("\r Wait two led on...\n\r");

    /* setup the HW trigger source */
    LPTMR_InitTriggerSourceOfAdc(DEMO_LPTMR_BASE);
    ADC16_EnableDMA(DEMO_ADC16_BASEADDR, false);
    NVIC_EnableIRQ(DEMO_ADC16_IRQ_ID);
    /* Warm up microcontroller and allow to set first boundaries */
    while (updateBoundariesCounter < (UPDATE_BOUNDARIES_TIME * 2))
    {
        while (!conversionCompleted)
        {
        }
        currentTemperature = GetCurrentTempValue();
        tempArray[updateBoundariesCounter] = currentTemperature;
        updateBoundariesCounter++;
        conversionCompleted = false;
    }

    /* Temp Sensor Calibration */
    boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
    updateBoundariesCounter = 0;

    /* Two LED is turned on indicating calibration is done */
    LED1_ON();
    LED2_ON();

    /* Wait for user input before beginning demo */
    PRINTF("\r Enter any character to begin...\n");
    GETCHAR();
    PRINTF("\r ---> OK! Main process is running...!\n");

    while (1)
    {
        /* Prevents the use of wrong values */
        while (!conversionCompleted)
        {
        }

        /* Get current Temperature Value */
        currentTemperature = GetCurrentTempValue();
        /* Store temperature values that are going to be use to calculate average temperature */
        tempArray[updateBoundariesCounter] = currentTemperature;

        if (currentTemperature > boundaries.upperBoundary)
        {
            LED2_OFF();
            LED1_ON();
        }
        else if (currentTemperature < boundaries.lowerBoundary)
        {
            LED2_ON();
            LED1_OFF();
        }
        else
        {
            LED2_ON();
            LED1_ON();
        }

        /* Call update function */
        if (updateBoundariesCounter >= (UPDATE_BOUNDARIES_TIME))
        {
            boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
            updateBoundariesCounter = 0;
        }
        else
        {
            updateBoundariesCounter++;
        }

        /* Clear conversionCompleted flag */
        conversionCompleted = false;

        /* Enter to Very Low Power Stop Mode */
        SMC_SetPowerModeVlps(SMC);
    }
}