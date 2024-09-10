int main()
{
	for (;;)
	{
		while (!g_USBSerial.readable())
			;
		char ch = g_USBSerial.getc();
		while (!g_USBSerial.writeable())
			;
		g_USBSerial.putc(ch + 1);
	}
}