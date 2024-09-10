//-----------------------------------------------------------------------------
// GetString
//-----------------------------------------------------------------------------
//
// Return Value : Pointer to string containing buffer read from UART.
// Parameters   : <buf> to store string; maximum <n>umber of characters to
//                read; <n> must be 2 or greater.
//
// This function returns a string of maximum length <n>.
//-----------------------------------------------------------------------------
int GetString()
{
	char c;
	int len = 0;
	char *buffer = Command;
	int max_length = sizeof(Command) - 1;

	SetLedPeriod(900, 100);
	printf("READY\r\n> ");

	while(1)
	{
		c = GETCHAR();
		if (c != '\0')
		{
			if (c == '\b' || c == 0x7F)
			{
				if (len != 0)
				{
					PUTCHAR(c);
					--len;
					--buffer;
				}
			}
			else if (c == '\r' || c == '\n')
			{
				SetLedPeriod(0, 0);
				PUTCHAR('\n');
				if (max_length == 0)
				{
					printf("Result: FF COMMAND_TOO_LONG\n");
					buffer = Command;
				}
				*buffer = '\0';
				return len;
			}
			else if (len != max_length)
			{
				PUTCHAR(c);
				*buffer++ = c;
				len++;
			}
			else
			{
				max_length = 0;
				len = 0;
			}
		}
	}
}