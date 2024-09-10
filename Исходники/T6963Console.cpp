String LCDConsole::readLine(GetKey getKey)
{
	char buffer[80];
	int8_t index = 0;
	bool wasCaretVisible = _caretVisible;
	showCaret();
	while (true)
	{
		char c = getKey();
		switch (c)
		{
		case 13:
			{
				buffer[index] = 0;
				String res = String(buffer);
				if (!wasCaretVisible)
					hideCaret();
				return res;
			}
		case 8: // backspace
			{
				if (index > 0)
				{
					index--;
					decrementCol();
					updateRowCol();
					_LCD->writeChar(' ');
					updateRowCol();
				}
				break;
			}
		default:
			if (index < sizeof(buffer) && c >= ' ' && c <= '~')
			{
			  buffer[index++] = c;
			  write(c);
			}
		}
	}
}