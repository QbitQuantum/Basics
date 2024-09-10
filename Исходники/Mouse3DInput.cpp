void Mouse3DInput::onRawInput(UINT nInputCode, HRAWINPUT hRawInput)
{
	const size_t cbSizeOfBuffer = 1024;
	BYTE pBuffer[cbSizeOfBuffer];

	PRAWINPUT pRawInput = reinterpret_cast<PRAWINPUT>(pBuffer);
	UINT cbSize = cbSizeOfBuffer;

	if (::GetRawInputData(hRawInput, RID_INPUT, pRawInput, &cbSize, sizeof(RAWINPUTHEADER)) == static_cast<UINT>(-1))
	{
		return;
	}

	bool b3dmouseInput = translateRawInputData(nInputCode, pRawInput);
	::DefRawInputProc(&pRawInput, 1, sizeof(RAWINPUTHEADER));

	// Check for any buffered messages
	cbSize = cbSizeOfBuffer;
	UINT nCount = getRawInputBuffer(pRawInput, &cbSize, sizeof(RAWINPUTHEADER));
	if (nCount == (UINT)-1)
	{
		qDebug ("GetRawInputBuffer returned error %d\n", GetLastError());
	}

	while (nCount>0 && nCount !=  static_cast<UINT>(-1))
	{
		PRAWINPUT pri = pRawInput;
		UINT nInput;
		for (nInput=0; nInput<nCount; ++nInput)
		{
			b3dmouseInput |= translateRawInputData(nInputCode, pri);
			// clean the buffer
			::DefRawInputProc(&pri, 1, sizeof(RAWINPUTHEADER));

			pri = NEXTRAWINPUTBLOCK(pri);
		}
		cbSize = cbSizeOfBuffer;
		nCount = getRawInputBuffer(pRawInput, &cbSize, sizeof(RAWINPUTHEADER));
	}

	// If we have mouse input data for the app then tell tha app about it
	if (b3dmouseInput)
		on3dmouseInput();
}