CConsoleInput::CConsoleInput()
	: caps((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // Uses Windows API
{
}