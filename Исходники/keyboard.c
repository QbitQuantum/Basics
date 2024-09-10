/**
 * Scans an integer value from the keyboard to the pointer *p.
 * @param *p The pointer of the result value.
 */
void USscanInt(int *p)
{
	acTask->writing = 1;
	scanUse = true;
	bool invert = false;
	char c;
	int i = 0;
	while(1)
	{
		c = getChar();
		if (c == '\n') break;
		else if (c == '-' && i == 0) invert = true;
		else
		{
			c -= 48;
			*p *= 10;
			*p += c;
			i++;
		}
	}
	if (invert) *p *= -1;
	scanUse = false;
	acTask->writing = 0;
}