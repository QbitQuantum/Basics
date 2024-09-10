int CSuggestor::Suggest(const CFSWString &szWord, bool bStartSentence){
	m_TimeStart=CFSTime::Now();
	m_Items.Cleanup();

	m_Cap.SetCap(szWord);
	if (bStartSentence && m_Cap.GetCapMode()==CFSStrCap<CFSWString>::CAP_LOWER) {
		m_Cap.SetCapMode(CFSStrCap<CFSWString>::CAP_INITIAL);
	}

	CFSWString szWordHigh=szWord.ToUpper();
	INTPTR ipWordLength=szWordHigh.GetLength();
	CFSWString szTemp;
	INTPTR i, j;
	long lLevel=100;
	SetLevel(lLevel);

	// Case problems & change list
	i=SpellWord(szWordHigh, szTemp, &lLevel);
	if ((i==SPL_NOERROR || i==SPL_CHANGEONCE) && !szTemp.IsEmpty()){
		SetLevel(GetLevelGroup(lLevel));
		m_Items.AddItem(CSuggestorItem(szTemp, lLevel));
	}
	else SetLevel(5);
	
	// Abbrevations
	// !!! Unimplemented

	// Quotes
/*	if (ipWordLength>=2 && 
		(szAllQuot.Find(szWordHigh[0])>=0 || szAllQuot.Find(szWordHigh[ipWordLength-1])>=0))
	{
		szTemp=szWordHigh;
		int iPos;
		if (szAllQuot.Find(szTemp[0])>=0){
			if (szQuotLeft.Find(szTemp[0])>=0) { }
			else if ((iPos=szQuotRight.Find(szTemp[0]))>=0) { szTemp[0]=szQuotLeft[iPos]; }
			else if (szDQuotLeft.Find(szTemp[0])>=0) { }
			else if ((iPos=szDQuotRight.Find(szTemp[0]))>=0) { szTemp[0]=szDQuotLeft[iPos]; }

			if (szAllQuot.Find(szTemp[ipWordLength-1])>=0) { szTemp[ipWordLength-1]=(szQuotRight+szDQuotRight)[(szQuotLeft+szDQuotLeft).Find(szTemp[0])];
		}
		else{
			if (szQuotRight.Find(szTemp[ipWordLength-1])>=0) { }
			else if ((iPos=szQuotLeft.Find(szTemp[ipWordLength-1]))>=0) { szTemp[ipWordLength-1]=szQuotRight[iPos]; }
			else if (szDQuotRight.Find(szTemp[ipWordLength-1])>=0) { }
			else if ((iPos=szDQuotLeft.Find(szTemp[ipWordLength-1]))>=0) { szTemp[ipWordLength-1]=szDQuotRight[iPos]; }
		}
		CheckAndAdd(szTemp);
	}*/

	// Add space
	for (i=1; i<ipWordLength-1; i++){
		static CFSWString szPunktuation=FSWSTR(".:,;!?");
		if (szPunktuation.Find(szWord[i])>=0){
			long lLevel1, lLevel2;
			CFSWString szTemp1, szTemp2;
			if (SpellWord(szWord.Left(i+1), szTemp1, &lLevel1)==SPL_NOERROR &&
				SpellWord(szWord.Mid(i+1), szTemp2, &lLevel2)==SPL_NOERROR)
			{
				m_Items.AddItem(CSuggestorItem(szWord.Left(i+1)+L' '+szWord.Mid(i+1), FSMAX(lLevel1, lLevel2)));
			}
		}
	}

	// Delete following blocks: le[nnu][nnu]jaam
	for (i=2; i<=3; i++){
		for (j=0; j<ipWordLength-i-i; j++){
			if (memcmp((const FSWCHAR *)szWordHigh+j, (const FSWCHAR *)szWordHigh+j+i, i*sizeof(FSWCHAR))==0){
				szTemp=szWordHigh.Left(j)+szWordHigh.Mid(j+i);
				CheckAndAdd(szTemp);
			}
		}
	}

	// Change following letters: abb -> aab & aab -> abb
	for (i=1; i<ipWordLength-1; i++){
		if (szWordHigh[i]==szWordHigh[i+1]){
			szTemp=szWordHigh;
			szTemp[i]=szTemp[i-1];
			if (FSIsLetterEst(szTemp[i])) CheckAndAdd(szTemp);
		}
		else if (szWordHigh[i]==szWordHigh[i-1]){
			szTemp=szWordHigh;
			szTemp[i]=szTemp[i+1];
			if (FSIsLetterEst(szTemp[i])) CheckAndAdd(szTemp);
		}
	}

	// Exchange letters: van[na]ema -> van[an]ema
	szTemp=szWordHigh;
	for (i=1; i<ipWordLength; i++){
		if (szTemp[i]!=szTemp[i-1]){
			FSWCHAR ch=szTemp[i];
			szTemp[i]=szTemp[i-1];
			szTemp[i-1]=ch;
			CheckAndAdd(szTemp);
			szTemp[i-1]=szTemp[i];
			szTemp[i]=ch;
		}
	}

	// Change blocks
	for (i=0; i<ipWordLength; i++){
		for (j=0; j<(INTPTR)(sizeof(ChangeStrings)/sizeof(__CChangeStrings)); j++){
			if (szWordHigh.ContainsAt(i, ChangeStrings[j].m_lpszFrom)){
				szTemp=szWordHigh.Left(i)+ChangeStrings[j].m_lpszTo+szWordHigh.Mid(i+FSStrLen(ChangeStrings[j].m_lpszFrom));
				CheckAndAdd(szTemp);
			}
		}
	}

	// Change end blocks
	for (i=0; i<(INTPTR)(sizeof(ChangeStringsEnd)/sizeof(__CChangeStrings)); i++){
		if (szWordHigh.EndsWith(ChangeStringsEnd[i].m_lpszFrom)){
			szTemp=szWordHigh.Left(ipWordLength-FSStrLen(ChangeStringsEnd[i].m_lpszFrom))+ChangeStringsEnd[i].m_lpszTo;
			CheckAndAdd(szTemp);
		}
	}

	// Po~o~sas
	MultiReplace(szWordHigh, 0);

	// gi/ki: Kylli[gi]le -> Kyllile[gi]
	for (i=3; i<=6; i++){
		if (i>ipWordLength) break;
		if (memcmp((const FSWCHAR *)szWordHigh+ipWordLength-i, FSWSTR("GI"), 2*sizeof(FSWCHAR))==0){
			szTemp=szWordHigh.Left(ipWordLength-i)+szWordHigh.Mid(ipWordLength-i+2)+FSWSTR("GI");
			CheckAndAdd(szTemp);
			szTemp=szWordHigh.Left(ipWordLength-i)+szWordHigh.Mid(ipWordLength-i+2)+FSWSTR("KI");
			CheckAndAdd(szTemp);
		}
	}

	// Delete letters: van[n]aema -> vanaema
	szTemp=szWordHigh.Mid(1);
	CheckAndAdd(szTemp);
	for (i=0; i<ipWordLength-1; i++){
		if (szTemp[i]!=szWordHigh[i]){
			szTemp[i]=szWordHigh[i];
			CheckAndAdd(szTemp);
		}
	}

	// Change letters from list
	for (i=0; i<ipWordLength; i++){
		const FSWCHAR *lpszTo=__SuggestChangeLetters(szWordHigh[i]);
		if (!lpszTo) continue;
		szTemp=szWordHigh;
		for (; lpszTo[0]; lpszTo++){
			szTemp[i]=lpszTo[0];
			CheckAndAdd(szTemp);
		}
	}
	
	// Insert letters to word body
	for (i=1; i<ipWordLength; i++){
		szTemp=szWordHigh.Left(i)+FSWSTR(' ')+szWordHigh.Mid(i);
		for (j=0; szInsertLetters[j]; j++){
			szTemp[i]=szInsertLetters[j];
			CheckAndAdd(szTemp);
		}
	}

	// Insert letters to the beginning
	szTemp=CFSWString(FSWSTR(" "))+szWordHigh;
	for (i=0; szInsertLettersBeg[i]; i++){
		if (szTemp[1]==szInsertLettersBeg[i]) continue;
		szTemp[0]=szInsertLettersBeg[i];
		CheckAndAdd(szTemp);
	}

	// Try apostrophe for names
	if (szWord[0]!=szWordHigh[0] && szWordHigh.Find('\'')<0){
		for (i=0; i<5; i++){
			if (i>=ipWordLength) break;
			szTemp=szWordHigh.Left(ipWordLength-i)+L'\''+szWordHigh.Mid(ipWordLength-i);
			CheckAndAdd(szTemp);
		}
	}

	Order();
	RemoveImmoderate();
	RemoveDuplicates();
	return 0;
}