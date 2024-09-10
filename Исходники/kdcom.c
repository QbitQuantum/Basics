NTSTATUS
NTAPI
KdpPortInitialize(IN ULONG ComPortNumber,
                  IN ULONG ComPortBaudRate)
{
    NTSTATUS Status;

    KDDBGPRINT("KdpPortInitialize, Port = COM%ld\n", ComPortNumber);

    Status = CpInitialize(&KdDebugComPort,
                          UlongToPtr(BaseArray[ComPortNumber]),
                          ComPortBaudRate);
    if (!NT_SUCCESS(Status))
    {
        return STATUS_INVALID_PARAMETER;
    }
    else
    {
        KdComPortInUse = KdDebugComPort.Address;
        return STATUS_SUCCESS;
    }
}