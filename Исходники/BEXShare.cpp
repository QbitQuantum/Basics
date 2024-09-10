int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.




	char
		szDate[30]					= {0},
		szDateTime[30]				= {0},
		szTemp[_MAX_PATH]			= {0},
		szApplicationLog[_MAX_PATH] = {0};

	try
	{
		char
			*ptr  = NULL,
			*ptr1 = NULL,
			szBexRegVerPath[_MAX_PATH]		= {0},
			szBexRegDataPath[_MAX_PATH]		= {0},
			szBexVerion[30]					= {0},
			szBexDataFilePath[_MAX_PATH]	= {0},
			szAppPath[_MAX_PATH]			= {0};

		Sleep(30*1000);
		memset(szBexRegVerPath, NULL, sizeof(szBexRegVerPath));
		memset(szBexRegDataPath, NULL, sizeof(szBexRegDataPath));
		memset(szBexVerion, NULL, sizeof(szBexVerion));
		memset(szBexDataFilePath, NULL, sizeof(szBexDataFilePath));
		memset(szTemp, NULL, sizeof(szTemp));
		memset(szAppPath, NULL, sizeof(szAppPath));	
		memset(szApplicationLog, NULL, sizeof(szApplicationLog));
		
		
		::GetModuleFileName(NULL,szAppPath, sizeof(szAppPath));
		ptr = strrchr(szAppPath, '\\');
		if(ptr)
		{
			ptr++;
			*ptr = '\0';
		}  
		sprintf(szApplicationLog, "%s\\ApplicationLog\\BEXShare.log", szAppPath);

		//Log
		memset(szDateTime, NULL, sizeof(szDateTime));
		memset(szTemp, NULL, sizeof(szTemp));
		GetDateTime(szDate,szDateTime);
		sprintf(szTemp, "%s\tStarting Application BEX Share \r\n",szDateTime);
		WriteToLog(szApplicationLog, szTemp);

		CRegKey
			objReg;

		long
			lError = 0;

		bool 
			bBackupInstalled = false;
		

////////////////////////////////////////////////////////////////
		//Read Reg ID
		char 
			szRegID[100] = {0},
			szLocalRegPath[MAX_PATH + 100]	=	{0},
			*szError= NULL;

		DWORD 
			dwBexVersn = 8;

		memset(szRegID, NULL, sizeof(szRegID));

		memset(szLocalRegPath,0,sizeof(szLocalRegPath));
		strcpy(szLocalRegPath,"SOFTWARE\\SAAZOD\0");

		if(!ReadRegistryForLocalRegid(szLocalRegPath,szRegID, szError))
		{
			memset(szTemp, NULL, sizeof(szTemp));
			sprintf(szTemp, "%s\tFailed Reading Local Registry %s. \r\n",szDateTime, szError);
			WriteToLog(szApplicationLog, szTemp);
			delete [] szError; 
			szError = NULL;
			
			return 0;
		}


////////////////////////////////////////////////////////////////
		do {

/*	Checking for Symantec
 *  Read Symantec Install Version 12.x
 */

			DWORD 
				dwCount    = _MAX_PATH;

			lstrcpy(szBexRegVerPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\12.0\\Install");
			lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegVerPath, KEY_READ);
			
			if (ERROR_SUCCESS != lError)
			{
				lstrcpy(szBexRegVerPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\11.0\\Install");
				lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegVerPath, KEY_READ);
			}

			
			if (ERROR_SUCCESS != lError)
			{
				lstrcpy(szBexRegVerPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\Install");
				lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegVerPath, KEY_READ);
			}


			if(ERROR_SUCCESS == lError)
			{
				//Log
				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "%s\tSuccessfully Opened Registry for Symantec :\r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);

				lError = objReg.QueryValue(dwBexVersn,"Major Version\0"); 
				
				if(ERROR_SUCCESS == lError)
				{
					//Log
					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tSymantec Version Installed [%d]:\r\n",szDateTime, dwBexVersn);
					WriteToLog(szApplicationLog, szTemp);

					bBackupInstalled = true;
					if (dwBexVersn > 8)
					{
						dwBexVersn = 9;
					}

					//Read Symantec Data Dir Path
					memset(szBexRegDataPath, NULL, sizeof(szBexRegDataPath));
					lstrcpy(szBexRegDataPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\Engine\\Misc");
			
					lError = objReg.Close();
					lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegDataPath, KEY_READ);
					lError = objReg.QueryValue(szBexDataFilePath,"Data Path\0",&dwCount);

					if(ERROR_SUCCESS == lError)
					{
						//Log
						memset(szTemp, NULL, sizeof(szTemp));
						sprintf(szTemp, "%s\tSymantec DataFilePath [%s]:\r\n",szDateTime, szBexDataFilePath);
						WriteToLog(szApplicationLog, szTemp);
					}
					else
					{
						//Symantec data file path not found
						//Log
						lError = objReg.Close();

						memset(szTemp, NULL, sizeof(szTemp));
						sprintf(szTemp, "%s\tSymantec Data File Path not Found. \r\n",szDateTime);
						WriteToLog(szApplicationLog, szTemp);
						GeneratePID(szRegID,"SUCCESS\0", "Symantec Data File Path not Found.\0");
						
						bBackupInstalled = false;
						//return 0;
						///		goto SRV;
						break;
					}

					lError = objReg.Close();

				}//Query Value 
				else
				{
					objReg.Close();


/*					
				//Log
					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tTrying Symmantec Version 2nd Path :\r\n",szDateTime);
					WriteToLog(szApplicationLog, szTemp);

//Symmantec 2nd Path
					memset(szBexRegVerPath, NULL, sizeof(szBexRegVerPath));
					lstrcpy(szBexRegVerPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\11.0\\Install");
					lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegVerPath, KEY_READ);

					if(ERROR_SUCCESS == lError)
					{
						//Log
						memset(szTemp, NULL, sizeof(szTemp));
						sprintf(szTemp, "%s\tSuccessfully Opened Registry for Symantec :\r\n",szDateTime);
						WriteToLog(szApplicationLog, szTemp);

						lError = objReg.QueryValue(dwBexVersn,"Major Version\0"); 
						
						if(ERROR_SUCCESS == lError)
						{
							//Log
							memset(szTemp, NULL, sizeof(szTemp));
							sprintf(szTemp, "%s\tSymantec Version Installed [%d]:\r\n",szDateTime, dwBexVersn);
							WriteToLog(szApplicationLog, szTemp);

							bBackupInstalled = true;
							if (dwBexVersn > 8)
							{
								dwBexVersn = 9;
							}

			//Read Symantec Data Dir Path
							memset(szBexRegDataPath, NULL, sizeof(szBexRegDataPath));
							lstrcpy(szBexRegDataPath, "SOFTWARE\\Symantec\\Backup Exec For Windows\\Backup Exec\\Engine\\Misc");
					
							lError = objReg.Close();
							lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegDataPath, KEY_READ);
							lError = objReg.QueryValue(szBexDataFilePath,"Data Path\0",&dwCount);

							if(ERROR_SUCCESS == lError)
							{
								//Log
								memset(szTemp, NULL, sizeof(szTemp));
								sprintf(szTemp, "%s\tSymantec DataFilePath [%s]:\r\n",szDateTime, szBexDataFilePath);
								WriteToLog(szApplicationLog, szTemp);
							}
							else
							{
								//Symantec data file path not found
								//Log
								lError = objReg.Close();

								memset(szTemp, NULL, sizeof(szTemp));
								sprintf(szTemp, "%s\tSymantec Data File Path not Found. \r\n",szDateTime);
								WriteToLog(szApplicationLog, szTemp);
								GeneratePID(szRegID,"SUCCESS\0", "Symantec Data File Path not Found.\0");			

								bBackupInstalled = false;

								//return 0;
//								goto SRV;
								break;
							}

							lError = objReg.Close();

						}
						else
						{
								//Log
								lError = objReg.Close();

								bBackupInstalled = false;

								memset(szTemp, NULL, sizeof(szTemp));
								sprintf(szTemp, "%s\tSymantec Version not Found. \r\n",szDateTime);
								WriteToLog(szApplicationLog, szTemp);
								GeneratePID(szRegID,"SUCCESS\0", "Symantec Version not Found.\0");			
								
								//return 0;
//								goto SRV;
								break;
						}
					}
*/
//symantec over
/////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
			else
			{
    		//Log
				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "%s\tSYMANTEC Path not found in registry. NOW LOOKING FOR VERITAS \r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);


// Checking for Symantec has failed
//			Now Checking for Veritas

//Read Veritas Install Version
				lError = objReg.Close();
				lstrcpy(szBexRegVerPath, "SOFTWARE\\VERITAS\\Backup Exec\\Install");
				lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegVerPath, KEY_READ);

				if(ERROR_SUCCESS == lError)
				{
					//Log
					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tSuccessfully Opened Registry for Veritas :\r\n",szDateTime);
					WriteToLog(szApplicationLog, szTemp);

					lError = objReg.QueryValue(dwBexVersn,"Major Version\0"); 
					
					if(ERROR_SUCCESS == lError)
					{
						//Log
						memset(szTemp, NULL, sizeof(szTemp));
						sprintf(szTemp, "%s\tVeritas Version Installed [%d]:\r\n",szDateTime, dwBexVersn);
						WriteToLog(szApplicationLog, szTemp);
						if (dwBexVersn > 8)
						{
							dwBexVersn = 9;
						}

						//Read Veritas Data Dir Path
						lstrcpy(szBexRegDataPath, "SOFTWARE\\VERITAS\\Backup Exec\\Engine\\Misc");
				
						lError = objReg.Close();
						lError = objReg.Open(HKEY_LOCAL_MACHINE, szBexRegDataPath, KEY_READ);
						lError = objReg.QueryValue(szBexDataFilePath,"Data Path\0",&dwCount);

						if(ERROR_SUCCESS == lError)
						{
							bBackupInstalled = true;

							//Log
							memset(szTemp, NULL, sizeof(szTemp));
							sprintf(szTemp, "%s\tVeritas DataFilePath [%s]:\r\n",szDateTime, szBexDataFilePath);
							WriteToLog(szApplicationLog, szTemp);
					
						}
						else
						{
							//Veritas data file path not found

							bBackupInstalled = false;

							//Log
							memset(szTemp, NULL, sizeof(szTemp));
							sprintf(szTemp, "%s\tVeritas Data File Path not Found. \r\n",szDateTime);
							WriteToLog(szApplicationLog, szTemp);
							GeneratePID(szRegID,"SUCCESS\0", "Veritas Data File Path not Found.\0");			
							
							//return 0;
///							goto SRV;
							break;
						}

						lError = objReg.Close();
					}
					else
					{
						objReg.Close();

						//Log
						memset(szTemp, NULL, sizeof(szTemp));
						sprintf(szTemp, "%s\tVeritas Version could not be read from registry :\r\n",szDateTime);
						WriteToLog(szApplicationLog, szTemp);
						GeneratePID(szRegID,"SUCCESS\0", "Veritas Version could not be read from registry.\0");			
						
						//return 0;
///						goto SRV;
						break;
					}
				}
				else
				{
					//Veritas path not found in registry
					lError = objReg.Close();

					bBackupInstalled = false;

					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tVeritas Path not Found in registry.\r\n",szDateTime);
					WriteToLog(szApplicationLog, szTemp);
					
					GeneratePID(szRegID,"SUCCESS\0", "Veritas Path not Found in registry.\0");
					
				}
			}

		}while (0);


//////////////////////////////////////////////////////////////////////////////////////////////////		

			memset(szTemp, NULL, sizeof(szTemp));
			sprintf(szTemp, "%s\tBefore Service Checking. [%d]\r\n",szDateTime, bBackupInstalled);
			WriteToLog(szApplicationLog, szTemp);
			

			if (false == bBackupInstalled)
			{
				//Checking Service Path

				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "%s\tChecking Service. \r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);

				char 
					szPath[256] = {0};
				memset(szPath, NULL, sizeof(szPath));

				ServiceDetails(szPath);

				if (0 < lstrlen(szPath) )
				{

					//Service Path
					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tService Path [%s].\r\n",szDateTime, szPath);
					WriteToLog(szApplicationLog, szTemp);
					
					ptr = NULL;
					ptr1 = NULL;
					ptr1= szPath;
					ptr1++;
					ptr = strrchr(szPath, '\\');
					memset(ptr+1, NULL, lstrlen(ptr+1));
					lstrcat(ptr+1, "Data\0");

					dwBexVersn = 9; 
					memset(szBexDataFilePath, NULL, sizeof(szBexDataFilePath));
					lstrcpy(szBexDataFilePath, ptr1);

					dwBexVersn = 9;
					bBackupInstalled    = true;
				}
				else
				{
					memset(szTemp, NULL, sizeof(szTemp));
					sprintf(szTemp, "%s\tNo Symantec Software detected. Quitting !!!.\r\n",szDateTime);
					WriteToLog(szApplicationLog, szTemp);
				}
			}

//////////////////////////////////////////////////////////////////////////////////////////////////		


			if (false == bBackupInstalled)
			{
				GeneratePID(szRegID,"SUCCESS\0", "No veritas found.\0");

				return 0;
				//GeneratePID(oThreadData->szRegId,"FAILED\0","Opening Last Parsed ini File Failed.\0");
			}
			else
			{
				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "Veritas Backup %d ", dwBexVersn);

				GeneratePID(szRegID,"SUCCESS\0", szTemp);
			}

			if (!(((8==dwBexVersn) || (9==dwBexVersn)) && (0 < lstrlen(szBexDataFilePath)))) 
			{
				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "%s\tBex Version [%d]. Path [%s]. Quitting !!!.\r\n",szDateTime, szBexDataFilePath);
				WriteToLog(szApplicationLog, szTemp);

				return 0;
			}


		
	//Make the Bex Data Directory Shareable

