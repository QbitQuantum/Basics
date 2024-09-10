void sclock(void)
{
	writePort(g_ucPinTCK, 0x01);
	writePort(g_ucPinTCK, 0x00);
}