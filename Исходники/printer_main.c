/**
 * Function description
 *
 * @return 0 on success, otherwise a Win32 error code
 */
UINT printer_register(PDEVICE_SERVICE_ENTRY_POINTS pEntryPoints,
                      rdpPrinter* printer)
{
	char* port;
	UINT32 Flags;
	int DriverNameLen;
	WCHAR* DriverName = NULL;
	int PrintNameLen;
	WCHAR* PrintName = NULL;
	UINT32 CachedFieldsLen;
	BYTE* CachedPrinterConfigData;
	PRINTER_DEVICE* printer_dev;
	UINT error;
	port = malloc(10);

	if (!port)
	{
		WLog_ERR(TAG, "malloc failed!");
		return CHANNEL_RC_NO_MEMORY;
	}

	sprintf_s(port, 10, "PRN%d", printer->id);
	printer_dev = (PRINTER_DEVICE*) calloc(1, sizeof(PRINTER_DEVICE));

	if (!printer_dev)
	{
		WLog_ERR(TAG, "calloc failed!");
		free(port);
		return CHANNEL_RC_NO_MEMORY;
	}

	printer_dev->device.type = RDPDR_DTYP_PRINT;
	printer_dev->device.name = port;
	printer_dev->device.IRPRequest = printer_irp_request;
	printer_dev->device.Free = printer_free;
	printer_dev->rdpcontext = pEntryPoints->rdpcontext;
	printer_dev->printer = printer;
	CachedFieldsLen = 0;
	CachedPrinterConfigData = NULL;
	Flags = 0;

	if (printer->is_default)
		Flags |= RDPDR_PRINTER_ANNOUNCE_FLAG_DEFAULTPRINTER;

	DriverNameLen = ConvertToUnicode(CP_UTF8, 0, printer->driver, -1, &DriverName,
	                                 0) * 2;
	PrintNameLen = ConvertToUnicode(CP_UTF8, 0, printer->name, -1, &PrintName,
	                                0) * 2;
	printer_dev->device.data = Stream_New(NULL,
	                                      28 + DriverNameLen + PrintNameLen + CachedFieldsLen);

	if (!printer_dev->device.data)
	{
		WLog_ERR(TAG, "calloc failed!");
		error = CHANNEL_RC_NO_MEMORY;
		free(DriverName);
		free(PrintName);
		goto error_out;
	}

	Stream_Write_UINT32(printer_dev->device.data, Flags);
	Stream_Write_UINT32(printer_dev->device.data, 0); /* CodePage, reserved */
	Stream_Write_UINT32(printer_dev->device.data, 0); /* PnPNameLen */
	Stream_Write_UINT32(printer_dev->device.data, DriverNameLen + 2);
	Stream_Write_UINT32(printer_dev->device.data, PrintNameLen + 2);
	Stream_Write_UINT32(printer_dev->device.data, CachedFieldsLen);
	Stream_Write(printer_dev->device.data, DriverName, DriverNameLen);
	Stream_Write_UINT16(printer_dev->device.data, 0);
	Stream_Write(printer_dev->device.data, PrintName, PrintNameLen);
	Stream_Write_UINT16(printer_dev->device.data, 0);

	if (CachedFieldsLen > 0)
	{
		Stream_Write(printer_dev->device.data, CachedPrinterConfigData,
		             CachedFieldsLen);
	}

	free(DriverName);
	free(PrintName);
	printer_dev->pIrpList = (WINPR_PSLIST_HEADER) _aligned_malloc(sizeof(
	                            WINPR_SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT);

	if (!printer_dev->pIrpList)
	{
		WLog_ERR(TAG, "_aligned_malloc failed!");
		error = CHANNEL_RC_NO_MEMORY;
		goto error_out;
	}

	InitializeSListHead(printer_dev->pIrpList);

	if (!(printer_dev->event = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		WLog_ERR(TAG, "CreateEvent failed!");
		error = ERROR_INTERNAL_ERROR;
		goto error_out;
	}

	if (!(printer_dev->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		WLog_ERR(TAG, "CreateEvent failed!");
		error = ERROR_INTERNAL_ERROR;
		goto error_out;
	}

	if ((error = pEntryPoints->RegisterDevice(pEntryPoints->devman,
	             (DEVICE*) printer_dev)))
	{
		WLog_ERR(TAG, "RegisterDevice failed with error %"PRIu32"!", error);
		goto error_out;
	}

	if (!(printer_dev->thread = CreateThread(NULL, 0,
	                            (LPTHREAD_START_ROUTINE) printer_thread_func, (void*) printer_dev, 0, NULL)))
	{
		WLog_ERR(TAG, "CreateThread failed!");
		error = ERROR_INTERNAL_ERROR;
		goto error_out;
	}

	return CHANNEL_RC_OK;
error_out:
	CloseHandle(printer_dev->stopEvent);
	CloseHandle(printer_dev->event);
	_aligned_free(printer_dev->pIrpList);
	Stream_Free(printer_dev->device.data, TRUE);
	free(printer_dev);
	free(port);
	return error;
}