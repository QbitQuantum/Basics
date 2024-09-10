inline const VKEY ConsoleUI::GetVkResponse(PCVKEY rgvkCriteria) const
{
	CONSOLE_CURSOR_INFO	cursorInfo;			// Console cursor information
	DWORD				dwInputMode;		// Console input mode flags
	bool				bValid = false;		// Loop termination flag
	INPUT_RECORD		recInput;			// INPUT_RECORD from console input
	DWORD				cEvents;			// Number of events read from console
	VKEY				vkInput;			// Virtual key code read from the console
	PCVKEY				pvk;				// Pointer to a virtual key code

	if(!rgvkCriteria) return NULL;			// No criteria codes to work with
	
	GetConsoleCursorInfo(m_hout, &cursorInfo);		// Get console cursor info
	
	cursorInfo.bVisible = FALSE;					// Turn off the cursor
	SetConsoleCursorInfo(m_hout, &cursorInfo);		// Set new cursor info
	
	// Remove the LINE_INPUT and ECHO_INPUT flags from the console input handle

	GetConsoleMode(m_hin, &dwInputMode);
	SetConsoleMode(m_hin, dwInputMode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);

	FlushConsoleInputBuffer(m_hin);					// Flush the console input buffer

	// Loop until the user presses one of the valid virtual keys
	
	while(!bValid) {

		vkInput = NULL;

		// Read in the next event from the console's input buffer, and discard
		// it if it's not a KEY_EVENT indicating a key down signal

		if(!ReadConsoleInput(m_hin, &recInput, 1, &cEvents)) break;
		
		if(recInput.EventType != KEY_EVENT) continue;		// Not a KEY_EVENT
		if(!recInput.Event.KeyEvent.bKeyDown) continue;		// Not a keydown event

		vkInput = recInput.Event.KeyEvent.wVirtualKeyCode;

		// Check to see if this virtual key code matches any of the specified
		// valid codes, and break the while() loop if it does

		for(pvk = rgvkCriteria; *pvk; pvk++) 
			if(vkInput == *pvk) { bValid = true; break; }
	};

	SetConsoleMode(m_hin, dwInputMode);				// Restore input mode flags
	
	cursorInfo.bVisible = TRUE;						// Turn the cursor back on
	SetConsoleCursorInfo(m_hout, &cursorInfo);		// Restore the cursor state
		
	return vkInput;
}