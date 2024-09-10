NTSTATUS
UartRegConvertAndValidateBaud (
    _In_ ULONG SpeedBPS,
    _Out_ USHORT * DivisorLatch
    )
{
    NTSTATUS status = STATUS_SUCCESS;
    USHORT divisor = 0;
    ULONG realBaud = 0;

    status = UartRegBaudToDivisorLatch(SpeedBPS, &divisor);

    if (NT_SUCCESS(status))
    {
        //
        // Determine if difference between desired and real
        // baud rate is within acceptable tolerance.
        //

        status = UartRegDivisorLatchToBaud(
            divisor,
            &realBaud);

        if (NT_SUCCESS(status))
        {
            ULONG baudDifference;
            
            if (SpeedBPS > realBaud)
            {
                baudDifference = SpeedBPS - realBaud;
            }
            else
            {
                baudDifference = realBaud - SpeedBPS;
            }

            KFLOATING_SAVE kFloatSave;
            status = KeSaveFloatingPointState(&kFloatSave);

            if (NT_SUCCESS(status))
            {
                if((DOUBLE)(baudDifference) / (DOUBLE)SpeedBPS >
                    UartBaudRateErrorTolerance)
                {
                    status = STATUS_INVALID_PARAMETER;
                    TraceMessage(
                        TRACE_LEVEL_ERROR,
                        TRACE_FLAG_CONTROL,
                        "Desired baudrate %lu exceeds error tolerance "
                        "(%.2f%%) - %!STATUS!",
                        SpeedBPS,
                        (UartBaudRateErrorTolerance*100),
                        status);
                }

                KeRestoreFloatingPointState(&kFloatSave);
            }
            else
            {
                TraceMessage(
                    TRACE_LEVEL_ERROR,
                    TRACE_FLAG_CONTROL,
                    "Failure saving floating point state - %!STATUS!",
                    status);
            }
        }
    }

    if (NT_SUCCESS(status))
    {
        *DivisorLatch = divisor;
    }
    
    return status;
}