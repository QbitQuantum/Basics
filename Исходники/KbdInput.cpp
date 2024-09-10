static void InputChar(unsigned char uChar, unsigned int nWaitMilliseconds)
{
	//char sLog[100] = "";
	//sprintf(sLog, "KeyInput: [%c]\n", (char )uChar);
	//OutputDebugStringA(sLog);

	// ref: https://msdn.microsoft.com/en-us/library/windows/desktop/ms646329(v=vs.85).aspx
	USHORT usVkey = VkKeyScanA(uChar);
	unsigned char shift = MapVirtualKey(VK_LSHIFT, 0); 
	unsigned char captial = MapVirtualKey(VK_CAPITAL, 0); 
	unsigned char scanCode = MapVirtualKey((unsigned char)(0x00ff & usVkey), 0);

	if (usVkey & 0x0100) { // `shift' key pressed
		MykeyDown(shift);
		Sleep(nWaitMilliseconds);

		MykeyDown(scanCode);
		Sleep(nWaitMilliseconds);

		MykeyUp(scanCode);
		Sleep(nWaitMilliseconds);

		MykeyUp(shift);
		Sleep(nWaitMilliseconds);
	}
	else {
		MykeyDown(scanCode);
		Sleep(nWaitMilliseconds);

		MykeyUp(scanCode);
		Sleep(nWaitMilliseconds);
	}
}