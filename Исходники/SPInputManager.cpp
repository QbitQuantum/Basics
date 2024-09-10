	bool SPInputManager::SetCursor( SPString path )
	{
		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			return false;
		}

		LONGLONG length = file->GetFileLength();
		char* pData = new char[length];
		file->Read(pData, length);

		wchar_t tname[10];		
		_wtmpnam_s(tname, 10);

		SPString name = SPString(tname);// + path.substr(path.find_last_of(L".") + 1);

		HANDLE newFile = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (newFile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD numOfByte;
		if(FALSE == WriteFile(newFile, pData, length, &numOfByte, NULL))
		{ 
			delete [] pData;
			SPFileManager::GetSingleton().CloseFile(path);
			CloseHandle(newFile);
			DeleteFile(name.c_str());
			return false;
		}

		CloseHandle(newFile);
		HCURSOR cursor = LoadCursorFromFile(name.c_str());
		if (!cursor)
		{
			DWORD err = GetLastError();
			delete [] pData;
			SPFileManager::GetSingleton().CloseFile(path);
			CloseHandle(newFile);
			DeleteFile(name.c_str());
			return false;
		}

		SPWindow::GetSingleton().SetCursor(cursor);

		DeleteFile(name.c_str());

		delete [] pData;
		SPFileManager::GetSingleton().CloseFile(path);
		//CloseHandle(newFile);

		return true;
	}