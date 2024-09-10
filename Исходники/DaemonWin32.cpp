		bool DaemonWin32::start()
		{
			setlocale(LC_CTYPE, "");
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			setlocale(LC_ALL, "Russian");

			return Daemon_Singleton::start();
		}