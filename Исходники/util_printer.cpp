bool PrinterUtil::initDeviceSettings( QString printerName, QByteArray& devModeA )
{
	bool done;
	uint size;
	LONG result = IDOK+1;
	Qt::HANDLE handle = NULL;
	// Get the printer handle
	done = OpenPrinterW( (LPWSTR) printerName.utf16(), &handle, NULL );
	if(!done)
		return false;
	// Get size of DEVMODE structure (public + private data)
	size = DocumentPropertiesW( ScCore->primaryMainWindow()->winId(), handle, (LPWSTR) printerName.utf16(), NULL, NULL, 0);
	// Compare size with DevMode structure size
	if( devModeA.size() == size )
	{
		// Merge printer settings
		result = DocumentPropertiesW( ScCore->primaryMainWindow()->winId(), handle, (LPWSTR) printerName.utf16(), (DEVMODEW*) devModeA.data(), (DEVMODEW*) devModeA.data(), DM_IN_BUFFER | DM_OUT_BUFFER);
	}
	else
	{
		// Retrieve default settings
		devModeA.resize( size );
		result = DocumentPropertiesW( ScCore->primaryMainWindow()->winId(), handle, (LPWSTR) printerName.utf16(), (DEVMODEW*) devModeA.data(), NULL, DM_OUT_BUFFER);
	}
	done = ( result == IDOK);
	// Free the printer handle
	ClosePrinter( handle );
	return done;
}