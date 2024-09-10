OSStatus
CPrinterSetupWizardSheet::InstallPrinterIPP(Printer * printer, Service * service)
{
	DEBUG_UNUSED( service );

	HANDLE			hPrinter = NULL;
	PRINTER_INFO_2	pInfo;
	OSStatus		err;
	
	//
	// add the printer
	//
	ZeroMemory(&pInfo, sizeof(PRINTER_INFO_2));
	
	pInfo.pPrinterName		= printer->actualName.GetBuffer();
	pInfo.pPortName			= printer->portName.GetBuffer();
	pInfo.pDriverName		= printer->model.GetBuffer();
	pInfo.pPrintProcessor	= L"winprint";
	pInfo.pLocation			= service->location.GetBuffer();
	pInfo.Attributes		= PRINTER_ATTRIBUTE_NETWORK | PRINTER_ATTRIBUTE_LOCAL;
	
	hPrinter = AddPrinter(NULL, 2, (LPBYTE)&pInfo);
	err = translate_errno( hPrinter, errno_compat(), kUnknownErr );
	require_noerr( err, exit );

exit:

	if ( hPrinter != NULL )
	{
		ClosePrinter(hPrinter);
	}

	return err;
}