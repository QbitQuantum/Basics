void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
#if 1

	// flomar, 03/28/2013: after hours of debugging I finally located the source of 
	// the problem; obviously the user's key strokes weren't correctly processed, in 
	// other words a character inserted at a specific location would get assigned to an 
	// incorrect matrix cell-- before digging in any deeper I completely re-wrote this 
	// function; it *should* work as intended now; I left the old code in here on purpose 
	// (see the '#if' blocks above and below) in case someone has to deal with this in 
	// another 10 or so years, and I'm not 100% sure I didn't introduce some bugs myself

	// the character the user tried to insert-- in case the character is invalid with regards 
	// to the analysis alphabet, it gets replaced implicitly; if the replacement fails (i.e. 
	// the character is still invalid), we return right away and notify the user with a beep
	const char newCharacter = MyToUpper(m_Alg->getAlphabet()->replaceInvalidLetter(true, nChar));
	if(!m_Alg->myisalpha2(newCharacter)) {
		MessageBeep(MB_OK);
	}
	// the character that was replaced by the new character; the way this is handled 
	// is pretty ugly with all that SetSel/GetLine stuff, but I'm certainly not gonna 
	// touch any other parts of this dialog for the meantime (note: a better solution 
	// would be to have member variables for each and every cell of the GUI matrix);
	// in case the character is not part of the analysis alphabet, we're trying to 
	// convert it just like we did with the new character above
	char tempCharacter[2];
	memset(tempCharacter, 0, sizeof(char) * 2);
	SetSel(0, 1);
	GetLine(0, tempCharacter, 1);
	ReplaceSel(CString(newCharacter));
	SetSel(0, 1);
	// try to replace the temp character with something valid, if necessary
	tempCharacter[0] = MyToUpper(m_Alg->getAlphabet()->replaceInvalidLetter(true, tempCharacter[0]));
	// if the character is still invalid after the conversion, we proceed with a 
	// null element which, as of today, is denoted by the '*' character
	if(!tempCharacter[0]) {
		tempCharacter[0] = m_Alg->getAlphabet()->getNullElement()->getValue();
	}
	// at this point all conversion work is done, we can now assign the old character
	const char oldCharacter = tempCharacter[0];
	// if old a new character are identical, return without doing anything else
	if(newCharacter == oldCharacter) {
		return;
	}
	// if the new character is invalid (not part of the alphabet), return as well
	if(!m_Alg->myisalpha2(newCharacter)) {
		return;
	}
	// we're gonna need those in a minute...
	int newCharacterIndexColumn = -1;
	int newCharacterIndexRow = -1;
	// get the size of the current maxtrix (either 5x5 or 6x6)
	const int matrixSize = m_Alg->getSize();
	// go through all cells of the matrix and find the newly inserted character
	for(int indexRow=0; indexRow<matrixSize; indexRow++) {
		for(int indexColumn=0; indexColumn<matrixSize; indexColumn++) {
			// get the current character
			char currentCharacter = m_Alg->getCharOfMatrix(indexColumn, indexRow);
			// ignore null elements
			if(currentCharacter != m_Alg->getAlphabet()->getNullElement()->getValue()) {
				// assign indices for new character
				if(newCharacter == currentCharacter) {
					newCharacterIndexColumn = indexColumn;
					newCharacterIndexRow = indexRow;
				}
			}
		}
	}
	// this variable tells us if the new character did already exist in the matrix
	const bool newCharacterAlreadyExisted = newCharacterIndexColumn != -1 && newCharacterIndexRow != -1;
	// if the new character did NOT exist in the matrix, determine its indices (column/row)
	if(!newCharacterAlreadyExisted) {
		for(int indexRow=0; indexRow<matrixSize && newCharacterIndexRow<0; indexRow++) {
			for(int indexColumn=0; indexColumn<matrixSize && newCharacterIndexColumn<0; indexColumn++) {
				// get the content of the current matrix cell
				CString stringCurrentMatrixCell;
				m_Dia->getEinfeld(indexColumn, indexRow)->GetWindowText(stringCurrentMatrixCell);
				// check if we've arrived at the new character
				if(newCharacter == stringCurrentMatrixCell[0]) {
					// update indices for the new character
					newCharacterIndexColumn = indexColumn;
					newCharacterIndexRow = indexRow;
					// now update the matrix (actually insert the new character at its appropriate position)
					m_Alg->setElMatrix(newCharacter, newCharacterIndexColumn, newCharacterIndexRow);
				}
			}
		}
	}
	// in case the new character was already inserted, switch back to the old character
	if(newCharacterAlreadyExisted) {
		// update the dialog
		m_Dia->getEinfeld(newCharacterIndexColumn, newCharacterIndexRow)->SetWindowText(CString(oldCharacter));
		// update the analysis
		m_Alg->setElMatrix(oldCharacter, newCharacterIndexColumn, newCharacterIndexRow);
	}
	// some clean-up work
	m_Alg->UpdateDigrams(m_Dia->getDec());
	m_Alg->DoCipher(false, m_Dia->getDec(),MAXSHOWLETTER);
	m_Dia->UpdateListBox();
	m_Dia->UpdatePassword();
	
#else
	char b1[2],b2[2];

	if(!m_Alg->myisalpha2(nChar))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
		nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, MyToUpper(nChar));
	if (m_Alg->myisalpha2(nChar))
	{
		int i,j,s,a,b,c,d;

		a=-1; c =-1;
		b2[1]=0;
		b2[0]=MyToUpper(nChar);
		SetSel(0, 1);
		GetLine(0,b1,2);
		ReplaceSel(b2);
		SetSel(0, 1);
		if(!m_Alg->myisalpha2(b1[0])){  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			b1[0] = m_Alg->getAlphabet()->replaceInvalidLetter(true, b1[0]);
			if (b1[0] == '\0')
				b1[0] = m_Alg->getAlphabet()->getNullElement()->getValue();
		}
		if (b1[0]==b2[0]||!m_Alg->myisalpha2(b2[0]))
			return;
		s=m_Alg->getSize();
		for (i=0;i<s;i++)
		{
			for (j=0;j<s;j++)
			{
				if (b1[0] == m_Alg->getCharOfMatrix (i,j))
				{ // hole Indices vom alten Buchstaben
					a=i;
					b=j;
				}
				if (b2[0] == m_Alg->getCharOfMatrix (i,j))
				{ // hole Indices vom eingetippten Buchstaben
					c=i;
					d=j;
				}
			}
		}
		if (a>=0) { // zu ersetzender Buchstabe gefunden
			i=i;
		} else { // wie erfahre ich meine Koordinaten?
			for (i=0;(i<s)&&(a<0);i++)
				for (j=0;(j<s)&&(a<0);j++) {
					CString tmpstr;
					m_Dia->getEinfeld(i,j)->GetWindowText(tmpstr);
					if (b2[0] == tmpstr[0]) {
						a=i; b=j;
					}
				}
			i=i;
		}
		m_Alg->setElMatrix (b2[0], a, b);
		if (c>=0) { // eingetippter Buchstabe war schon vorhanden
			m_Dia->getEinfeld(c,d)->SetWindowText(b1);
			m_Alg->setElMatrix (b1[0], c, d);
		} else {
			i=i;
		}
		m_Alg->UpdateDigrams(m_Dia->getDec());
		m_Alg->DoCipher(false, m_Dia->getDec(),MAXSHOWLETTER);
		m_Dia->UpdateListBox();
		m_Dia->UpdatePassword();
	} else  // invalid character
		MessageBeep(MB_OK);
#endif
} // void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)