//Get Host Name

		char 
			szHostName[100] = {0};
		WSADATA 
			wsData;
		
		WSAStartup(MAKEWORD( 2, 2 ),&wsData);
		
		ZeroMemory(szHostName, sizeof(szHostName));
		gethostname(szHostName,sizeof(szHostName));
		
		WSACleanup();

//Check For share
//		char 
//			RemoteTerminalName[100] = {0},
//			szPathName[_MAX_PATH] = {0};

//		memset(szPathName, NULL, _MAX_PATH);

//		lstrcpy(szPathName, szBexDataFilePath);

		char * szPathC = NULL;
		wchar_t *str = NULL;
 
		char* szSortVal = NULL;
		szSortVal = new char[_MAX_PATH];
		memset(szSortVal, NULL, _MAX_PATH);
 
		PSHARE_INFO_502 
					bufPtr;
		SHARE_INFO_502 
					info;
		NET_API_STATUS 
					res = 0;
 
		memset(&info, NULL, sizeof(info));

		//Share Name
		 //sprintf(szSortVal, "%c$", szPathName[0]);
		sprintf(szSortVal, "zBEX%dX", dwBexVersn);
 

		//Log
		memset(szDateTime, NULL, sizeof(szDateTime));
		memset(szTemp, NULL, sizeof(szTemp));
		GetDateTime(szDate,szDateTime);
		sprintf(szTemp, "%s\tFinding Share Name [%s]:\r\n",szDateTime, szSortVal);
		WriteToLog(szApplicationLog, szTemp);
		
