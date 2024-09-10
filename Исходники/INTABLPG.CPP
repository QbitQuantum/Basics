void CInputTablePage::OnChangeDatabase() 
{
	// TODO: Add your control notification handler code here
	try
	{
		ASSERT (NULL != m_pParams);
		if ((MdbTable == m_pParams -> m_tImportType) || 
			(MdbTableOld == m_pParams -> m_tImportType))
			m_bOpenTyp = TRUE;
		else
			m_bOpenTyp = FALSE;

	//	Datei-Auswahl-Diolog öffnen
		CString strExt, strFilter, strCaption;
		VERIFY (strExt.LoadString (m_bOpenTyp ? IDS_DATABASE_EXTENSION : IDS_FOXPRO_EXTENSION));
		VERIFY (strFilter.LoadString (m_bOpenTyp ? IDS_MDB_FILTER : IDS_FOXPRO_FILTER));
		VERIFY (strCaption.LoadString (IDS_SELECT_DB_CAPTION));

		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;		// voreingest.
		CFileDialog Dlg (TRUE, strExt, NULL, dwFlags, strFilter, this);

	//	Datenpfad ermitteln
		CString strDataPath (((CGakApp *) AfxGetApp ()) -> DatabaseName ());
		CString strDrive, strDir, strNewPath;
		char *pDrive = strDrive.GetBuffer (_MAX_DRIVE); 
		char *pDir = strDir.GetBuffer (_MAX_DIR);
		char *pNewPath = strNewPath.GetBuffer (_MAX_PATH);
		_splitpath (strDataPath, pDrive, pDir, NULL, NULL);
		_makepath (pNewPath, pDrive, pDir, NULL, NULL);

		Dlg.m_ofn.lpstrInitialDir = pNewPath;	// Pfad setzen
		Dlg.m_ofn.lpstrTitle = strCaption;
		if (IDOK != Dlg.DoModal ())
			AfxThrowUserException ();			// alles bleibt beim alten

	//	alten Set ggf. schließen
		if (m_pParams -> m_SourceSet.IsOpen ())
			m_pParams -> m_SourceSet.Close ();
		if (m_pParams -> m_SourceDatabase.IsOpen ())
			m_pParams -> m_SourceDatabase.Close ();

	//	alten Infos löschen
		m_lbTables.ResetContent ();
		m_edDatabase.SetWindowText ("");

	//	Database öffnen
		if (m_bOpenTyp)	// MDB-Datei
		{
			m_pParams -> m_SourceDatabase.Open (Dlg.GetPathName ());
												// FALSE,	/* nicht exclusiv */
												// TRUE);	/* read only */
			SetTableInfo (m_pParams -> m_tImportType, m_pParams -> m_tTableType);
		}
		else		// FOXPRO
		{
			CString strConnect;
			VERIFY (strConnect.LoadString (IDS_FOXPRO_CONNECT));
			_splitpath (Dlg.GetPathName (), pDrive, pDir, NULL, NULL);
			_makepath (pNewPath, pDrive, pDir, NULL, NULL);
			m_pParams -> m_SourceDatabase.Open (pNewPath, 
												FALSE,	/* nicht exclusiv */
												TRUE,	/* read only */
												_T(strConnect));	
			SetTableInfo (m_pParams -> m_tImportType, m_pParams -> m_tTableType);
		}

	//	Tabellen ausgeben
		int iCnt = m_pParams -> m_SourceDatabase.GetTableDefCount();
		CDaoTableDefInfo Info;
		for (short iIndex = 0; iIndex < iCnt; iIndex++)
		{
		//	primary info
			m_pParams -> m_SourceDatabase.GetTableDefInfo (iIndex, Info);	
			if (Info.m_lAttributes & dbSystemObject)	// keine
				continue;								// Systemtabellen

			if (m_lbTables.AddString (Info.m_strName) < 0)
				AfxThrowMemoryException ();
		}

	//	bei FOXPRO gleich Set öffnen
		if (!m_bOpenTyp)
		{
			m_pParams -> m_SourceSet.m_pDatabase = &m_pParams -> m_SourceDatabase;
			CString strSQL, strFileName;
			char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
			_splitpath (Dlg.GetFileName (), NULL, NULL, pFileName, NULL);			
			AfxFormatString1 (strSQL, IDS_SELECT_ALL, pFileName);
			m_pParams -> m_SourceSet.Open (dbOpenSnapshot, strSQL, dbReadOnly);
			m_pParams -> m_strInputTableName = pFileName;
			m_lbTables.SelectString (-1, pFileName);
		}
		
	//	Name der Datenbank ausgeben
		m_edDatabase.SetWindowText (m_bOpenTyp ? Dlg.GetPathName () : pNewPath);
	}
	catch (CUserException *ue)
	{
		ue -> Delete ();		// hier Abbruch
	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS (CDaoException)))
			:: DisplayDaoException ((CDaoException *) e);
		else
			e -> ReportError ();
		e -> Delete ();

		if (m_pParams -> m_SourceDatabase.IsOpen ())
			m_pParams -> m_SourceDatabase.Close ();
	}

	SetWizardButton ();	
}