void key_turn_on_numlock()
{
#ifdef _WIN32
	unsigned char keys[256];
	GetKeyboardState(keys);
	keys[VK_NUMLOCK] = 1;
	SetKeyboardState(keys);
#endif
}