//		memset(RemoteTerminalName, NULL, 100);
//		sprintf(RemoteTerminalName,"\\\\%s", szHostName);
//		wchar_t *term = new wchar_t[(strlen(RemoteTerminalName)*2)+2];
//		memset(term, NULL, strlen(RemoteTerminalName)*2 + 2);
//		swprintf(term, L"%S",RemoteTerminalName);
 
		wchar_t *name = new wchar_t[(strlen(szSortVal)*2)+2];
		memset(name, NULL, strlen(szSortVal)*2 + 2);
		swprintf(name,L"%S",szSortVal);
 
		 //check if share share exits 
 
		  if((res = NetShareGetInfo(NULL /*(LPTSTR)term*/, //local server
									(LPWSTR)name,   //share name
									502,
									(LPBYTE *) &bufPtr)) != ERROR_SUCCESS)
		  {

			  // Share does not exists

			//Log
			memset(szDateTime, NULL, sizeof(szDateTime));
			memset(szTemp, NULL, sizeof(szTemp));
			GetDateTime(szDate,szDateTime);
			sprintf(szTemp, "%s\tShare Name [%s] not found Return Value [%d]:\r\n", szDateTime, szSortVal, res);
			WriteToLog(szApplicationLog, szTemp);
				  
			  
    		  szPathC = new char[_MAX_PATH];
			  memset(szPathC, NULL, _MAX_PATH);

			   sprintf(szPathC, "%s", szBexDataFilePath);
   
   
			   info.shi502_netname = (LPWSTR)name; //ToWideChar(szSortVal);
			   info.shi502_type  = STYPE_SPECIAL;
			   info.shi502_remark = NULL;//ToWideChar ("Hello");
			   info.shi502_permissions  = ACCESS_ALL;
			   info.shi502_max_uses = -1;
			   info.shi502_path  = (LPWSTR)ToWideChar(szPathC);
			   info.shi502_passwd = NULL;
   
			   res = NetShareAdd ( NULL,/*(LPTSTR)term,*/ // local
									502,         
									(LPBYTE)&info,    
									NULL);        
			   if (0 == res)
			   {

					//Log
					memset(szDateTime, NULL, sizeof(szDateTime));
					memset(szTemp, NULL, sizeof(szTemp));
					GetDateTime(szDate,szDateTime);
					sprintf(szTemp, "%s\tSuccessfully Created  Share Name [%s]:\r\n",szDateTime, szSortVal);
					WriteToLog(szApplicationLog, szTemp);

					GeneratePID(szRegID,"SUCCESS\0", "Share created.\0");

			   }
   			   else
			   {
					//Log
					memset(szDateTime, NULL, sizeof(szDateTime));
					memset(szTemp, NULL, sizeof(szTemp));
					GetDateTime(szDate,szDateTime);
					sprintf(szTemp, "%s\tFailed Creating Share Name [%s]. Return Value [%d]:\r\n",szDateTime, szSortVal, res);
					WriteToLog(szApplicationLog, szTemp);

					GeneratePID(szRegID,"FAILED\0", "Unable to create share.\0");

			   }

		  }
		  else
		  {
			//Share Exists	

				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tShare Name [%s] already Exists. Return Value [%d] :\r\n",szDateTime, szSortVal, res);
				WriteToLog(szApplicationLog, szTemp);

			//Check that data path are same
				memset(szTemp, NULL, sizeof(szTemp));
				sprintf(szTemp, "%S",bufPtr->shi502_path);
			

				if (stricmp(szTemp, szBexDataFilePath) )
				{
					//Data path vary
					memset(szDateTime, NULL, sizeof(szDateTime));
					memset(szTemp, NULL, sizeof(szTemp));
					GetDateTime(szDate,szDateTime);
					sprintf(szTemp, "%s\tShare Name is same but data path varies. Deleting Previous share and creating new share [%s] with path [%s]:\r\n",szDateTime, szSortVal, szBexDataFilePath);
					WriteToLog(szApplicationLog, szTemp);

					res = NetShareDel(NULL, (LPWSTR)name, NULL);

					if (0 == res)
					{
						  szPathC = new char[_MAX_PATH];
						  memset(szPathC, NULL, _MAX_PATH);
   
						  sprintf(szPathC, "%s", szBexDataFilePath);
   
   
						   info.shi502_netname = (LPWSTR)name; //ToWideChar(szSortVal);
						   info.shi502_type  = STYPE_SPECIAL;
						   info.shi502_remark = NULL;//ToWideChar ("Hello");
						   info.shi502_permissions  = ACCESS_ALL;
						   info.shi502_max_uses = -1;
						   info.shi502_path  = (LPWSTR)ToWideChar(szPathC);
						   info.shi502_passwd = NULL;
   
						   res = NetShareAdd ( NULL,
												502,         
												(LPBYTE)&info,    
												NULL);        
					}

				    if (0 == res)
					{
						//Log
						memset(szDateTime, NULL, sizeof(szDateTime));
						memset(szTemp, NULL, sizeof(szTemp));
						GetDateTime(szDate,szDateTime);
						sprintf(szTemp, "%s\tSuccessfully Created  Share Name [%s]:\r\n",szDateTime, szSortVal);
						WriteToLog(szApplicationLog, szTemp);

						GeneratePID(szRegID,"SUCCESS\0", "Share created.\0");	
					}
   				    else
					{
						//Log
						memset(szDateTime, NULL, sizeof(szDateTime));
						memset(szTemp, NULL, sizeof(szTemp));
						GetDateTime(szDate,szDateTime);
						sprintf(szTemp, "%s\tFailed Creating Share Name [%s]. Return Value [%d]:\r\n",szDateTime, szSortVal, res);
						WriteToLog(szApplicationLog, szTemp);

						GeneratePID(szRegID,"FAILED\0", "Unable to create share.\0");
					}
				}
			}

			res = NetApiBufferFree((LPVOID)bufPtr);

			//Checking For Last Parsed ini
			//If not Present create it with Last Parsed time as SAAZOD Installed date  

			//Log
			memset(szDateTime, NULL, sizeof(szDateTime));
			memset(szTemp, NULL, sizeof(szTemp));
			GetDateTime(szDate,szDateTime);
			sprintf(szTemp, "%s\tChecking for Last Parsed Ini File :\r\n", szDateTime);
			WriteToLog(szApplicationLog, szTemp);


			char 
				szSAAZODRegPath[100] = {0},
				szSAAZODInstallDate[25] = {0},
				szSAAZODInstallPath[_MAX_PATH] = {0},
				szInstallDate[50]= {0};



			DWORD 
				dwCount;

			memset(szSAAZODRegPath, 0, 100);
			lstrcpy(szSAAZODRegPath, "SOFTWARE\\SAAZOD");

			memset(szSAAZODInstallDate, 0, 25);
			memset(szSAAZODInstallPath, 0, _MAX_PATH);
			memset(szInstallDate, 0, 50);

			lError = objReg.Open(HKEY_LOCAL_MACHINE, szSAAZODRegPath, KEY_READ);

			dwCount = 25;
			lError = objReg.QueryValue(szSAAZODInstallDate,"InstallDate\0",&dwCount);
			if (lError)
			{
				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tError Opening SAAZOD Install Date in registry: \r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);

				objReg.Close();

				return 1;
			}

			lError = objReg.Close();
			
			lError = objReg.Open(HKEY_LOCAL_MACHINE, szSAAZODRegPath, KEY_READ);
			if (lError)
			{
				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tError Opening SAAZOD Install Date in registry:\r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);

				objReg.Close();
				return 1;
			}
			dwCount = _MAX_PATH;
			lError = objReg.QueryValue(szSAAZODInstallPath, "InstallationPath\0",&dwCount);
			if (lError)
			{
				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tError Opening SAAZOD Install Path in registry: \r\n",szDateTime);
				WriteToLog(szApplicationLog, szTemp);

				objReg.Close();

				return 1;
			}

			lError = objReg.Close();

			//Log
			memset(szDateTime, NULL, sizeof(szDateTime));
			memset(szTemp, NULL, sizeof(szTemp));
			GetDateTime(szDate,szDateTime);
			sprintf(szTemp, "%s\tSAAZOD Install Path [%s]  SAAZOD Install Date [%s]: \r\n",szDateTime, szSAAZODInstallPath, szSAAZODInstallDate);
			WriteToLog(szApplicationLog, szTemp);

			lstrcat(szSAAZODInstallDate, "/");
			char **arrValues = NULL;
			
			SplitString(szSAAZODInstallDate, "/", arrValues);
			
			sprintf(szInstallDate,"%s-%s-%s 00:00:00", arrValues[2], arrValues[0], arrValues[1]);
			
			HANDLE	
				hIniCheck = NULL; 
			char 
				szLastParseIni[_MAX_PATH] = {0};

			memset(szLastParseIni, NULL, _MAX_PATH);
			
			sprintf(szLastParseIni, "%s\\Configuration\\Bex%dx\\%s_LastParsed.ini", szSAAZODInstallPath, dwBexVersn, szHostName);
		
			hIniCheck = CreateFile(szLastParseIni, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

			if(hIniCheck  == INVALID_HANDLE_VALUE)
			{
				//	memset(szTemp, 0, sizeof(szTemp));
				//	lstrcpy(szTemp, szLastParseIni);
				//	memset(szLastParseIni, 0, sizeof(szLastParseIni));
				//	sprintf(szLastParseIni, "%s\\%s_LastParsed.ini", szTemp, szHostName);
				//	Create Bex Directory

				char 
					szConfigDirectory[_MAX_PATH] = {0};

				memset(szConfigDirectory, NULL, _MAX_PATH);
				
				sprintf(szConfigDirectory, "%s\\Configuration\\Bex%dx\\", szSAAZODInstallPath, dwBexVersn);

				CreateDirectoriesRecursively(szConfigDirectory);

				DWORD
					dwBytesWritten = 0;
				hIniCheck = CreateFile(szLastParseIni, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
				WriteFile(hIniCheck, szInstallDate, strlen(szInstallDate), &dwBytesWritten, NULL);	

				CloseHandle(hIniCheck);

				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tCreated File [%s] with data [%s]: \r\n",szDateTime, szLastParseIni, szInstallDate);
				WriteToLog(szApplicationLog, szTemp);
			}
			else
			{
				//Log
				memset(szDateTime, NULL, sizeof(szDateTime));
				memset(szTemp, NULL, sizeof(szTemp));
				GetDateTime(szDate,szDateTime);
				sprintf(szTemp, "%s\tFile [%s] found : \r\n",szDateTime, szLastParseIni);
				WriteToLog(szApplicationLog, szTemp);
				
				CloseHandle(hIniCheck);
				hIniCheck = NULL;
			}
	}
	catch(...)
	{
		//Log
		memset(szDateTime, NULL, sizeof(szDateTime));
		memset(szTemp, NULL, sizeof(szTemp));
		GetDateTime(szDate,szDateTime);
		sprintf(szTemp, "%s\tException occured in main : \r\n",szDateTime);
		WriteToLog(szApplicationLog, szTemp);
	}

	return 0;
}