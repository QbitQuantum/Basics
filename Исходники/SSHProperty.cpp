BOOL
OnApply(HWND hwnd, PSHNOTIFY* phdr)
{
	CSSHProperty::string_list* files = (CSSHProperty::string_list*)GetWindowLong(hwnd, GWL_USERDATA);
	HANDLE   hFile;

	CSSHProperty::string_list::iterator it = files->begin();

	for(; it != files->end(); ++it) {
		std::wstring file = *it + L":SSHFSProperty.Permission";
		hFile = CreateFile(
					file.c_str(),
					GENERIC_READ,
					FILE_SHARE_READ,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);

		if (hFile == INVALID_HANDLE_VALUE)
			continue;

		char buffer[32];
		DWORD readBytes = 0;
		ZeroMemory(buffer, sizeof(buffer));
		if (!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL)) {
			CloseHandle(hFile);
			continue;
		}
		CloseHandle(hFile);

		int owner = buffer[0] - '0';
		UINT state;
		state = IsDlgButtonChecked(hwnd, IDC_W_EXEC);
		if (state == BST_CHECKED)
			owner |= 0x1;
		if (state == BST_UNCHECKED)
			owner &= ~0x1;
		
		state = IsDlgButtonChecked(hwnd, IDC_W_WRITE);
		if (state == BST_CHECKED)
			owner |= 0x2;
		if (state == BST_UNCHECKED)
			owner &= ~0x2;

		state = IsDlgButtonChecked(hwnd, IDC_W_READ);
		if (state == BST_CHECKED)
			owner |= 0x4;
		if (state == BST_UNCHECKED)
			owner &= ~0x4;


		int group = buffer[1] - '0';
		state = IsDlgButtonChecked(hwnd, IDC_G_EXEC);
		if (state == BST_CHECKED)
			group |= 0x1;
		if (state == BST_UNCHECKED)
			group &= ~0x1;
		
		state = IsDlgButtonChecked(hwnd, IDC_G_WRITE);
		if (state == BST_CHECKED)
			group |= 0x2;
		if (state == BST_UNCHECKED)
			group &= ~0x2;

		state = IsDlgButtonChecked(hwnd, IDC_G_READ);
		if (state == BST_CHECKED)
			group |= 0x4;
		if (state == BST_UNCHECKED)
			group &= ~0x4;


		int other = buffer[2] - '0';
		state = IsDlgButtonChecked(hwnd, IDC_O_EXEC);
		if (state == BST_CHECKED)
			other |= 0x1;
		if (state == BST_UNCHECKED)
			other &= ~0x1;
		
		state = IsDlgButtonChecked(hwnd, IDC_O_WRITE);
		if (state == BST_CHECKED)
			other |= 0x2;
		if (state == BST_UNCHECKED)
			other &= ~0x2;

		state = IsDlgButtonChecked(hwnd, IDC_O_READ);
		if (state == BST_CHECKED)
			other |= 0x4;
		if (state == BST_UNCHECKED)
			other &= ~0x4;


		char newpermission[32];
		ZeroMemory(newpermission, sizeof(newpermission));
		newpermission[0] = owner + '0';
		newpermission[1] = group + '0';
		newpermission[2] = other + '0';

		bool changed = false;
		for(int i=0; i<3; ++i)
			if(buffer[i] != newpermission[i])
				changed = true;

		buffer[3] = '\0';
		//DokanDbgPrint("SSHFSProperty: %s %s -> %s\n",
		//	file.c_str(), buffer, newpermission);

		if (changed) {
			hFile = CreateFile(
				file.c_str(),
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hFile == INVALID_HANDLE_VALUE)
				continue;

			DWORD writtenBytes = 0;
			WriteFile(hFile, newpermission, 3, &writtenBytes, NULL);
			CloseHandle(hFile);
		}

	}

    // Return PSNRET_NOERROR to allow the sheet to close if the user clicked OK.
    SetWindowLong(hwnd, DWL_MSGRESULT, PSNRET_NOERROR);
    return TRUE;
}