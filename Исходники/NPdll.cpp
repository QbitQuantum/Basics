int NPSendMessage(PVOID InputBuffer)
{
	DWORD bytesReturned = 0;
	DWORD hResult = 0;
	PCOMMAND_MESSAGE commandMessage = (PCOMMAND_MESSAGE) InputBuffer;	
	
    hResult = FilterSendMessage(
		g_hPort,
        commandMessage,
        sizeof(COMMAND_MESSAGE),
        NULL,
        NULL,
        &bytesReturned );

	if (hResult != S_OK) {
		return hResult;
	}
	return 0;
}