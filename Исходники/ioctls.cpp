//
// Internal Function: UartCtlSetLineControl
//
VOID
UartCtlSetLineControl(
    _In_ WDFDEVICE Device, 
    _In_ WDFREQUEST Request,
    _In_ size_t OutputBufferLength,
    _In_ size_t InputBufferLength
    )
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    PUART_DEVICE_EXTENSION pDevExt = UartGetDeviceExtension(Device);
    UCHAR lineControlRegister = 0;
    PSERIAL_LINE_CONTROL pLineControl = NULL;

    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);

    FuncEntry(TRACE_FLAG_CONTROL);

    status = WdfRequestRetrieveInputBuffer(Request, 
                    sizeof(SERIAL_LINE_CONTROL), 
                    (PVOID*)(& pLineControl), 
                    NULL);

    if (!NT_SUCCESS(status))
    {
        TraceMessage(
            TRACE_LEVEL_ERROR,
            TRACE_FLAG_CONTROL,
            "Failed to retrieve input buffer for WDFREQUEST %p - "
            "%!STATUS!",
            Request,
            status);
    }

    if (NT_SUCCESS(status))
    {
        status = UartRegStructToLCR(pLineControl, &lineControlRegister);

        if (!NT_SUCCESS(status))
        {
            TraceMessage(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_CONTROL,
                "Failed to calculate LCR from SERIAL_LINE_CONTROL %p  - "
                "%!STATUS!",
                pLineControl,
                status);
        }
    }

    if (NT_SUCCESS(status))
    {
        WdfInterruptAcquireLock(pDevExt->WdfInterrupt);

        // Set line control, save break setting
        lineControlRegister = lineControlRegister | 
            (READ_LINE_CONTROL(pDevExt, pDevExt->Controller) & SERIAL_LCR_BREAK);
        WRITE_LINE_CONTROL(pDevExt, pDevExt->Controller, lineControlRegister);

        WdfInterruptReleaseLock(pDevExt->WdfInterrupt);
    }

    TraceMessage(TRACE_LEVEL_INFORMATION,
                    TRACE_FLAG_CONTROL,
                    "WdfRequestComplete( %!HANDLE! => %!STATUS! )",
                    Request,
                    status);
    WdfRequestComplete(Request, status);

    FuncExit(TRACE_FLAG_CONTROL);
}