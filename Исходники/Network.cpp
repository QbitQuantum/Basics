void			wififriend_extract_next(GtkWidget* Widget, gpointer Data)
{
	DWORD		Error = ERROR_SUCCESS;
	GtkWidget	*Profil;
	t_wifi		Extract;
	const gchar	*Retrieve;
	long		Size;
	BSTR		UnicodeStr;
	LPWSTR		OutProfil;
	char		*NewProfil;
	FILE		*File;
	int			I = 0;
	char		*PathFile;

	Profil = (GtkWidget *)Data;
	Retrieve = gtk_entry_get_text(GTK_ENTRY(Profil));
	Extract = wififriend_create_handle();
	Extract = wififriend_retrieve_config(Extract);
	Size = lstrlenA(Retrieve);
	UnicodeStr = SysAllocStringLen(NULL, Size);
	MultiByteToWideChar(CP_ACP, 0, Retrieve, Size, UnicodeStr, Size);
	if((Error = WlanGetProfile(Extract.MyHandle, &Extract.MyGuid, UnicodeStr, NULL, &OutProfil, 0, 0)) != ERROR_SUCCESS)
		error_get_profil(0, Retrieve);
	else
	{
		while (OutProfil[I])
			I++;
		NewProfil = (char *)malloc(sizeof(char) * I + 1);
		wcstombs(NewProfil, OutProfil, I + 1);
		PathFile = (char *)malloc(sizeof(char *) * strlen(Retrieve) + 1);
		strcpy(PathFile, Retrieve);
		strcat(PathFile, ".xml");
		File = fopen(PathFile, "w+");
		fputs(NewProfil, File);
		fclose(File);
		free(PathFile);
		error_get_profil_success(0, Retrieve);
	}
	SysFreeString(UnicodeStr);
	WlanCloseHandle(Extract.MyHandle, NULL);
}