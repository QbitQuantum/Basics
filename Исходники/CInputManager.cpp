char CInputManager::HandleKeyboard(float dtime)
{
	DWORD oldTime = 0;
	DWORD tickDelta;
	// update counts and time
    oldTime = m_fTime;

	DWORD newCount = GetTickCount();

	tickDelta = newCount - m_fOldCount;

	// if none of the keys are pressed
	if (!m_pInputModule->KBIsAnyKeyPressed())
	{
		// clear the key states and return
		ClearAllKeyStates();
		m_fOldCount = (newCount-1);
		return 0;
	}

	int i;
	char cLastASCII = 0;

	// figure out if shift is pressed
	bool bShift = (m_pInputModule->KBIsKeyPressed(EEK_RSHIFT)!=0)||
				  (m_pInputModule->KBIsKeyPressed(EEK_LSHIFT)!=0);

	// load key table
	const SEEKey *pTable = m_pInputModule->GetKeyTable();

	// go through all the keys
	for (i = 0; i < MAX_NUM_KEYS;i++)
	{
		// check if key is pressed
		bool state = (m_pInputModule->KBIsKeyPressed(i)!=0);

		// check modifiers and escape
		if (i==EEK_RSHIFT || i==EEK_LSHIFT || i==EEK_LCTRL || 
			i==EEK_RCTRL  || i==EEK_LALT || i==EEK_ALTGR || 
			i==EEK_ESC) 
		{
			m_bPressed[i]=state;
			continue;
		}

		// if a key is pressed
		if (state)
		{
			// make sure the repeat delay time as passed
			// if it has see the key pressed to be true
			m_bPressed[i] = (m_fPressedTime[i] == -KEYREPEAT_DELAYTIME);
			// add time change to time array
			m_fPressedTime[i] += tickDelta;

			if (m_fPressedTime[i] >= KEYREPEAT_FREQUENCY)
			{
				m_fPressedTime[i] = fmodf(m_fPressedTime[i],
										   KEYREPEAT_FREQUENCY);
				m_bPressed[i] = true;
				// also display in output
				//OutputDebugString(_T("PASSED TEST!\n"));
			}
		} 
		else
		{
			// otherwise make sure the key isn't pressed
			// in the array
			m_fPressedTime[i] = -KEYREPEAT_DELAYTIME;
			m_bPressed[i] = false;
		}
    
		// map virtual key to ASCII
		if (!cLastASCII && m_bPressed[i])
		{
			const SEEKey *pKey = &pTable[i];
			cLastASCII = (bShift) ? 
						  pKey->m_chUpper:pKey->m_chLower;
		}
	}	
	
	// send message that a key has been pressed
	static DWORD msgHash_KeyPress = CHashString(_T("KeyPress")).GetUniqueID();
	m_ToolBox->SendMessage(msgHash_KeyPress, (DWORD)(sizeof(char)), &cLastASCII);

	m_fOldCount = (newCount-1);
	return cLastASCII;
}