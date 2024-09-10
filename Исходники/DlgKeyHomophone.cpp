BOOL CDlgKeyHomophone::OnInitDialog() 
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	m_ctrlEncodeUmlauts.SetCheck(FALSE);
	m_AlphabetBackup = theApp.TextOptions.getAlphabet();

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
	CString HParam;
	if ( PasteKey( pc_str, HParam ) )
	{
		UpdateData(true);
		int d = strlen("PARAMETER: ");
		m_BaseHomophones          = (int)(HParam[d] - '0');
		m_ctrlEncryptFormatCharacters.SetCheck((int)(HParam[d+2] - '0'));
		m_ctrlEncodeUmlauts.SetCheck((int)(HParam[d+4] - '0'));
		m_InputType				  = (int)(HParam[d+6] - '0');
		m_NoOfHomophones          = (int)atoi( HParam.GetBuffer(0) +(d+8) );
		UpdateData(false);



		// TEXT 
		int ReInitFlag = 0;
		if ( !m_InputType )
		{
			int l_alphabetLength = theApp.TextOptions.getAlphabet().GetLength();
			if (m_NoOfHomophones < l_alphabetLength) {
				UpdateData();
				m_NoOfHomophones = l_alphabetLength;
				UpdateData(FALSE);
			}


			if ( m_ctrlEncryptFormatCharacters.GetCheck() )
			{	
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\n", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\n"); 
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\t", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\t");
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\r", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\r");			
				ReInitFlag = 1;
			}	
			else
			{
				int ndx;
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\n", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\t", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\r", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
			}
		}

		if ( m_NoOfHomophones != HB.GetKeySize() )
		{
			HB.Resize( m_NoOfHomophones );
			UpdateData();
			m_Bitlength = HB.LogKeySize( 2 );
			UpdateData(FALSE);
			ReInitFlag = 1;
		}
		if ( ReInitFlag )
			HB.Init_Data();
	}

	m_listview.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,"Ord",LVCFMT_LEFT,colWidth-48,1);							// Ordnung Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth-24,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_QUANTITY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(4,pc_str,LVCFMT_LEFT,colWidth-8,3);							// Verschlüsselung
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LIST_OF_HOMOPHONES,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(5,pc_str,LVCFMT_LEFT,colWidth+2000,4);							// Verschlüsselung
	Init_ListBox();

	LOGFONT LogFont;
	CFont *defaultFont=m_listview.GetFont();				// this->GetFont() sollte auch funktionieren
	defaultFont->GetLogFont(&LogFont);						// Default Systemschrift ermitteln
	strncpy(LogFont.lfFaceName,"Courier",32);				// Auf Courier umstellen
	m_Font.CreateFontIndirect(&LogFont);					// Font initialisieren
	m_listview.SetFont(&m_Font);

	if ( DeactivateDecryptionButton )
		m_ButtonDecryption.EnableWindow(FALSE);

	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_Paste.SetToolTipText(&buttonPasteText);

	if ( m_InputType == HOM_ENC_TXT )
	{
		m_ctrlEncodeUmlauts.EnableWindow();
		m_ctrlEncryptFormatCharacters.EnableWindow();
		m_ctrlTextOptions.EnableWindow();
	}
	else
	{
		m_ctrlTextOptions.EnableWindow(FALSE);
		m_ctrlEncodeUmlauts.EnableWindow(FALSE);
		m_ctrlEncryptFormatCharacters.EnableWindow(FALSE);
	}

	CString SKeyID;
	SKeyID.LoadStringA(IDS_CRYPT_HOMOPHONE);
	if ( IsKeyEmpty( SKeyID ) )
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}
	return(TRUE);
}