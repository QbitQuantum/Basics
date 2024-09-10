void KeyStates::ProcessDoubleClick(byte key)
{
	assert(key >= VK_LBUTTON && key <= VK_XBUTTON2);
	Process(key, true);
	doubleclk[key] = true;
}