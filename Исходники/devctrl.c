NTSTATUS NTAPI
SerialSetBaudRate(
	IN PSERIAL_DEVICE_EXTENSION DeviceExtension,
	IN ULONG NewBaudRate)
{
	ULONG BaudRate;
	USHORT divisor;
	PUCHAR ComPortBase = ULongToPtr(DeviceExtension->BaseAddress);
	NTSTATUS Status = STATUS_SUCCESS;

	if (NewBaudRate == 0)
		return STATUS_INVALID_PARAMETER;

	divisor = (USHORT)(BAUD_CLOCK / (CLOCKS_PER_BIT * NewBaudRate));
	BaudRate = BAUD_CLOCK / (CLOCKS_PER_BIT * divisor);

	Status = IoAcquireRemoveLock(&DeviceExtension->RemoveLock, ULongToPtr(DeviceExtension->ComPort));
	if (NT_SUCCESS(Status))
	{
		UCHAR Lcr;
		TRACE_(SERIAL, "SerialSetBaudRate(COM%lu, %lu Bauds)\n", DeviceExtension->ComPort, BaudRate);
		/* Set Bit 7 of LCR to expose baud registers */
		Lcr = READ_PORT_UCHAR(SER_LCR(ComPortBase));
		WRITE_PORT_UCHAR(SER_LCR(ComPortBase), Lcr | SR_LCR_DLAB);
		/* Write the baud rate */
		WRITE_PORT_UCHAR(SER_DLL(ComPortBase), divisor & 0xff);
		WRITE_PORT_UCHAR(SER_DLM(ComPortBase), divisor >> 8);
		/* Switch back to normal registers */
		WRITE_PORT_UCHAR(SER_LCR(ComPortBase), Lcr);

		IoReleaseRemoveLock(&DeviceExtension->RemoveLock, ULongToPtr(DeviceExtension->ComPort));
	}

	if (NT_SUCCESS(Status))
		DeviceExtension->BaudRate = BaudRate;
	return Status;
}