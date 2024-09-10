// MW-2005-05-15: Updated for new answer command restructuring
int MCA_folder(MCStringRef p_title, MCStringRef p_prompt, MCStringRef p_initial, unsigned int p_options, MCStringRef &r_value, MCStringRef &r_result)
{
	if (MCmajorosversion >= 0x0600 && MCModeMakeLocalWindows())
		return MCA_file(p_title, p_prompt, nil, p_initial, p_options | MCA_OPTION_FOLDER_DIALOG, r_value, r_result);

// MW-2005-05-27: We'll use a static (I know bad me) to store the version
//   of the shell dll.
	static int s_shell_version = -1;
	static MCStringRef s_last_folder = MCValueRetain(kMCEmptyString);

	MCAutoStringRef t_native_filename;

	if (p_initial != NULL)
	{
		MCAutoStringRef t_std_path;

		/* UNCHECKED */ MCS_pathfromnative(p_initial, &t_std_path);
		t_native_filename = *t_std_path;
	}
	else
		t_native_filename = MCValueRetain(s_last_folder);

	if (!MCModeMakeLocalWindows())
    {
		MCAutoStringRef t_answer_path;
		MCRemoteFolderDialog(p_title, p_prompt, *t_native_filename, &t_answer_path);
        if (*t_answer_path != nil)
		{
			MCAutoStringRef t_std_path;

			/* UNCHECKED */ MCS_pathfromnative(*t_answer_path, &t_std_path);
			MCValueAssign(s_last_folder, *t_std_path);
		}
		r_value = MCValueRetain(*t_answer_path);
		return 0;
	}

	if (s_shell_version == -1)
		s_shell_version = get_dll_version(L"shell32.dll");

	bool sheet = (p_options & MCA_OPTION_SHEET) != 0;

	BROWSEINFOW bi;
	memset(&bi, 0, sizeof(BROWSEINFOW));

	Window pw;
	pw = MCModeGetParentWindow();

	if (pw != DNULL)
		bi.hwndOwner = (HWND)pw->handle.window;

	MCAutoStringRefAsWString t_prompt_wstr;
	MCAutoStringRefAsWString t_native_filename_wstr;
	/* UNCHECKED */ t_prompt_wstr.Lock(p_prompt);

	bi.pidlRoot = NULL;
	bi.lpszTitle = *t_prompt_wstr;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	if (s_shell_version >= 500)
		bi.ulFlags |= BIF_NEWDIALOGSTYLE;
	if (*t_native_filename != nil && !MCStringIsEmpty(*t_native_filename))
	{
		t_native_filename_wstr.Lock(*t_native_filename);
		
		bi . lpfn = BrowseCallbackProc;
		bi . lParam = (LPARAM)*t_native_filename_wstr;
	}
	else
	{
		bi.lpfn = NULL;
		bi.lParam = NULL;
	}
	LPITEMIDLIST lpiil;
	LPMALLOC lpm;
	SHGetMalloc(&lpm);

	DWORD t_error;
	lpiil = SHBrowseForFolderW(&bi);
	if (lpiil == NULL)
	{
		t_error = GetLastError();
	}
	
	MCAutoArray<unichar_t> t_buffer;
	/* UNCHECKED */ t_buffer.New(MAX_PATH);

	if (lpiil != NULL && SHGetPathFromIDListW(lpiil, t_buffer.Ptr()))
	{
		if (s_last_folder != NULL)
			MCValueRelease(s_last_folder);

		size_t t_length;
		/* UNCHECKED */ StringCchLength(t_buffer.Ptr(), t_buffer.Size(), &t_length);
		/* UNCHECKED */ MCStringCreateWithChars(t_buffer.Ptr(), t_length, s_last_folder);

		MCAutoStringRef t_std_path;
		/* UNCHECKED */ MCS_pathfromnative(s_last_folder, &t_std_path);

		r_value = MCValueRetain(*t_std_path);
	}
	else
		r_result = MCSTR(MCcancelstring);

	//  SMR 1880 clear shift and button state
	waitonbutton();

	lpm->Free(lpiil);
	lpm->Release();

	return 0;
}