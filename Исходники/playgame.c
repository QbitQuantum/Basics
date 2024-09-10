static int wince_mess_vprintf(char *fmt, va_list arg)
{
	int length;
	int old_length;
	LPTSTR new_messages;
	LPCTSTR tbuffer;
	char buffer[256];

	/* get into a buffer */
	length = vsnprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), fmt, arg);
	tbuffer = A2T(buffer);

	/* output to debugger */
	OutputDebugString(tbuffer);

	/* append the buffer to the rest of the messages */
	old_length = messages ? tcslen(messages) : 0;
	new_messages = realloc(messages, (old_length + tcslen(tbuffer) + 1) * sizeof(TCHAR));
	if (new_messages)
	{
		messages = new_messages;
		tcscpy(messages + old_length, tbuffer);
	}
	return length;
}