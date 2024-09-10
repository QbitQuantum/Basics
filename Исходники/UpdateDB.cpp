int wmain (int argc,wchar_t ** argv)
{
	CAppData::stdfunc();
	
	_wsetlocale(LC_CTYPE,L".OCP"); 

	SetRegKey(argc,argv);

	if (!SetLanguageSpecifigHandles(argv[0]))
		return 1;

	CArrayFP<CDatabase*> aDatabases;
	
	WORD wCurrentThread=0;

	aDatabases.Add(CDatabase::FromDefaults(TRUE));
	aDatabases[0]->SetNamePtr(alloccopy(L"DEFAULTX"));
	aDatabases[0]->SetThreadId(wCurrentThread);

    int i,helps=0;
#ifndef WIN32
    if (getenv("TZ")==NULL)
		fprintf(stderr,"Timezone is not set. Database may contain invalid file times.\nFor example type "SET TZ=GMT+1" for central european time.\n");
#endif
    for (i=1;i<argc;i++)
    {
        if (argv[i][0]=='-' || argv[i][0]=='/')
        {
            switch (argv[i][1])
			{
			case L'X':
				if (argv[i][2]==L'\0')
				{
					if (i<argc-1)
						i++; // RegKeyName already set
				}
				break;
			case 'l':
			case 'L':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 && 
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else if (argv[i][2]=='1')
				{
					aDatabases.GetLast()->AddLocalRoots();
					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				else 
				{
					CStringW* pStr;
					if (argv[i][2]==L'\0' && i+1<argc)
						pStr=new CStringW(argv[++i]);
					else
						pStr=new CStringW(argv[i]+2);
					
					if ((*pStr)[0]==L'\"')
						pStr->DelChar(0);
					if (pStr->LastChar()==L'\"')
						pStr->DelLastChar();
					while (pStr->LastChar()==L'\\')
						pStr->DelLastChar();
					
					if (pStr->GetLength()>1)
					{
						pStr->ReplaceChars('/','\\');
						if ((*pStr)[1]==':' && pStr->GetLength()==2)
							aDatabases.GetLast()->AddRoot(pStr->GiveBuffer());
						else if (FileSystem::IsDirectory(*pStr))
							aDatabases.GetLast()->AddRoot(pStr->GiveBuffer());
						else
							fwprintf(stderr,ID2W(IDS_UPDATEDB32DIRECTORYISNOTVALID),(LPCWSTR)*pStr);
					}
					else
						fwprintf(stderr,ID2W(IDS_UPDATEDB32DIRECTORYISNOTVALID),(LPCWSTR)*pStr);
					delete pStr;

					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				break;
			case 'e':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 && 
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else 
				{
					CStringW* pStr;
					if (argv[i][2]=='\0' && i+1<argc)
						pStr=new CStringW(argv[++i]);
					else
						pStr=new CStringW(argv[i]+2);
					
					if ((*pStr)[0]==L'\"')
						pStr->DelChar(0);
					if (pStr->LastChar()==L'\"')
						pStr->DelLastChar();
					while (pStr->LastChar()==L'\\')
						pStr->DelLastChar();
					
					if (pStr->GetLength()>0)
						aDatabases.GetLast()->SetExcludedFiles(*pStr);

					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				break;
			case 'E':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 && 
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else 
				{
					CStringW* pStr;
					if (argv[i][2]=='\0' && i+1<argc)
						pStr=new CStringW(argv[++i]);
					else
						pStr=new CStringW(argv[i]+2);
					
					if ((*pStr)[0]==L'\"')
						pStr->DelChar(0);
					if (pStr->LastChar()==L'\"')
						pStr->DelLastChar();
					while (pStr->LastChar()==L'\\')
						pStr->DelLastChar();
					
					if (pStr->GetLength()>1)
					{
						pStr->ReplaceChars('/','\\');
						if (!aDatabases.GetLast()->AddExcludedDirectory(*pStr))
							fwprintf(stderr,ID2W(IDS_UPDATEDB32DIRECTORYISNOTVALID),(LPCWSTR)*pStr);
					}
					else
						fwprintf(stderr,ID2W(IDS_UPDATEDB32DIRECTORYISNOTVALID),(LPCWSTR)*pStr);
					delete pStr;

					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				break;
			case 't':
			case 'T':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 &&
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else if (argv[i][2]==L'c' || argv[i][2]==L'C')
				{
                       if (argv[i][3]==L'\0')
                           aDatabases.GetLast()->SetCreatorPtr(alloccopy(argv[++i]));
                       else
                           aDatabases.GetLast()->SetCreatorPtr(alloccopy(argv[i]+2));

					   aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				else if (argv[i][2]==L'd' || argv[i][2]==L'D')
				{
                       if (argv[i][3]==L'\0')
                           aDatabases.GetLast()->SetDescriptionPtr(alloccopy(argv[++i]));
                       else
                           aDatabases.GetLast()->SetDescriptionPtr(alloccopy(argv[i]+2));

					   aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				break;
			case 'i':
			case 'I':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 &&
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else
				{
                    aDatabases.GetLast()->SetFlag(CDatabase::flagIncrementalUpdate,TRUE);
					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				break;
			case 'c':
			case 'C':
				if (wcsncmp(aDatabases.GetLast()->GetName(),L"PARAMX",6)!=0 &&
					wcsncmp(aDatabases.GetLast()->GetName(),L"DEFAULTX",8)!=0)
					wprintf(ID2W(IDS_UPDATEDB32CANNOTCHANGELOADED),aDatabases.GetLast()->GetName());
				else if (argv[i][2]==L'A' || argv[i][2]==L'a')
				{
					aDatabases.GetLast()->SetFlag(CDatabase::flagAnsiCharset,TRUE);
					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				else if (argv[i][2]==L'U' || argv[i][2]==L'u')
				{
					aDatabases.GetLast()->SetFlag(CDatabase::flagAnsiCharset,FALSE);
					aDatabases.GetLast()->SetNamePtr(alloccopy(L"PARAMX"));
				}
				
				break;
			case 'N':
			case 'n':
				wCurrentThread++;
				break;
			case 'q':
			case 'Q':
				nQuiet=TRUE;
				break;
			case 'v':
			case 'V':
				printf("%s\n",szVersionStr);
				return 0;
			case 'd':
				{
					// Using database file
					CStringW sFile;
					if (argv[i][2]=='\0')
						sFile=argv[++i];
					else
						sFile=(argv[i]+2);
					sFile.ReplaceChars('/','\\');
					if (aDatabases.GetSize()==1 && wcscmp(aDatabases[0]->GetName(),L"DEFAULTX")==0)
					{
						aDatabases[0]->SetNamePtr(alloccopy(L"PARAMX"));
						aDatabases[0]->SetArchiveNamePtr(sFile.GiveBuffer());
					}
					else 
					{
						CDatabase* pDatabase=CDatabase::FromFile(sFile,(int)sFile.GetLength());
						if (pDatabase!=NULL)
						{
                            aDatabases.Add(pDatabase);
							pDatabase->SetNamePtr(alloccopy(L"PARAMX"));
							pDatabase->SetThreadId(wCurrentThread);
						}
					}
					

			
				}
				break;
			case 'D':
				{
					// Loading database 'name' from registry, cannot be changed 
					CStringW sName;
					if (argv[i][2]=='\0')
						sName=argv[++i];
					else
						sName=(argv[i]+2);

					if (CDatabase::FindByName(aDatabases,sName,(int)sName.GetLength())==NULL)
					{
						CDatabase* pDatabase=CDatabase::FromName(HKCU,
							CString(g_szRegKey)+"\\Databases",sName);

						if (pDatabase!=NULL)
						{
							pDatabase->SetFlag(CDatabase::flagGlobalUpdate);
							// Is only default loaded
							if (aDatabases.GetSize()==1 && wcscmp(aDatabases[0]->GetName(),L"DEFAULTX")==0)
							{
								delete aDatabases[0];
								aDatabases[0]=pDatabase;
							}
							else
							{
								aDatabases.Add(pDatabase);
								pDatabase->SetThreadId(wCurrentThread);
							}
						}
					}
				}
				break;
			case 'h':
			case 'H':
			case '?':
				helps=1;
				break;
			default:
				helps=1;
				break;
			}
       }
    }
    if (helps==1)
    {
#ifdef WIN32
		fprintf(stdout,"%s\n",szVersionStr);
#else
        fprintf(stdout,"%s\nusage updatedb",szVersionStr);
#endif

		HRSRC hRc=FindResource(GetLanguageSpecificResourceHandle(),MAKEINTRESOURCE(IDR_UPDATEDBHELP),"HELPTEXT");
		HGLOBAL hGlobal=LoadResource(GetLanguageSpecificResourceHandle(),hRc);
		LPCSTR pStr=(LPCSTR)LockResource(hGlobal);

		// Counting length
		int len;
		for (len=0;pStr[len]!='\0';len++)
		{
			if (pStr[len]=='E' && pStr[len+1]=='O' && pStr[len+2]=='F')
				break;
		}


		fwrite(pStr,1,len,stdout);
		
		FreeLibrary(GetLanguageSpecificResourceHandle());
		return 1;
    }

	// Checking databases
	// First, check that there is database 
	if (aDatabases.GetSize()==0)
		CDatabase::LoadFromRegistry(HKCU,CString(g_szRegKey)+"\\Databases",aDatabases);   
	else if (aDatabases.GetSize()==1 && wcsncmp(aDatabases[0]->GetName(),L"DEFAULTX",8)==0)
	{
		aDatabases.RemoveAll();
		CDatabase::LoadFromRegistry(HKCU,CString(g_szRegKey)+"\\Databases",aDatabases);   

		// No registry values?
		if (aDatabases.GetSize()==0)
		{
			aDatabases.Add(CDatabase::FromDefaults(TRUE));
			aDatabases[0]->SetNamePtr(alloccopy(L"DEFAULTX"));
		}
	}
		
		
	CDatabase::CheckValidNames(aDatabases);
	CDatabase::CheckDoubleNames(aDatabases);
	
	
	for (int i=0;i<aDatabases.GetSize();)
	{
		if (!aDatabases[i]->IsGloballyUpdated())
			aDatabases.RemoveAt(i);
		else 
		{
			if ((wcsncmp(aDatabases[i]->GetName(),L"PARAMX",6)==0 ||
				wcsncmp(aDatabases[i]->GetName(),L"DEFAULTX",8)==0))
			{
				BOOL bNameChanged=FALSE;
				if (aDatabases[i]->GetRoots()==0)
				{
					BOOL bFree;
					LPWSTR pFile=aDatabases[i]->GetResolvedArchiveName(bFree);
					CDatabaseInfo* pDatabaseInfo=CDatabaseInfo::GetFromFile(pFile);
					if (bFree)
						delete[] pFile;
					if (pDatabaseInfo!=NULL)
					{
						CDatabase* pDatabase;
						if (!pDatabaseInfo->sExtra2.IsEmpty())
							pDatabase=CDatabase::FromExtraBlock(pDatabaseInfo->sExtra2);
						if (pDatabase==NULL && !pDatabaseInfo->sExtra1.IsEmpty())
							pDatabase=CDatabase::FromExtraBlock(pDatabaseInfo->sExtra1);
						
						wprintf(ID2W(IDS_UPDATEDB32USINGEXISTINGSETTINGS),
							aDatabases[i]->GetArchiveName(),pDatabase->GetName());
						
						pDatabase->SetArchiveType(aDatabases[i]->GetArchiveType());
						pDatabase->SetArchiveName(aDatabases[i]->GetArchiveName());
						
						delete aDatabases[i];
						aDatabases[i]=pDatabase;

						delete pDatabaseInfo;
						bNameChanged=TRUE;
					}
				}

				if (!bNameChanged)
				{
					ULONG_PTR nFirst=LastCharIndex(aDatabases[i]->GetArchiveName(),L'\\')+1;
					int nLength=LastCharIndex(aDatabases[i]->GetArchiveName()+nFirst,L'.');
					if (nLength==-1)
						nLength=istrlenw(aDatabases[i]->GetArchiveName()+nFirst);

					

					aDatabases[i]->SetNamePtr(alloccopy(aDatabases[i]->GetArchiveName()+nFirst,nLength));
				}
			}

			
			i++;
		}
	}

	// Starting to update
	WORD dwTheads=CDatabase::CheckIDs(aDatabases);
    if (dwTheads==0)
	{
		FreeLibrary(GetLanguageSpecificResourceHandle());
		return FALSE;
	}
	if (dwTheads==1)
	{
		CDatabaseUpdater Updater(aDatabases,aDatabases.GetSize(),UpdateProc);
		Updater.Update(FALSE);
	}
	else
	{
		WORD wThread;

		ppUpdaters=new CDatabaseUpdater*[dwTheads+1];

		for (wThread=0;wThread<dwTheads;wThread++)
		{
			ppUpdaters[wThread]=new CDatabaseUpdater(aDatabases,aDatabases.GetSize(),							
				UpdateProc,wThread,(DWORD)0);
		}
		ppUpdaters[dwTheads]=NULL;

		// Starting
		DWORD dwRunning=0;
		UpdateError ueCode;
		for (wThread=0;wThread<dwTheads;wThread++)
		{
			ueCode=ppUpdaters[wThread]->Update(TRUE);
			if (ueCode==ueSuccess)
				dwRunning++;
			else
			{
				delete ppUpdaters[wThread];
				ppUpdaters[wThread]=UPDATER_EXITED(ueCode);
			}
		}
		
		if (dwRunning==0)
			delete ppUpdaters;
		else
		{
			while (ppUpdaters!=NULL)
				Sleep(100);
		}
	}

	FinishRegKey();

	FreeLibrary(GetLanguageSpecificResourceHandle());

	return 1;
}