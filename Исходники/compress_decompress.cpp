int overwrite(string file, __int64 fsize, __time64_t fmod = NULL){
	char buffer[512];
	char buffer2[256];
	dOverwrite _dOverwrite;
	_dOverwrite.Create(IDD_OVERWRITE);
	HICON ico;
	//_dOverwrite.ShowWindow(SW_SHOW);
	//_dOverwrite.BeginModalState();
	
	sprintf(buffer, loadString(IDS_FILE_ALREADY_EXISTS), file.c_str());
	_dOverwrite.sOverwrite.SetWindowText(buffer);

	struct _finddatai64_t c_file;
	long hFile;
	if((hFile = _findfirsti64(file.c_str(), &c_file)) == -1L){
		//file doesn't exist?
	}else{
		strcpy(buffer2, convertUnits(c_file.size));
		sprintf(buffer, loadString(IDS_OVERWRITE_SIZE), buffer2);
		_dOverwrite.sOriginalSize.SetWindowText(buffer);

		_ctime64_s(buffer2, sizeof(buffer2), &c_file.time_write);
		sprintf(buffer, loadString(IDS_OVERWRITE_MOD), buffer2);
		_dOverwrite.sOriginalMod.SetWindowText(buffer);

		ico = getIcon(file);
		_dOverwrite.iOld.SetIcon(ico);
	}

	
	//new file
	strcpy(buffer2, convertUnits(fsize));
	sprintf(buffer, loadString(IDS_OVERWRITE_SIZE), buffer2);
	_dOverwrite.sNewSize.SetWindowText(buffer);
	if(fmod != NULL){
		_ctime64_s(buffer2, sizeof(buffer2), &fmod);
		sprintf(buffer, loadString(IDS_OVERWRITE_MOD), buffer2);
	}else{
		sprintf(buffer, loadString(IDS_OVERWRITE_MOD), "");
	}
	_dOverwrite.sNewMod.SetWindowText(buffer);
	_dOverwrite.iNew.SetIcon(ico);

	_dOverwrite.ShowWindow(SW_SHOW);
	_dOverwrite.bYes.SetButtonStyle(BS_DEFPUSHBUTTON);
	_dOverwrite.bYesAll.SetButtonStyle(_dOverwrite.bYesAll.GetButtonStyle() & ~BS_DEFPUSHBUTTON);
	return _dOverwrite.RunModalLoop();//_dOverwrite.DoModal();
}