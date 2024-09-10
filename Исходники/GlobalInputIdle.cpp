int main()
{
	LASTINPUTINFO lpi;
	lpi.cbSize = sizeof(lpi);

	while (1)
	{
		int ret = GetLastInputInfo(&lpi);
		printf("%d, idle for %d s.\n", ret, (::GetTickCount()-lpi.dwTime)/1000);
		Sleep(500);
	}
	return 0;
}