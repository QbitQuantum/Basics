void wiRawInput::RetrieveBufferedData()
{
	// Some temp global buffer, 1KB is overkill.
	static uint64_t rawBuffer[1024 / 8];
	
	// Then in some function,
	UINT bytes = sizeof(rawBuffer);
	// Loop through reading raw input until no events are left,
	while (1) {
		// Fill up buffer,
		int32_t count = GetRawInputBuffer((PRAWINPUT)rawBuffer, &bytes, sizeof(RAWINPUTHEADER));
		if (count <= 0) return;
		
		// Process all the events, 
		const RAWINPUT* raw = (const RAWINPUT*) rawBuffer;
		while (1) {
			// Process raw event.
			this->raw = *raw;
			// Goto next raw event.
			count--;
			if (count <= 0) break;
			raw = NEXTRAWINPUTBLOCK(raw);
		}
	}

	////while (true){
	//	UINT cbSize;
	//	//Sleep(1000);

	//	GetRawInputBuffer(NULL, &cbSize, sizeof(RAWINPUTHEADER));
	//	cbSize *= 16;            // this is a wild guess
	//	PRAWINPUT pRawInput = (PRAWINPUT)malloc(cbSize);
	//	if (pRawInput == NULL)
	//	{
	//		return;
	//	}
	//	for (;;)
	//	{
	//		UINT cbSizeT = cbSize;
	//		UINT nInput = GetRawInputBuffer(pRawInput, &cbSizeT, sizeof(RAWINPUTHEADER));
	//		if (nInput == 0)
	//		{
	//			break;
	//		}
	//		assert(nInput > 0);
	//		PRAWINPUT* paRawInput = (PRAWINPUT*)malloc(sizeof(PRAWINPUT) * nInput);
	//		if (paRawInput == NULL)
	//		{
	//			break;
	//		}
	//		PRAWINPUT pri = pRawInput;
	//		for (UINT i = 0; i < nInput; ++i)
	//		{
	//			paRawInput[i] = pri;
	//			pri = NEXTRAWINPUTBLOCK(pri);
	//			if (pri->header.dwType == RIM_TYPEHID)
	//			{
	//				int asd=32;
	//				asd = asd;
	//			}
	//		}
	//		// to clean the buffer
	//		DefRawInputProc(paRawInput, nInput, sizeof(RAWINPUTHEADER));

	//		free(paRawInput);
	//	}
	//	free(pRawInput);
	////}
}