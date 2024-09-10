void EventHandle::PollInput() // Grabs input from 'GetAsyncKeyState()'
{
	int i = 0;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_vKeys.push_back(VK_LEFT); ++i; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_vKeys.push_back(VK_RIGHT); ++i; }
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_vKeys.push_back(VK_UP); ++i; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_vKeys.push_back(VK_DOWN);  ++i; }

	if (GetAsyncKeyState('W') & 0x8000)	{ m_vKeys.push_back(0x57);  ++i; } // W Key
	if (GetAsyncKeyState('A') & 0x8000) { m_vKeys.push_back(0x41);  ++i; } // A Key
	if (GetAsyncKeyState('S') & 0x8000) { m_vKeys.push_back(0x53);  ++i; } // S Key
	if (GetAsyncKeyState('D') & 0x8000) { m_vKeys.push_back(0x44);  ++i; } // D Key

	if (GetAsyncKeyState('P') & 0x8000) { m_vKeys.push_back(0x50);  ++i; } // P Key
	if (GetAsyncKeyState('G') & 0x8000) { m_vKeys.push_back(0x47);  ++i; } // G Key
	if (GetAsyncKeyState('X') & 0x8000) { m_vKeys.push_back(0x58);  ++i; } // X Key

	if (GetAsyncKeyState('F') & 0x8000) { m_vKeys.push_back(0x46);  ++i; } // F Key

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) { m_vKeys.push_back(VK_RETURN);  ++i; }

	if (GetAsyncKeyState(VK_PRIOR) & 0x8000) { m_vKeys.push_back(VK_PRIOR); ++i; }
	if (GetAsyncKeyState(VK_NEXT) & 0x8000) { m_vKeys.push_back(VK_NEXT); ++i; }

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { m_vKeys.push_back(VK_ESCAPE); ++i; }

	OrderInput();
	ParseInput();
	if (!i)
	{
		m_vPrevKeys.clear();
		m_vUntilPressed.clear();
		m_vUntilRepeat.clear();
	}
}