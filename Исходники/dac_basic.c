/*!
 * @brief Main function
 */
int main(void)
{
    dac_config_t dacConfigStruct;
    uint32_t dacValue;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nDAC basic Example.\r\n");

    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_INSTANCE, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_INSTANCE, true);
    DAC_SetBufferReadPointer(DEMO_DAC_INSTANCE, 0U); /* Make sure the read pointer to the start. */
                                                     /*
                                                     * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
                                                     * and itemss can be written manually by user.
                                                     */

    while (1)
    {
        PRINTF("\r\nPlease input a value (0 - 4095) to output with DAC: ");
        SCANF("%d", &dacValue);
        PRINTF("\r\nInput value is %d\r\n", dacValue);
        if (dacValue > 0xFFFU)
        {
            PRINTF("Your value is output of range.\r\n");
            continue;
        }
        DAC_SetBufferValue(DEMO_DAC_INSTANCE, 0U, dacValue);
        PRINTF("DAC out: %d\r\n", dacValue);
        /*
        * The value in the first item would be converted. User can measure the output voltage from DAC_OUTx pin.
        */
    }
}