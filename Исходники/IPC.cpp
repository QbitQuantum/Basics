	extern "C" __declspec(dllexport) DWORD WINAPI OnAttach(LPDWORD args)
	{
		try
		{
			const DWORD access = PROCESS_DUP_HANDLE | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | SYNCHRONIZE;
			HANDLE hProcess = OpenProcess(access, FALSE, args[0]);
			if (!hProcess)
				throw L"OpenProcess";

			//init shared memory
			HANDLE mmf = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SharedMemory), nullptr);
			if (!mmf)
				throw L"CreateFileMapping";
			shared = (SharedMemory*)MapViewOfFile(mmf, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			if (!shared)
				throw L"MapViewOfFile";
			HANDLE mmfRemote = Duplicate(hProcess, mmf);
			CloseHandle(mmf);

			if (!RegisterWaitForSingleObject(&mmf, hProcess, OnExit, nullptr, INFINITE, WT_EXECUTEONLYONCE))
				throw L"RegisterWaitForSingleObject";
			CloseHandle(mmf);

			//init events
			sentOut = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			handledOut = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			sentIn = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			handledIn = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (!sentOut || !handledOut || !sentIn || !handledIn)
				throw L"CreateEvent";
			shared->msgOut[0] = (UINT)Duplicate(hProcess, sentOut);
			shared->msgOut[1] = (UINT)Duplicate(hProcess, handledOut);
			shared->msgOut[2] = (UINT)Duplicate(hProcess, sentIn);
			shared->msgOut[3] = (UINT)Duplicate(hProcess, handledIn);
			CloseHandle(hProcess);

			//init UOHooks
			Client client;
			Hooks::Imports(client);
			Hooks::Packets(client);
			Hooks::Other(client);
			if (args[1])
				Patches::Encryption(client);
			Patches::Multi(client);
			Patches::Intro(client);
			memcpy(shared->dataOut, Hooks::GetPacketTable(), 0x100 * sizeof(UINT));

			std::thread(MessagePump).detach();//start ipc server
			return (DWORD)mmfRemote;
		}
		catch (LPCWSTR str) { MessageBox(nullptr, str, L"OnAttach", MB_ICONERROR | MB_OK); }
		return 0;
	}