int main(int argc, char* argv[])
{
	std::cout << "DbgMsgSrc, pid: " << GetCurrentProcessId() << std::endl;
	//OutputDebugStringA("ping");
	//return 0;

	// get un-spoofable executable file name 
	//char buf[260];
	//GetMappedFileName(GetCurrentProcess(), _tmain, buf, sizeof(buf));
	//printf("%S\n", buf);

	//HANDLE handle1 = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
	//HANDLE handle2 = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
	//HANDLE handle3 = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
	//printf(" %p, %p, %p\n", handle1, handle2, handle3);

	int lastArgc = argc - 1;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg == "-1")
		{
			Output("titan_crash_debugview_43mb.log");
			return 0;
		}
		else if (arg == "-2")
		{
			if (i == lastArgc)
			{
				PrintUsage();
				return -1;
			}
			Output(argv[i + 1]);
			return 0;
		}
		else if (arg == "-3")
		{
			EndlessTest();
			return 0;
		}
		else if (arg == "-s")		// run separate process test
		{
			SeparateProcessTest();
			return 0;
		}
		else if (arg == "-w")
		{
			std::cout << "Send OutputDebugStringA 'WithoutNewLine ' (15 bytes)\n";
			OutputDebugStringA("WithoutNewLine ");
			return 0;
		}
		else if (arg == "-n")
		{
			std::cout << "Send OutputDebugStringA 'WithNewLine\\n' (12 bytes)\n";
			OutputDebugStringA("WithNewLine\n");
			return 0;
		}
		else if (arg == "-e")
		{
			std::cout << "Send empty OutputDebugStringA message (0 bytes)\n";
			OutputDebugStringA("");			//empty message
			return 0;
		}
		else if (arg == "-4")
		{
			std::cout << "Send 2x OutputDebugStringA 'WithNewLine\\n (24 bytes)'\n";
			OutputDebugStringA("WithNewLine\n");
			OutputDebugStringA("WithNewLine\n");
			return 0;
		}
		else if (arg == "-5")
		{
			std::cout << "Send OutputDebugStringA '1\\n2\\n3\\n' (6 bytes)\n";
			OutputDebugStringA("1\n2\n3\n");
			return 0;
		}
		else if (arg == "-6")
		{
			std::cout << "Send OutputDebugStringA '1 ' '2 ' '3\\n' in separate messages (6 bytes)\n";
			OutputDebugStringA("1 ");
			OutputDebugStringA("2 ");
			OutputDebugStringA("3\n");
			return 0;
		}
		else if (arg == "-7")
		{
			DbgMsgTest();
			return 0;
		}
		else if (arg == "-8")
		{
			if (i == lastArgc)
			{
				PrintUsage();
				return -1;
			}
			int n = atoi(argv[i + 1]);
			DbgMsgSrc(n);
			return 0;
		}
		else if (arg == "-9")
		{
			DbgMsgClearTest();
			return 0;
		}
		else if (arg == "-A")
		{
			CoutCerrTest();
			return 0;
		}
		else if (arg == "-B")
		{
			CoutCerrTest2();
			return 0;
		}
		else if (arg == "-C")
		{
			SocketTest();
			return 0;
		}
		else
		{
			Output(arg);
			return 0;
		}
	}
	PrintUsage();
	return 0;
}