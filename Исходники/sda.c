PGPError SDAEncryptFile(MYSTATE *ms,
		PGPSymmetricCipherContextRef CASTContext)
{
	SDAHEADER *SDAHeader;
	FILE *fout;
	char inbuffer[kBlockSize];
	char outbuffer[kBlockSize];
	char szOutput[MAX_PATH+1];
	PGPFileSpecRef filespec;
	char *fullPathPtr;
	BOOL CancelOperation;
	GETPUTINFO gpi;
	DWORD dwStubSize;
	HRSRC hRCStub;
	HGLOBAL hGBStub;
	char *pStubData;
	FILELIST *flnext,*fl;
	char *lastslash;
	BOOL OneDirectory;
	char szCaption[256];

	hRCStub=FindResource(g_hinst,
		MAKEINTRESOURCE(IDR_SDASTUB),
		RT_RCDATA);

	dwStubSize=SizeofResource(g_hinst,hRCStub);

	hGBStub=LoadResource(g_hinst,hRCStub);
	pStubData=(char *)LockResource(hGBStub);

	// Sanity checking here for resource munging
	if(!((*(USHORT *)pStubData == IMAGE_DOS_SIGNATURE) &&
        (*(DWORD *)NTSIGNATURE (pStubData) == IMAGE_NT_SIGNATURE)))
	{
		PGPscMessageBox (ms->hwndWorking,IDS_PGPERROR,IDS_COULDNOTOPENSTUB,
		MB_OK|MB_ICONSTOP);

		return kPGPError_NoErr;
	}

	// Reverse list since we need directories first
	fl=NULL;

	while(ms->ListHead!=NULL)
	{
		flnext=ms->ListHead->next;
		
		ms->ListHead->next=fl;
		fl=ms->ListHead;

		ms->ListHead=flnext;
	}

	// Now same, but reversed
	ms->ListHead=fl;

	// Check to see if we only have one directory with contents
	OneDirectory=ms->ListHead->IsDirectory;

	SDAHeader=ms->SDAHeader;

	strcpy(szOutput,ms->ListHead->name);
	strcat(szOutput,".sda.exe");

	if(OneDirectory)
	{
		LoadString (g_hinst, IDS_FILECONFLICT, szCaption, sizeof(szCaption));

		// Do automatically if possible
		CancelOperation=SaveOutputFile(ms->context,
			ms->hwndWorking, 
			szCaption,
			szOutput, 
			&filespec,
			FALSE);
	}
	else
	{
		LoadString (g_hinst, IDS_CONFIRMSDANAME, szCaption, sizeof(szCaption));

		// Always check with the user first
		CancelOperation=SaveOutputFile(ms->context,
			ms->hwndWorking, 
			szCaption,
			szOutput, 
			&filespec,
			TRUE);
	}

	if(CancelOperation)
		return kPGPError_UserAbort;

	PGPGetFullPathFromFileSpec( filespec,
		&fullPathPtr);

	strcpy(szOutput,fullPathPtr);
	PGPFreeData(fullPathPtr);
	PGPFreeFileSpec(filespec);

	fout=fopen(szOutput,"wb");

	if(fout==0)
	{
		PGPscMessageBox (ms->hwndWorking,IDS_PGPERROR,IDS_COULDNOTOPENFILE,
				MB_OK|MB_ICONSTOP);

		return kPGPError_UserAbort;
	}

	// Copy SDA.exe prefix executable into SDA file and
	// set header offset so we can find data again.
	// Write out stub to disk from resources
	fwrite(pStubData,1,dwStubSize,fout);

	UnlockResource(hGBStub);
	FreeResource(hGBStub);

	SDAHeader->offset=dwStubSize;

	// Initialize variables for compression call
	memset(&gpi,0x00,sizeof(GETPUTINFO));

	gpi.fout=fout;
	gpi.SDAHeader=SDAHeader;
	gpi.blockindex=0;
	gpi.outbuffer=outbuffer;
	gpi.inbuffer=inbuffer;
	gpi.hwnd=ms->hwndWorking;
	gpi.CASTContext=CASTContext;
	gpi.from_pointer=0;
	gpi.CancelOperation=FALSE;
	gpi.ms=ms;
	gpi.bFeedFilename=TRUE;
	gpi.fl=fl;
	gpi.hPrgDlg=(HPRGDLG)GetWindowLong(ms->hwndWorking, GWL_USERDATA);

	// Find beginning of SDA directory tree
	lastslash=strrchr(gpi.fl->name,'\\');
	if(lastslash==NULL)
		lastslash=gpi.fl->name;
	else
		lastslash++;

	gpi.PathHead=lastslash-gpi.fl->name;

	Deflate_Compress(&gpi);

	if(gpi.fin)
		fclose(gpi.fin);

	fl=NULL;

	// Re-reverse list since we may need to delete
	while(ms->ListHead!=NULL)
	{
		flnext=ms->ListHead->next;
		
		ms->ListHead->next=fl;
		fl=ms->ListHead;

		ms->ListHead=flnext;
	}

	// Now same, but reversed
	ms->ListHead=fl;

	// Write out the last block since compress doesn't
	// know how we are delaying writes
	if(gpi.to_pointer!=0)
	{
		EncryptBlock512(gpi.CASTContext,
			gpi.SDAHeader,
			gpi.blockindex,
			(const PGPUInt32 *)gpi.inbuffer,
			(PGPUInt32 *)gpi.outbuffer);

		fwrite(gpi.outbuffer,1,kBlockSize,gpi.fout);
	}

	fwrite(SDAHeader,1,sizeof(SDAHEADER),fout);

	memset(inbuffer,0x00,kBlockSize);
	memset(outbuffer,0x00,kBlockSize);

	fclose(fout);

	if(gpi.CancelOperation)
	{
		remove(szOutput);
		return kPGPError_UserAbort;
	}

	return kPGPError_NoErr;
}