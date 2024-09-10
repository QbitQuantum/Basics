void NewCreateFile(void *lpVoid)
{
	struct Device	*dev;
	int iType;
	char			tempStr[31];
	HWND			dlg = (HWND)lpVoid;
	int				type = 0;
	char strNewFileName[MAX_PATH * 2];
	struct Volume	*vol;
	HXCFLOPPYEMULATOR* hxcfe;
	FLOPPY * fp;
	int loaderId;

	Percent = 0;

	iType = SendMessage(GetDlgItem(dlg, IDC_NEWHFE), BM_GETCHECK, 0, 0l);
	if(iType == BST_CHECKED)
	{
		strcpy(strNewFileName, dirTemp);
		MakeSureDirectoryPathExists(dirTemp);				// Create temp dir.
		strcat(strNewFileName,"newfile.adf");
	}
	else
	{
		strcpy(strNewFileName,gstrFileName);
	}

	if (Size == 1760) /* 880KB Floppy */
		dev = adfCreateDumpDevice(strNewFileName, 80, 2, 11);
	else
		if (Size == (1760 * 2)) /* HD Floppy */
			dev = adfCreateDumpDevice(strNewFileName, 80, 2, 22);
		else /* hardfile */
			dev = adfCreateDumpDevice(strNewFileName, Size, 1, 1);

	GetDlgItemText(dlg, IDC_NEWLABEL, tempStr, sizeof(tempStr));

	if (SendMessage(GetDlgItem(dlg, IDC_NEWFFS), BM_GETCHECK, 0, 0l) == BST_CHECKED)
		type += FSMASK_FFS;
	if (SendMessage(GetDlgItem(dlg, IDC_NEWINTL), BM_GETCHECK, 0, 0l) == BST_CHECKED)
		type += FSMASK_INTL;
	if (SendMessage(GetDlgItem(dlg, IDC_NEWDIRC), BM_GETCHECK, 0, 0l) == BST_CHECKED)
		type += FSMASK_DIRCACHE;
	
	if ((Size == 1760) || (Size == 1760 * 2)){
		adfCreateFlop(dev, tempStr, type);
		// Install bootblock if "Bootable" selected.
		if(SendMessage(GetDlgItem(dlg, IDC_NEWBOOTABLE), BM_GETCHECK, 0, 0l) == BST_CHECKED){
			vol = adfMount(dev, 0, FALSE);
			InstallBootBlock(dlg, vol, TRUE);
		}
	}
	else
		adfCreateHdFile(dev, tempStr, type);

	adfUnMountDev(dev);

	if(iType == BST_CHECKED)
	{
		hxcfe=hxcfe_init();

		fp=0;
		// Load the image
		loaderId=hxcfe_autoSelectLoader(hxcfe,strNewFileName,0);
			// Load the image
		if(loaderId>=0)
			fp=hxcfe_floppyLoad(hxcfe,strNewFileName,loaderId,0);
		if(fp)
		{
			// Select the HFE loader/exporter.
			loaderId=hxcfe_getLoaderID(hxcfe,"HXC_HFE");
			// Save the file...
			hxcfe_floppyExport(hxcfe,fp,gstrFileName,loaderId);
			// Free the loaded image
			hxcfe_floppyUnload(hxcfe,fp);
		}
		hxcfe_deinit(hxcfe);

		// Delete intermediate adf.
		remove(strNewFileName);
	}

	Done = TRUE;
}