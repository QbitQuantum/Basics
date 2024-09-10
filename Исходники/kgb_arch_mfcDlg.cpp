DWORD WINAPI zipCompress(LPVOID lpParam){
	_filename = COMPRESS_PREPARING;
	sTime = time(NULL);

	CZipArchive zip;
	vector<__int64>filesize;
	_size_all = 1;

	/*char b[123];
	sprintf(b, "%d", spanSize);
	MessageBox(0, b, "", 0);*/
	
	if(spanSize == 0)
		zip.Open(archive_name, CZipArchive::OpenMode::zipCreate);
	else
		zip.Open(archive_name, CZipArchive::OpenMode::zipCreateSpan, spanSize);
	zip.SetPassword(passwd);
	//zip.SetAutoFlush();
	
	_filename = COMPRESS_GETTING_FILE_SIZES;
	for (int i=0; i<int(filename.size()); ++i) {
      FILE* f=fopen(filename[i].c_str(), "rb");
      if(f){
		_fseeki64(f, 0LL, SEEK_END);
		filesize.push_back(_ftelli64(f));
        _size_all += _ftelli64(f);
        fclose(f);
      }
    }

	for(int i=0;i<filename.size();i++){
		_filename = filename[i];
		//zip.AddNewFile(filename[i].c_str(), MEM);
		zip.AddNewFile(filename[i].c_str(), filename[i].c_str(), MEM);
		_done_all += filesize[i];
		
		CZipFileHeader fhInfo;
		zip.GetFileInfo(fhInfo, i);
		_compressed += fhInfo.GetEffComprSize() + fhInfo.GetSize() + fhInfo.GetExtraFieldSize();
		
	}
	zip.Close();

	/*FILE *f = fopen(archive_name, "rb");
	if(f){
		_fseeki64(f, 0LL, SEEK_END);
		_compressed = _ftelli64(f);
		fclose(f);
	}*/

	if(sfx_arch){ //do³¹czamy modu³ sfx
		_filename = COMPRESS_ADDING_SFX_MOD;
		
		/*archive_name[strlen(archive_name)-3] = '\0';
		sprintf(archive_name, "%sexe", archive_name);*/

		//odczytujemy œcie¿kê do modu³u
		HANDLE hProc = GetCurrentProcess();
		HMODULE hMod;
        DWORD cbNeeded;
		char processName[MAX_PATH];

        EnumProcessModules(hProc, &hMod, sizeof(hMod), &cbNeeded);
        GetModuleFileNameEx(hProc, hMod, processName, MAX_PATH);
        
		for(int i=strlen(processName)-1;i>=0;i--){
			if(processName[i] == '\\' || processName[i] == '/'){
				processName[i+1] = '\0';
				sprintf(processName, "%skgb_arch_sfx_zip.mod", processName);
				break;
			}
		}

		FILE *sfx = fopen(processName, "rb");

		//MessageBox(0, "", "", 0);
		if(sfx == NULL){
			MessageBox(0, "An internal error has occured, please reinstall KGB Archiver!", "KGB Archiver", 0);
			_fcloseall();
			DeleteFile(archive_name);
			return false;
		}

		//MessageBox(0, archive_name, "", 0);

		FILE *archive = fopen(archive_name, "rb");
		if(archive == NULL){
			_fcloseall();
			return false;
		}
		//MessageBox(0, "", "", 0);

		archive_name[strlen(archive_name)-3] = '\0';
		sprintf(archive_name, "%sexe", archive_name);

		//MessageBox(0, archive_name, "", 0);

		FILE *archive_sfx = fopen(archive_name, "wb");
		if(archive_sfx == NULL){
			_fcloseall();
			return false;
		}

		//MessageBox(0, "2", "", 0);

		int count=0;
		char buffer[65536];
		while(!feof(sfx)){
			count = fread(buffer, sizeof(char), sizeof(buffer), sfx);
			fwrite(buffer, sizeof(char), count, archive_sfx);
		}
		while(!feof(archive)){
			count = fread(buffer, sizeof(char), sizeof(buffer), archive);
			fwrite(buffer, sizeof(char), count, archive_sfx);
		}
		fclose(archive);
		fclose(sfx);
		fclose(archive_sfx);

		archive_name[strlen(archive_name)-3] = '\0';
		sprintf(archive_name, "%szip", archive_name);
		DeleteFile(archive_name);
	}

	_done_all++;

	return true;
}