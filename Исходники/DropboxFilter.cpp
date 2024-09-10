void EditConfig()
{
	GetDropboxPath();
	if(dropboxPath[0] == 0) {
		MessageBox(NULL,"Cant find where your dropbox path is.\n\nIs dropbox installed?","Error",MB_OK);
		return;
	}
	char configPath[MAX_PATH];
	sprintf(configPath,"%s\\DropboxFilter.cfg",dropboxPath);
	FILE *file = fopen(configPath,"r");
	if(file == NULL) {
		if(MessageBoxA(NULL,"I cant find a config file DropboxFilter.cfg in your dropbox folder, do you wish to create a default one?","Default config file",MB_YESNO) == IDYES) {
			FILE *file = fopen(configPath,"wb");
			int written;
			HRSRC hResource;
			if(file) {
				hResource = FindResource(NULL,"ID_CONFIG","TXT");
				void *resource = LockResource(LoadResource(NULL,hResource));
				written = fwrite(resource,1,SizeofResource(NULL,hResource),file);
				fclose(file);
			}
			if(file == NULL || written != SizeofResource(NULL,hResource)) {
				MessageBox(NULL,"Failed to copy default config to dropbox folder.","Failed",MB_OK);
			}
		} else {
			return;
		}
	} else {
		fclose(file);
	}
	char notepadExe[MAX_PATH];
	sprintf(notepadExe,"%s\\notepad.exe",getenv("SystemRoot"));
	_spawnl(_P_DETACH,notepadExe,notepadExe,configPath,NULL);
}