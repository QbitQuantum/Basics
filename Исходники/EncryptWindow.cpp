void EncryptWindow::DoBlankSetup ()
{
	SingleFileInfo *pinfo;

	int a = 0;
	char szDestpath[SIZE_STRING];

	char szFileonly[SIZE_STRING];
	char szPathonly[SIZE_STRING];
	char szTemp[SIZE_STRING];

	char szTempdir[SIZE_STRING];
	ZeroMemory (szTempdir, SIZE_STRING);
	//strcpy_s (szTempdir, SIZE_STRING, "C:\\Temp\\TempEnc");

	GetEnvironmentVariable ("Temp", szTempdir, SIZE_STRING);
	strcat_s (szTempdir, SIZE_STRING, "\\CedeCrypt.tmp");
	

	for (a=0;a<m_dlFileinfolist.GetNumItems ();a++) {

		pinfo = (SingleFileInfo *) m_dlFileinfolist.GetItem (a);

		if (pinfo->bIsDir == true) {
			
			ZeroMemory (szDestpath, SIZE_STRING);
			strcpy_s (szDestpath, SIZE_STRING, szTempdir);
			strcat_s (szDestpath, SIZE_STRING, "\\");

			ZeroMemory (szFileonly, SIZE_STRING);
			ZeroMemory (szPathonly, SIZE_STRING);
			
			GetPathOnly (pinfo->szRootdir, szPathonly, szFileonly, "\\");

			ZeroMemory (szTemp, SIZE_STRING);
			StripStartPath (pinfo->szRootdir, pinfo->szFilepath, szTemp);

			strcat_s (szDestpath, SIZE_STRING, szFileonly);
			strcat_s (szDestpath, SIZE_STRING, szTemp);
			
			//m_pdiag->OutputText ("Encrypt Source: ", pinfo->szFilepath);
			m_pdiag->OutputText ("BlankFile Dest: ", szDestpath);

			m_enc.SetupBlankFile (szDestpath);
		} else {

			ZeroMemory (szDestpath, SIZE_STRING);
			strcpy_s (szDestpath, SIZE_STRING, szTempdir);
			strcat_s (szDestpath, SIZE_STRING, "\\");

			ZeroMemory (szFileonly, SIZE_STRING);
			ZeroMemory (szPathonly, SIZE_STRING);

			GetPathOnly (pinfo->szFilepath, szPathonly, szFileonly, "\\");
			
			strcat_s (szDestpath, SIZE_STRING, szFileonly);

			m_pdiag->OutputText ("BlankFile Dest: ", szDestpath);

			m_enc.SetupBlankFile (szDestpath);
		}
	}
}