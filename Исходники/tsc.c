VOID
NTAPI
HalpInitializeTsc(VOID)
{
    ULONG_PTR Flags;
    KIDTENTRY OldIdtEntry, *IdtPointer;
    PKPCR Pcr = KeGetPcr();
    UCHAR RegisterA, RegisterB;

    /* Check if the CPU supports RDTSC */
    if (!(KeGetCurrentPrcb()->FeatureBits & KF_RDTSC))
    {
        KeBugCheck(HAL_INITIALIZATION_FAILED);
    }

     /* Save flags and disable interrupts */
    Flags = __readeflags();
    _disable();

    /* Enable the periodic interrupt in the CMOS */
    RegisterB = HalpReadCmos(RTC_REGISTER_B);
    HalpWriteCmos(RTC_REGISTER_B, RegisterB | RTC_REG_B_PI);

    /* Modify register A to RTC_MODE to get SAMPLE_FREQENCY */
    RegisterA = HalpReadCmos(RTC_REGISTER_A);
    RegisterA = (RegisterA & 0xF0) | RTC_MODE;
    HalpWriteCmos(RTC_REGISTER_A, RegisterA);

    /* Save old IDT entry */
    IdtPointer = KiGetIdtEntry(Pcr, HalpRtcClockVector);
    OldIdtEntry = *IdtPointer;

    /* Set the calibration ISR */
    KeRegisterInterruptHandler(HalpRtcClockVector, TscCalibrationISR);

    /* Reset TSC value to 0 */
    __writemsr(MSR_RDTSC, 0);

    /* Enable the timer interupt */
    HalEnableSystemInterrupt(HalpRtcClockVector, CLOCK_LEVEL, Latched);

    /* Read register C, so that the next interrupt can happen */
    HalpReadCmos(RTC_REGISTER_C);;

    /* Wait for completion */
    _enable();
    while (TscCalibrationPhase < NUM_SAMPLES) _ReadWriteBarrier();
    _disable();

    /* Disable the periodic interrupt in the CMOS */
    HalpWriteCmos(RTC_REGISTER_B, RegisterB & ~RTC_REG_B_PI);

    /* Disable the timer interupt */
    HalDisableSystemInterrupt(HalpRtcClockVector, CLOCK_LEVEL);

    /* Restore old IDT entry */
    *IdtPointer = OldIdtEntry;

    /* Calculate an average, using simplified linear regression */
    HalpCpuClockFrequency.QuadPart = DoLinearRegression(NUM_SAMPLES - 1,
                                                        TscCalibrationArray);

    /* Restore flags */
    __writeeflags(Flags);

}