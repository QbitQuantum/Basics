STDMETHODIMP CMicroFlash::Print(int iCopies)
{
	HRESULT r;
	char endLine [] = "\r\n";
	DWORD dwBytesWritten;
	char *pcPrintBuf;
	int iLineCount, n;

	// Assume failure
	r = S_FALSE;

	pcPrintBuf = NULL;
	iLineCount = 0;

	if(!OpenPort()) goto Exit;

	// Add formfeed to data
	m_strData.Append (TEXT("\x0C"));

	// Convert to char data
	n = m_strData.Length ();
	pcPrintBuf = new char [n + 1];
	wcstombs (pcPrintBuf, m_strData, n);
	pcPrintBuf [n] = 0;

	// Wakeup the printer
	for(iLineCount = 0; iLineCount < 10; iLineCount++)
		WriteFile(m_hComPort, endLine, strlen(endLine), &dwBytesWritten, NULL);

	Sleep(500);

	// Print the buffer
	for(iLineCount = 0; iLineCount < iCopies; iLineCount++)
		if(!WriteFile(m_hComPort, pcPrintBuf, strlen(pcPrintBuf), 
			&dwBytesWritten, NULL)) goto Exit;

	m_strData.Empty ();

	r = S_OK;

Exit:
	ClosePort ();
	delete [] pcPrintBuf;

	return r;
}