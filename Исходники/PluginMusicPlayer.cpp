//向全局发送单一键击
void SendKey(WORD key)
{
	KEYBDINPUT kbi = { 0 };
	kbi.wVk = key;
	kbi.dwExtraInfo = (ULONG_PTR)GetMessageExtraInfo();

	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki = kbi;

	SendInput(1, &input, sizeof(INPUT));
}