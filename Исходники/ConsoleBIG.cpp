int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { 80, 40 };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);
	SetConsoleTitleW(L"MyGame");

	CGamePrimitive* screen[80 * 40];
	memset(screen, 0, sizeof(screen));

	COORD v_c = {7,7};
	screen[25] = new DrawSymbolRealization(v_c);
	v_c = { 9, 9 };
	screen[35] = new DrawSymbolRealization(v_c);
	v_c = { 79, 39 };
	screen[96] = new DrawSymbolRealization(v_c);
	for (int i = 0;
		i < sizeof(screen) / sizeof(*screen);
		++i)
	{
		if (nullptr == screen[i])
			continue;
		screen[i]->Draw(out_handle);
	}

	system("pause");
	return 0;
}