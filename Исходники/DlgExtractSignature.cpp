BOOL CDlgExtractSignature::OnInitDialog() 
{
#ifndef _UNSTABLE
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	LOGFONT LogFont;
	char DefaultFontName[32];
	LONG defaultFontWeight;
	CFont *defaultFont = m_DefEditCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(DefaultFontName, LogFont.lfFaceName, 32); // Default Wert sichern
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_TextMsgCtrl.SetFont(&Font);
	m_TextSigCtrl.SetFont(&Font);
	m_TextSignerCtrl.SetFont(&Font);
	m_TextKeyCtrl.SetFont(&Font);
	m_TextAlgCtrl.SetFont(&Font);

	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zurückstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen
	Font2.CreateFontIndirect( &LogFont ); // Font2 initialisieren
    m_MessageCtrl.SetFont(&Font2);
	m_SignatureCtrl.SetFont(&Font2);
	//strncpy(LogFont.lfFaceName, DefaultFontStyle, 32);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSig = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextMsg = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_ORIGINATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSigner = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_USED_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextKey = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_METHOD,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextAlg = (CString) pc_str;
	UpdateData(FALSE);

	int err;

	bool messagefromfile=false; // zeigt an, ob die signierte Nachricht aus einer Datei
	// gelesen werden musste
	CString filename;
				
	CString SigAlg="";
	CString HashAlg="";
	CString UserKeyId="";
	int SignLength; // (Aus dem Ausgabefenster eingelesene) Länge der Signatur in Bits

	CKeyFile FileHandling;

	SignatureType = GetSignData(inFileName,messagefromfile,filename,&message,SigAlg,HashAlg,UserKeyId,&SignLength,&Signatur,c,d);
	// Folgende Speicherbereiche sind von GetSignData() alloziert worden und
	// müssen später wieder freigegeben werden:
	// message.octets (falls != NULL) 
	// Signatur.signature.bits (falls != NULL)

	if ( (SignatureType > 0) && (SignatureType != EC_SIGN) &&\
		(SignatureType != RSA_OR_DSA_SIGN) && (SignatureType != UNKNOWN_SIGN) )
	{
		// Fehler beim auslesen der Daten (Nicht genügend Speicher vorhanden)
		Message(IDS_STRING_ERR_MEMORY_SIGNATURE_VERIFICATION, MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		EndDialog(-1);
		return TRUE;
	}
	else if ((SignatureType != EC_SIGN) && (SignatureType != RSA_OR_DSA_SIGN) &&\
		(SignatureType != UNKNOWN_SIGN))
	{
		Message(IDS_STRING_ASYMKEY_COULD_NOT_EXTRACT_SIGNATURE,MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		EndDialog(-2);
		return TRUE;
	}

	if (messagefromfile == true)
	{
		// Die signierte Nachricht ist zu gross und passt nicht komplett
		// in ein CEdit Feld. Es wird lediglich ein erster Teil der Nachricht dargestellt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE_FIRST_PART,pc_str,STR_LAENGE_STRING_TABLE);
		m_TextMsg = (CString) pc_str;
	}

	// Überprüfe, ob angegebener Schlüsselbezeichner tatsächlich existiert
	bool keyExists = FileHandling.FilenameExisting(UserKeyId);

	char *name=NULL;
	char *firstname=NULL;
	char *keyType=NULL;
	char *keyInfo=NULL;
	char *creattime=NULL;
	char *ctstr=NULL;

	CString kInfo;

	if (keyExists == true)
	{
		err = FileHandling.ExtractData(UserKeyId,&ctstr,&creattime,&name,&firstname,&keyType,&keyInfo);
		if (ctstr) free(ctstr); // wird hier nicht benötigt
		if (keyInfo==NULL)
			kInfo="";
		else
			kInfo = ((CString)" (")+((CString)keyInfo)+((CString)") ");

		// Infos über den Signaturersteller
		m_InfoAboutSigner = (CString) ((CString)firstname)+((CString)" ")+((CString)name); // Signatur erzeugt von:

		// Infos über Schlüssel
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_DATE,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)keyType)+kInfo,((CString)creattime));
		m_KeyInfo = (CString) pc_str; // Benutzter Schlüssel:
	}
	else
	{
		// Schlüsselbezeichner "UserKeyId" existiert nicht
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_UNKNOWN_KEY_IDENTIFIER,pc_str1,STR_LAENGE_STRING_TABLE);
		// pc_str1 = "Übermittelter Schlüsselbezeichner existiert nicht!"
		m_InfoAboutSigner = ((CString)pc_str1);
		// Signaturerzeuger unbekannt
	}

	// Überprüfe ob angegebener Signatur-/Hashalgorithmus bekannt ist
	if ( (SigAlg!="RSA") && (SigAlg!="DSA") && (SigAlg!="ECSP-NR") && (SigAlg!="ECSP-DSA") )
	{
		// unbekannter Signaturalgorithmus angegeben
		LoadString(AfxGetInstanceHandle(),IDS_STRING_UNKNOWN,pc_str,STR_LAENGE_STRING_TABLE);
		// pc_str = "unbekannt !"
		SigAlg = SigAlg+((CString)" (")+((CString)pc_str)+((CString)")");
	}
	if ( (HashAlg!="MD2") && (HashAlg!="MD5") && (HashAlg!="SHA") && (HashAlg!="SHA-1") &&\
		(HashAlg!="RIPEMD-160") )
	{
		// unbekannter Hashalgorithmus angegeben
		LoadString(AfxGetInstanceHandle(),IDS_STRING_UNKNOWN,pc_str,STR_LAENGE_STRING_TABLE);
		// pc_str = "unbekannt !"
		HashAlg = HashAlg+((CString)" (")+((CString)pc_str)+((CString)")");
	}

	// Benutzter Signaturalgorithmus
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_HASH_FUNCTION,pc_str1,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, pc_str1, SigAlg, HashAlg);
	m_SigHashAlg = (CString) pc_str;

	UpdateData(FALSE);

	int srcSize;
	int destSize;

	// Signierte Nachricht ausgeben
	if (message.noctets != 0)
	{
		// Nachricht ist kein leerer String
		srcSize = message.noctets;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *msgdata = (char *) malloc(destSize+1);

		err = HexDumpMem(msgdata, destSize, (unsigned char *) message.octets, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return TRUE;
		}
		CString mData(msgdata);
		m_Message = mData;
		free(msgdata);
	}
	// Länge der signierten Nachricht
	char buffer[30];
	_itoa( message.noctets, buffer, 10 );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_MESSAGE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, pc_str1,((CString)buffer));
	m_MessageLength = (CString) pc_str;
	UpdateData(FALSE);

	if (SignatureType == EC_SIGN)
	{
		//
		CheckRadioButton (IDC_RADIO1, IDC_RADIO4, IDC_RADIO3); UpdateData(TRUE);
		base = 10; // Signatur als Dezimalzahlen darstellen

		int signlength = theApp.SecudeLib.lngtouse(c)+theApp.SecudeLib.lngtouse(d)+2;// Bit-Länge der Signatur

		char buffer[30];
		_itoa( signlength, buffer, 10 );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)buffer));
		m_SignatureLength = (CString) pc_str;
		UpdateData(FALSE);

		UpdateSigEditBox();
	}
	else if (SignatureType == RSA_OR_DSA_SIGN)
	{
		//
		CheckRadioButton (IDC_RADIO1, IDC_RADIO4, IDC_RADIO1); UpdateData(TRUE);
		base = -1; // Signatur als Octets darstellen

		srcSize = (Signatur.signature.nbits+7)/8;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *sigdata = (char *) malloc(destSize+1);

		err = HexDumpMem(sigdata, destSize, (unsigned char *) Signatur.signature.bits, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return TRUE;
		}
		m_Signature = (CString) sigdata; UpdateData(FALSE);
		free(sigdata);
		
		char buffer[30];
		_itoa( Signatur.signature.nbits, buffer, 10 );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)buffer));
		m_SignatureLength = (CString) pc_str;
		UpdateData(FALSE);
	}
	else // (SignatureType == UNKNOWN_SIGN)
	{
		// unbekanntes Signaturverfahren angegeben
		m_RadioOctets.EnableWindow(FALSE);
		m_RadioOktal.EnableWindow(FALSE);
		m_RadioDezimal.EnableWindow(FALSE);
		m_RadioHexadezimal.EnableWindow(FALSE);
	}
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}