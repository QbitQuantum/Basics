	std::set<wxString, wxStringOrdinalComparator> ProcessManager::GetModulesForProcessIdInternalV3(int processID, DWORD& resultCode)
	{
		unique_handle hProcessSnap(CreateToolhelp32Snapshot(TH32CS_SNAPALL | TH32CS_SNAPMODULE32 | TH32CS_SNAPPROCESS, 0));
		if (hProcessSnap.get() == INVALID_HANDLE_VALUE)
			return set<wxString, wxStringOrdinalComparator>();
		MODULEENTRY32W me32;
		me32.dwSize = sizeof(MODULEENTRY32W);
		if (!Module32FirstW(hProcessSnap.get(), &me32))
		{
			return set<wxString, wxStringOrdinalComparator>();
		}

		set<wxString, wxStringOrdinalComparator> resultList;
		do
		{
			resultList.insert(me32.szExePath);
		} while (Module32NextW(hProcessSnap.get(), &me32));
		return move(resultList);
	}