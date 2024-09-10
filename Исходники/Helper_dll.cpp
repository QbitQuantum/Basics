	String*	Helper::GetListViewItemText	(DWORD	processID,
										 IntPtr	listViewHWnd,
										 int	rowNum,
										 int	colNum)
	{
		const	int	textSize = 1024; // TODO: figure out the correct size
		HANDLE hProcess = OpenProcess (STANDARD_RIGHTS_REQUIRED | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processID);
		char *pTextProcess = (char *) VirtualAllocEx (hProcess, NULL, textSize, MEM_COMMIT, PAGE_READWRITE);
		LV_ITEM *pListViewItemProcess = (LV_ITEM *) VirtualAllocEx (hProcess, NULL, sizeof (LV_ITEM), MEM_COMMIT, PAGE_READWRITE);

		BOOL	result = FALSE;
		char	pszText[textSize];
		ZeroMemory (pszText, textSize * sizeof (char));
		unsigned long	bytesRead = 0;
		unsigned long	bytesWritten = 0;

		LV_ITEM listViewItem;
		ZeroMemory (&listViewItem, sizeof (listViewItem));
		listViewItem.mask = LVIF_TEXT;
		listViewItem.iItem = rowNum;
		listViewItem.iSubItem = colNum;
		listViewItem.cchTextMax = textSize;
		listViewItem.pszText = pTextProcess;

		result = WriteProcessMemory (hProcess, pListViewItemProcess, &listViewItem, sizeof (listViewItem), &bytesWritten);
		if (!result) {
			char *msg = NULL;
			FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError (), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &msg, 0, NULL);
			String *message = new String (msg);
			LocalFree (msg);
			msg = NULL;
			throw new HelperException ((new String ("WriteProcessMemory Error - "))->Concat (message));
		}

		result = ListView_GetItem ((HWND) listViewHWnd.ToPointer (), pListViewItemProcess);
		if (!result) {
			throw new HelperException ("ListView_GetItem Error - ListView_GetItem failed");
		}

		result = ReadProcessMemory (hProcess, pListViewItemProcess, &listViewItem, sizeof (listViewItem), &bytesRead);
		if (!result) {
			char *msg = NULL;
			FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError (), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &msg, 0, NULL);
			String *message = new String (msg);
			LocalFree (msg);
			msg = NULL;

			throw new HelperException ((new String ("ReadProcessMemory Error - "))->Concat (message));
		}

		result = ReadProcessMemory (hProcess, listViewItem.pszText, pszText, textSize, &bytesRead);
		if (!result) {
			char *msg = NULL;
			FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError (), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &msg, 0, NULL);
			String *message = new String (msg);
			LocalFree (msg);
			msg = NULL;

			throw new HelperException ((new String ("ReadProcessMemory Error - "))->Concat (message));
		}

		String *itemText = new String (pszText);

		return itemText;
	} // GetListViewItemText