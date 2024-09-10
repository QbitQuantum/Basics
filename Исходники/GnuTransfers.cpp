CGnuDownloadShell* CGnuTransfers::LoadDownloadHosts(CString FilePath)
{
	// Check if file already loaded
	for(int i = 0; i < m_DownloadList.size(); i++)
		if( m_DownloadList[i]->m_BackupPath.CompareNoCase(FilePath) == 0 )
			return NULL;


	CStdioFile BackupFile;

	CString NextLine;
	CString Backup;
	
	if (BackupFile.Open(FilePath, CFile::modeRead))
	{
		while (BackupFile.ReadString(NextLine))
			Backup += NextLine + "\n";

		BackupFile.Abort();
	}

	if(Backup.IsEmpty() || Backup.Find("[Download]") == -1)
		return NULL;

	int CurrentPos = Backup.Find("[Download]");

	CGnuDownloadShell* Download = new CGnuDownloadShell(this);
	
	Download->m_ShellStatus		= (CGnuDownloadShell::Status) atoi(GetBackupString("Status", CurrentPos, Backup));
	Download->m_Name			= GetBackupString("Name", CurrentPos, Backup);
	Download->m_FileLength		= _atoi64(GetBackupString("FileLength", CurrentPos, Backup));
	Download->m_PartSize		= atoi(GetBackupString("PartSize", CurrentPos, Backup));
	Download->m_OverrideName	= GetBackupString("OverrideName", CurrentPos, Backup);
	Download->m_OverridePath	= GetBackupString("OverridePath", CurrentPos, Backup);
	Download->m_PartialPath		= GetBackupString("PartialPath", CurrentPos, Backup);
	Download->m_BackupPath  	= FilePath;
	Download->m_Sha1Hash		= GetBackupString("Sha1Hash", CurrentPos, Backup);
	Download->m_Search			= GetBackupString("Search", CurrentPos, Backup);
	Download->m_AvgSpeed		= atoi(GetBackupString("AvgSpeed", CurrentPos, Backup));
	Download->m_HashComputed	= atoi(GetBackupString("HashComputed", CurrentPos, Backup));
	Download->m_HashVerified	= atoi(GetBackupString("HashVerified", CurrentPos, Backup));
	Download->m_FileMoved		= atoi(GetBackupString("FileMoved", CurrentPos, Backup));
	Download->m_ReasonDead		= GetBackupString("ReasonDead", CurrentPos, Backup);
	Download->m_MetaXml         = GetBackupString("Meta", CurrentPos, Backup);

	Download->m_UseProxy		= atoi(GetBackupString("UseProxy", CurrentPos, Backup));
	Download->m_DefaultProxy	= GetBackupString("DefaultProxy", CurrentPos, Backup);

	Download->m_TigerHash		= GetBackupString("TigerHash", CurrentPos, Backup);
	Download->m_TreeSize		= atoi(GetBackupString("TreeSize", CurrentPos, Backup));
	Download->m_TreeRes			= atoi(GetBackupString("TreeRes", CurrentPos, Backup));

	if(Download->m_TreeSize)
	{
		Download->m_TigerTree = new byte[Download->m_TreeSize];
		memset(Download->m_TigerTree, 0, Download->m_TreeSize);
	}

	if(Download->m_TigerTree)
	{
		CString Value = GetBackupString("TigerTree", CurrentPos, Backup);

		int buffPos = 0;
		int dotPos  = Value.Find(".");

		while(dotPos != -1 && buffPos < Download->m_TreeSize)
		{
			DecodeBase32( Value.Mid(dotPos - 39, 39), 39, Download->m_TigerTree + buffPos, Download->m_TreeSize - buffPos );

			buffPos += 24;
			dotPos = Value.Find(".", dotPos + 1);
		}
	}


	Download->Init(Download->m_Name, Download->m_FileLength, HASH_SHA1, Download->m_Sha1Hash);

	
	// Load Host info
	if( !Download->m_FileMoved )
		for(int i = 0; ; i++)
		{
			CurrentPos = Backup.Find("[Host " + NumtoStr(i) + "]");

			if(CurrentPos == -1)
				break;

			CurrentPos += 5; // Host in header and value conflict

			FileSource nResult;
			nResult.Name = GetBackupString("Name", CurrentPos, Backup);
			nResult.NameLower = nResult.Name;
			nResult.NameLower.MakeLower();

			nResult.Sha1Hash	 = GetBackupString("Sha1Hash", CurrentPos, Backup);
			//nResult.BitprintHash = GetBackupString("BitprintHash", CurrentPos, Backup);

			nResult.FileIndex	= atoi(GetBackupString("FileIndex", CurrentPos, Backup));
			nResult.Size		= _atoi64(GetBackupString("Size", CurrentPos, Backup));

			nResult.Address.Host = StrtoIP(GetBackupString("Host", CurrentPos, Backup));
			nResult.Address.Port = atoi(GetBackupString("Port", CurrentPos, Backup));
			nResult.Network      = atoi(GetBackupString("Network", CurrentPos, Backup));
			nResult.HostStr		 = GetBackupString("HostStr", CurrentPos, Backup);
			nResult.Path		 = GetBackupString("Path", CurrentPos, Backup);
			nResult.Speed		 = atoi(GetBackupString("Speed", CurrentPos, Backup));
			nResult.Vendor		 = GetBackupString("Vendor", CurrentPos, Backup);

			nResult.Firewall	= atoi(GetBackupString("Firewall", CurrentPos, Backup)) != 0;
			nResult.OpenSlots	= atoi(GetBackupString("OpenSlots", CurrentPos, Backup)) != 0;
			nResult.Busy		= atoi(GetBackupString("Busy", CurrentPos, Backup)) != 0;
			nResult.Stable		= atoi(GetBackupString("Stable", CurrentPos, Backup)) != 0;
			nResult.ActualSpeed = atoi(GetBackupString("ActualSpeed", CurrentPos, Backup)) != 0;
			nResult.SupportF2F  = atoi(GetBackupString("SupportF2F", CurrentPos, Backup)) != 0;
			DecodeBase16(GetBackupString("PushID", CurrentPos, Backup), 32, (byte*) &nResult.PushID, 16);

			CString Nodes = GetBackupString("Direct", CurrentPos, Backup);
			while(!Nodes.IsEmpty())
				nResult.DirectHubs.push_back( StrtoIPv4(ParseString(Nodes, ',')) );

			nResult.GnuRouteID = 0;
			nResult.Distance = 7;
			//nResult.Icon     = m_pCore->GetIconIndex(nResult.Name);

			Download->AddHost(nResult);
		}

	//Download->m_DoReQuery = true;


	// Add Download to list
	m_DownloadAccess.Lock();
	m_DownloadList.push_back(Download);
	m_DownloadAccess.Unlock();

	TransferLoadMeta();

	if(Download->m_ShellStatus == CGnuDownloadShell::eActive)
		Download->Start();

	return Download;
}