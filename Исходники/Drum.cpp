	void Drum:: Show(int a)
	{
		{/*
		dcoord.X = a;
		dcoord.Y = 12;
		SetConsoleCursorPosition( dhConsole, dcoord );*/
		ConsoleWorker::SetConsolePosition(a,12);

		cout<<pCur->symbol<<endl;
				/*
	dcoord.X = a;
		dcoord.Y = 13;
		SetConsoleCursorPosition( dhConsole, dcoord );*/
		ConsoleWorker::SetConsolePosition(a,13);

		cout<<getChar()<<' ';
		/*dcoord.X = a;
		dcoord.Y = 14;
		SetConsoleCursorPosition( dhConsole, dcoord );*/
		ConsoleWorker::SetConsolePosition(a,14);

		cout<<pHead->symbol<<endl;
		}
	}