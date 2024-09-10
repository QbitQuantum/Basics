BOOL Ckgb_arch_decompressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	/*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);*/

	/*CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, TRUE);		// Set small icon

	// TODO: Add extra initialization here
	
	lFiles.InsertColumn(0, loadString(IDS_FILE), LVCFMT_LEFT, 300);
	lFiles.InsertColumn(1, loadString(IDS_SIZE), LVCFMT_RIGHT, 100);

	
	char curDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, curDir);
	eDestination.SetWindowText(curDir);

	vector<string>files;
	vector<unsigned long>fsize;
	char arch[MAX_PATH];

	HANDLE hProc = GetCurrentProcess();
	HMODULE hMod;
    DWORD cbNeeded;

    EnumProcessModules(hProc, &hMod, sizeof(hMod), &cbNeeded);
    GetModuleFileNameEx(hProc, hMod, arch, MAX_PATH); //pierwszy modu³ jest aplikacj¹
    
//MessageBox("");
	if(isSFXencrypted(arch)){
		//wo³amy o has³o
		dlgPasswd dlgPass;
		if(dlgPass.DoModal() != IDOK){
			theApp.ExitInstance();
			return false;
		}

		strcpy(passwd, dlgPass._passwd);
		for(int i=strlen(passwd);i<32;i++)
			passwd[i] = '\0';
		
		char arch2[MAX_PATH];
		//strcpy(arch2, arch.c_str());
		GetTempPath(MAX_PATH, arch2);
		GetLongPathName(arch2, arch2, sizeof(arch2));
		strcat(arch2, "temp.kgb");
		//arch2[strlen(arch2)-1] = 'b';

		aes_ctx ctx[1];
		ctx->n_rnd = 0; // ensure all flags are initially set to zero
		ctx->n_blk = 0;
		aes_dec_key((const unsigned char*)passwd, 32, ctx);
		
		/*CDialog dProgress;
		dProgress.Create(IDD_DECODING);
		dProgress.ShowWindow(SW_SHOW);
		dProgress.UpdateWindow();*/
		
		FILE *fin = fopen(arch, "rb");
		if(fin == 0)
			return false;
		fseek(fin, isSFXencrypted(arch), SEEK_SET);
		FILE *fout = fopen(arch2, "wb");
		if(fout == 0)
			return false;
		decfile(fin, fout, ctx, arch, arch2);

		fclose(fin);
		fclose(fout);
		/*dProgress.ShowWindow(SW_HIDE);
		dProgress.~CDialog();*/
		if(!checkArchiveFormat(arch2)){
			_fcloseall();
			DeleteFile(arch2);
			//eArchName.SetWindowText("");
			MessageBox(loadString(IDS_WRONG_PASSWD), "KGB Archiver");
			theApp.ExitInstance();
			return false;
		}

		strcpy(arch, arch2);
		getFilesFromArchive(arch, files, fsize);
	}else{
		getFilesFromArchive(arch, files, fsize);
	}
	strcpy(globalARCH, arch);
//MessageBox("");
	for(unsigned long i=0;i<files.size();i++){
		char buffer[32];
		/*if(filesizes[i] < 1024)
			sprintf(buffer, "%dB", filesizes[i]);
		else if(filesizes[i] < 1024*1024)
			sprintf(buffer, "%dKB", filesizes[i]/1024);
		else
			sprintf(buffer, "%dMB", filesizes[i]/1024/1024);
		*/
		sprintf(buffer, "%.1fKB", (double)fsize[i]/1024.0);
		lFiles.InsertItem(0, i, 0, 0, 0, 0, 0);
		
		lFiles.SetItemText(i, 0, files[i].c_str());
		lFiles.SetItemText(i, 1, buffer);
	}

	//MessageBox("");

	//delete curDir;

	/*char *cmd = theApp.m_lpCmdLine;
	char temp[MAX_PATH];
	bool isArchName = true;
	
	/*sscanf(cmd, "-%c", &mode);
	switch(mode){
		case 'c':
			cmd += 2; //przesówamy wskaŸnik* /

	for(unsigned long i=0;i<strlen(cmd);i++){
		if(cmd[i] == '"'){
			for(unsigned long j=0;i+j+1<strlen(cmd);j++){
				if(cmd[i+j+1] != '"')
					temp[j] = cmd[i+j+1];
				else if(cmd[i+j+1] == '"'){
					temp[j] = 0;
					i += j+1;
					if(!isArchName)
						//lFiles.AddString(temp);
						eDestination.SetWindowText(temp);
					else{
						eArchName.SetWindowText(temp);
						isArchName = false;
					}
					break;
				}
			}
		}
	}*/

	//MessageBox(cmd);

	/*if(strlen(temp) == 0 || strlen(cmd) <= 2)
		return TRUE;

	vector<string> files;
	vector<unsigned long> filesizes;
	if(!getFilesFromArchive(temp, files, filesizes)){
		MessageBox("Wybrany plik nie jest prawid³owym archiwum KGB!");
		eArchName.SetWindowText("");
		eDestination.SetWindowText("");
		return TRUE;
	}

	//lFiles.DeleteAllItems();

	for(unsigned long i=0;i<files.size();i++){
		char buffer[32];
		/*if(filesizes[i] < 1024)
			sprintf(buffer, "%dB", filesizes[i]);
		else if(filesizes[i] < 1024*1024)
			sprintf(buffer, "%dKB", filesizes[i]/1024);
		else
			sprintf(buffer, "%dMB", filesizes[i]/1024/1024);
		* /
		sprintf(buffer, "%.1fKB", (double)filesizes[i]/1024.0);
		lFiles.InsertItem(0, i, 0, 0, 0, 0, 0);
		
		lFiles.SetItemText(i, 0, files[i].c_str());
		lFiles.SetItemText(i, 1, buffer);
	}*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}