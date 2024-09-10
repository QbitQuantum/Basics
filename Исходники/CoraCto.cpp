	void print()
	{
		std::ostringstream out;
		for (int y = 0; y < HEIGHT; y++)
		{
			out << chars[y] << std::endl;
			chars[y][0] = '\0';
		}
		auto str = out.str();

		//１、cmd.exeのcls命令を使う方法
		//system("cls");

		//２、Win32APIでカーソル位置を操作する方法
		//COORD coord = { 0, 0 };
		//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		
		//std::cout << str;

		//３、Win32APIでスクリーンバッファを切り替える方法
		DWORD cell;
		WriteConsoleA(hSrc, str.c_str(), str.length(), &cell, NULL);
		SetConsoleActiveScreenBuffer(hSrc);
		hSrc = (hSrc == hSrc0) ? hSrc1 : hSrc0;
	}