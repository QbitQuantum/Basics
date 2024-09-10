VOID CToolDumper::Start()
{
	//показать диалог
	CSelectProcessDialog Dialog;
	if(!Dialog.Show(gApplication.mhMainWindow,&mProcessID)) return;

	//открыть процесс
	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,mProcessID);
	if(!hProcess)
	{
		MessageBox(NULL,TEXT("Could not open handle of selected process.\nNo rights to perform the operation."),TEXT("Dumping process"),MB_ICONSTOP);
		return;
	}

	//запросить файл для сохранения дампа
	TCHAR szFile[MAX_PATH]={0};
	{
		OPENFILENAME ofn={sizeof(OPENFILENAME)};
		ofn.hwndOwner=gApplication.mhMainWindow;
		ofn.lpstrFile=szFile;
		ofn.nMaxFile=MAX_PATH;
		ofn.lpstrFilter=TEXT("Code0 Dump Files (*.dump)\0*.dump\0");
		ofn.lpstrTitle=TEXT("Select File to Save Dump File");
		ofn.Flags=OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST |OFN_HIDEREADONLY;
		if(!GetSaveFileName(&ofn))
		{
			//закрыть процесс и закончить
			CloseHandle(hProcess);
			return;
		}
	}

	//создать файл дампа
	HANDLE hFile=CreateFile(szFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		CloseHandle(hProcess);
		MessageBox(NULL,TEXT("Could not create file on specified location."),TEXT("Dumping process"),MB_ICONSTOP);
		return;
	}

	//получить список регионов и размеры памяти регионов
	std::list<FILE_DUMP_REGION> RegionsList;
	DWORD MemorySize=0;
	{
		//цикл по регионам
		PBYTE pRegion=0;
		do
		{
			//получить информацию о регионе
			MEMORY_BASIC_INFORMATION RegionInfo;
			if(!VirtualQueryEx(hProcess,pRegion,&RegionInfo,sizeof(RegionInfo))) break;

			//добавить регион в список
			FILE_DUMP_REGION Region;
			Region.Flags=0;
			Region.BaseAddress=(DWORD)pRegion;
			Region.Size=RegionInfo.RegionSize;
			Region.State=RegionInfo.State;
			Region.Protect=RegionInfo.Protect;
			Region.DataOffset=RegionInfo.State==MEM_COMMIT ? MemorySize : 0;
			RegionsList.push_back(Region);

			//увеличить размеры необходимой памяти, если память региона действительна
			if(RegionInfo.State==MEM_COMMIT)
				MemorySize+=RegionInfo.RegionSize;

			//перейти к следующему региону
			pRegion+=RegionInfo.RegionSize;
		}
		while(pRegion);
	}

	//получить список потоков
	std::list<FILE_DUMP_THREAD> ThreadsList;
	{
		//создать снимок процесса
		HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
		if(hSnapshot==INVALID_HANDLE_VALUE)
			MessageBox(NULL,TEXT("Thread list in dump is not available."),TEXT("Dumping process"),MB_ICONEXCLAMATION);
		else
		{
			//цикл по потокам
			THREADENTRY32 ThreadEntry;
			ThreadEntry.dwSize=sizeof(ThreadEntry);

			if(Thread32First(hSnapshot,&ThreadEntry))
				do
				{
					//если поток принадлежит нужному процессу (так как перечисляются все потоки)
					if(ThreadEntry.th32OwnerProcessID==mProcessID)
					{
						//добавить информацию о потоке в список
						FILE_DUMP_THREAD Thread;
						Thread.Flags=0;
						Thread.ThreadID=ThreadEntry.th32ThreadID;
						Thread.UsageCount=ThreadEntry.cntUsage;
						Thread.PriorityBase=ThreadEntry.tpBasePri;
						Thread.PriorityDelta=ThreadEntry.tpDeltaPri;
						ThreadsList.push_back(Thread);
					}
				}
				while(Thread32Next(hSnapshot,&ThreadEntry));
			//закрыть снимок процесса
			CloseHandle(hSnapshot);
		}
	}

	//получить список модулей
	std::list<FILE_DUMP_MODULE> ModulesList;
	{
		//создать снимок процесса
		HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,mProcessID);
		if(hSnapshot==INVALID_HANDLE_VALUE)
			MessageBox(NULL,TEXT("Modules list in dump is not available."),TEXT("Dumping process"),MB_ICONEXCLAMATION);
		else
		{
			//цикл по модулям
			MODULEENTRY32 ModuleEntry;
			ModuleEntry.dwSize=sizeof(ModuleEntry);

			if(Module32First(hSnapshot,&ModuleEntry))
				do
				{
					//добавить информацию о модуле в список
					FILE_DUMP_MODULE Module;
					ZeroMemory(&Module,sizeof(Module));
					Module.Flags=0;
					Module.BaseAddress=(DWORD)ModuleEntry.modBaseAddr;
					Module.BaseSize=ModuleEntry.modBaseSize;
					Module.UsageGlobalCount=ModuleEntry.GlblcntUsage;
					Module.UsageProcessCount=ModuleEntry.ProccntUsage;
					_tcscpy(Module.ModuleName,ModuleEntry.szModule);
					_tcscpy(Module.ModulePath,ModuleEntry.szExePath);
					ModulesList.push_back(Module);
				}
				while(Module32Next(hSnapshot,&ModuleEntry));
			//закрыть снимок процесса
			CloseHandle(hSnapshot);
		}
	}

	//сформировать и записать заголовок файла дампа
	DWORD Written;
	DWORD HeadersSize;
	{
		FILE_DUMP_HEADER Header;
		Header.Magics[0]=FILE_DUMP_MAGIC0;
		Header.Magics[1]=FILE_DUMP_MAGIC1;
		Header.RegionsCount=RegionsList.size();
		Header.ThreadsCount=ThreadsList.size();
		Header.ModulesCount=ModulesList.size();
		HeadersSize=sizeof(FILE_DUMP_HEADER)+Header.RegionsCount*sizeof(FILE_DUMP_REGION)+Header.ThreadsCount*sizeof(FILE_DUMP_THREAD)+Header.ModulesCount*sizeof(FILE_DUMP_MODULE);
		Header.FileSize=HeadersSize+MemorySize;
		WriteFile(hFile,&Header,sizeof(Header),&Written,NULL);
	}

	//записать список регионов, добавляя каждому к смещению размеры заголовков
	{
		for(std::list<FILE_DUMP_REGION>::iterator i=RegionsList.begin();i!=RegionsList.end();i++)
		{
			(*i).DataOffset+=HeadersSize;
			WriteFile(hFile,&*i,sizeof(FILE_DUMP_REGION),&Written,NULL);
		}
	}
	//записать список потоков
	{
		for(std::list<FILE_DUMP_THREAD>::iterator i=ThreadsList.begin();i!=ThreadsList.end();i++)
			WriteFile(hFile,&*i,sizeof(FILE_DUMP_THREAD),&Written,NULL);
	}
	//записать список модулей
	{
		for(std::list<FILE_DUMP_MODULE>::iterator i=ModulesList.begin();i!=ModulesList.end();i++)
			WriteFile(hFile,&*i,sizeof(FILE_DUMP_MODULE),&Written,NULL);
	}

	//записать память регионов
	{
		//цикл по регионам
		for(std::list<FILE_DUMP_REGION>::iterator i=RegionsList.begin();i!=RegionsList.end();i++)
		{
			//получить регион
			FILE_DUMP_REGION Region=*i;
			//если регион действителен
			if(Region.State==MEM_COMMIT)
			{
				//получить и записать память региона постранично
				PBYTE pEndAddress=(PBYTE)(Region.BaseAddress+Region.Size);
				static BYTE Buffer[0x1000];
				for(PBYTE pAddress=(PBYTE)Region.BaseAddress;pAddress<pEndAddress;pAddress+=0x1000)
				{
					ReadProcessMemory(hProcess,pAddress,Buffer,0x1000,NULL);
					WriteFile(hFile,Buffer,0x1000,&Written,NULL);
				}
			}
		}
	}

	//закрыть файл
	CloseHandle(hFile);

	//закрыть описатель процесса
	CloseHandle(hProcess);

	//сообщить об успешном завершении
	MessageBox(NULL,TEXT("Dumping process has been finished succesfully."),TEXT("Dumping process"),MB_ICONINFORMATION);
}