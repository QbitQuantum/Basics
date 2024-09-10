void AttachmentViewer::PrepareAttachments(){
	if ( initialized == true ){
		if ( fileWatchController != NULL ){
			fileWatchController->pause = TRUE;  //Needs work but this is to prevent me from getting into an infinite loop
		}
		Document doc = db.getDocument(_id, _rev);

		wchar_t tempdir[MAX_PATH];
		GetTempPath(MAX_PATH, tempdir);

		StringCchCat(tempdir, MAX_PATH, L"cinch\\");
		
		CreateDirectory(tempdir, NULL);

		StringCchCat(tempdir, MAX_PATH, s2ws(_id).c_str());
		
		CreateDirectory(tempdir, NULL);
		
		string dir = ws2s(tempdir);
		string idfile = dir + "\\.id";
		string revfile = dir + "\\.rev";
		
		SetFileAttributes(s2ws(idfile).c_str(), FILE_ATTRIBUTE_NORMAL);
		SetFileAttributes(s2ws(revfile).c_str(), FILE_ATTRIBUTE_NORMAL);


		FILE* f;
		errno_t err = fopen_s(&f, idfile.c_str(), "w");
		if (err == 0 ){
			fwrite(_id.c_str(), sizeof(char), _id.length(), f);
			fclose(f);
		}

		err = fopen_s(&f, revfile.c_str(), "w");
		if ( err == 0 ){
			fwrite(_rev.c_str(), sizeof(char), _rev.length(), f);
			fclose(f);
		}

		SetFileAttributes(s2ws(idfile).c_str(), FILE_ATTRIBUTE_HIDDEN);
		SetFileAttributes(s2ws(revfile).c_str(), FILE_ATTRIBUTE_HIDDEN);


		try {
			vector<Attachment> attachments = doc.getAllAttachments();
			for(unsigned i=0; i<attachments.size(); i++){
				Attachment a = attachments[i];
				a.saveToDirectory(dir);
			}
		}catch(Exception e){
		}
		
		IShellItem *psi;
		HRESULT hr = SHCreateItemFromParsingName(tempdir, 0, IID_PPV_ARGS(&psi)); 
		if (SUCCEEDED(hr)){
			HRESULT hr = _peb->BrowseToObject(psi, EBF_NONE);
		}

		if ( fileWatchController != NULL ){
			fileWatchController->pause = FALSE;
		}

		WatchDirectory(s2ws(dir).c_str());
	}
}