void ExhTestCPEngine::ExhTestProperties()
{
	HRESULT hr;

	// REVIEW LarsH: how do we pass in the location of the UnicodeData.txt file as
	// a parameter?  Env var?
	StrAnsi staDataFile = L"d:\\lars\\Unicode\\UnicodeData.txt";
	FILE *pFileIn = fopen(staDataFile, "r");
	if (!pFileIn)
		FailureFormat("Unable to open Unicode data file %s", staDataFile);

	CodePtData cpdCurrent, cpdNext;
	cpdNext.chCodeValue = -1;	// uninitialized

	// TODO LarsH: We should test through 0x10FFFF, but currently there are
	// some problems with higher characters which have been postponed,
	// so in order to avoid a humungous error log we'll stick with the first page for now.
	// Raid #31
#define JUST_FIRST_PAGE
#ifdef JUST_FIRST_PAGE
	for (int ch = 0; ch <= 0xFFFF; ch++)
#else
	for (int ch = 0; ch <= 0x10FFFF; ch++)
#endif
	{
		if (! (ch % 0x1000))
			LogFormat("%x:\n", ch);

		// Read in the next record unless we've already got this data
		if (cpdNext.chCodeValue < ch)
			ParseRecord(pFileIn, &cpdNext);
		// This is NOT an "else"; it may happen in addition to the above.
		if (cpdNext.chCodeValue == ch)
		{
			// got the right record; copy it over
			cpdCurrent.chCodeValue = ch;
			strcpy(cpdCurrent.szCategory, cpdNext.szCategory);
			wcscpy(cpdCurrent.szwName, cpdNext.szwName);
			cpdCurrent.nNumericValue = cpdNext.nNumericValue;
			cpdCurrent.nCombiningClass = cpdNext.nCombiningClass;
			wcscpy(cpdCurrent.szwDecomposition, cpdNext.szwDecomposition);
			cpdCurrent.chUpper = cpdNext.chUpper;
			cpdCurrent.chLower = cpdNext.chLower;
			cpdCurrent.chTitle = cpdNext.chTitle;
		}

		// Treat special ranges specially:
		if (ch >= 0x3400 && ch <= 0x4db5 || ch >= 0x4e00 && ch <= 0x9fa5)
		{
			// CJK Ideographs (Extension A and other)
			// Most data is same as previous, so don't need to load;
			// but must set names algorithmically.
			swprintf(cpdCurrent.szwName, L"CJK UNIFIED IDEOGRAPH-%X", ch);
		}
		else if (ch >= 0xac00 && ch <= 0xd7a3)
		{
			// Hangul Syllables
			// Data for 0xAC00 is loaded, and applies to all others, except
			//  name and decomp.
			HangulDecomposition(ch, cpdCurrent.szwDecomposition);
			HangulName(cpdCurrent.szwDecomposition, cpdCurrent.szwName);
		}
		else if (ch >= 0xd800 &&
			  // ch <= 0xdb7f || ch >= 0xdb80 && ch <= 0xdbff ||
			  // ch >= 0xdc00 && ch <= 0xdfff || ch >= 0xe000
				 ch <= 0xf8ff)
		{
			// Consecutive ranges: Non-Private Use High Surrogates,
			// Private Use High Surrogates, Low Surrogates, Private Use Area.
			// All of these are nameless (UnicodeData File Format v3.0.0)
			// TODO LarsH: change all this before closing Raid #24.
			cpdCurrent.szwName[0] = '\0';
		}
		else if (ch == 0xfffe || ch == 0xffff ||  // explicitly "not Unicode chars"
			cpdNext.chCodeValue > ch || (cpdNext.chCodeValue < ch && feof(pFileIn)))
		{
			// Not assigned in the data file.
			cpdCurrent.chCodeValue = ch;
			cpdCurrent.szwName[0] = '\0';
			strcpy(cpdCurrent.szCategory, "Cn");
			cpdCurrent.nCombiningClass = 0;
			// Must distinguish between lack of a NumericValue and a zero NumericValue.
			cpdCurrent.nNumericValue = -1;
			cpdCurrent.szwDecomposition[0] = '\0';
			// Zero is not an anycase equivalent of any character.
			cpdCurrent.chLower = cpdCurrent.chUpper = cpdCurrent.chTitle = ch;
		}

		// ** If looking for a character with a specific combination of properties,
		// ** you can test it here.  This would be better done in SQL.
		//	if (cpdCurrent.szCategory[0] != 'L' && cpdCurrent.chUpper > 0)
		//		LogFormat("*** U+%x fulfills conditions\n");
		//	continue; // skip all the usual tests if desired

		// Make sure the property interface methods get the same data.
		LgGeneralCharCategory cc = ParseCC(cpdCurrent.szCategory);
		CheckCat(ch, cc);

		ComBool fLet, fPun, fNum, fSep, fSym, fMar, fOth, fAll;
#define CheckBoolProp(prop, var, index, letter) \
		{ \
			hr = m_qpropeng->get_##prop(ch, &var); \
			WarnHr(hr); \
			if (var != (cpdCurrent.szCategory[index] == letter)) \
				FailureFormat("get_" #prop "(U+%x) gave wrong answer", ch); \
		}

		CheckBoolProp(IsLetter,      fLet, 0, 'L');
		CheckBoolProp(IsPunctuation, fPun, 0, 'P');
		CheckBoolProp(IsNumber,      fNum, 0, 'N');
		CheckBoolProp(IsSeparator,   fSep, 0, 'Z');
		CheckBoolProp(IsSymbol,      fSym, 0, 'S');
		CheckBoolProp(IsMark,        fMar, 0, 'M');
		CheckBoolProp(IsOther,       fOth, 0, 'C');

		// REVIEW LarsH: is int(ComBool) guaranteed to be 1 if true?  I think so.
		int nCat;
		if ((nCat = fLet + fPun + fNum + fSep + fSym + fMar + fOth) != 1)
			FailureFormat("Codepoint U+%x is in %d categories instead of one.",
				ch, nCat);

		if (fLet)
		{
			ComBool fUpp, fLow, fTit, fMod, fOth;
			CheckBoolProp(IsUpper,    fUpp, 1, 'u');
			CheckBoolProp(IsLower,    fLow, 1, 'l');
			CheckBoolProp(IsTitle,    fTit, 1, 't');
			CheckBoolProp(IsModifier, fMod, 1, 'm');
			CheckBoolProp(IsOtherLetter,    fOth, 1, 'o');
			if ((nCat = fUpp + fLow + fTit + fMod + fOth) != 1)
				FailureFormat("Letter U+%x is in %d subcategories instead of one.",
					ch, nCat);
		}
		else
		{
			// All should be false.
			CheckBoolProp(IsUpper,    fAll, 0, 'L');
			CheckBoolProp(IsLower,    fAll, 0, 'L');
			CheckBoolProp(IsTitle,    fAll, 0, 'L');
			CheckBoolProp(IsModifier, fAll, 0, 'L');
			CheckBoolProp(IsOtherLetter, fAll, 0, 'L');
		}

		if (fPun)
		{
			ComBool fOpe, fClo, fMed;
			CheckBoolProp(IsOpen,       fOpe, 1, 's');
			CheckBoolProp(IsClose,      fOpe, 1, 'e');
			CheckBoolProp(IsWordMedial, fOpe, 1, 'c');
			// TODO LarsH: update this if definition in Language.idh changes, e.g.
			// if the above methods come to be true for Pd, Pi, Pf
		}
		else
		{
			CheckBoolProp(IsOpen,       fAll, 0, 'P');
			CheckBoolProp(IsClose,      fAll, 0, 'P');
			CheckBoolProp(IsWordMedial, fAll, 0, 'P');
		}

		// IsControl should return true if category is Cc, false otherwise:
		CheckBoolProp(IsControl, fAll, 1, (cpdCurrent.szCategory[0] == 'C' ? 'c' : 0));

#undef CheckBoolProp

#define IsLetter() (cpdCurrent.szCategory[0] == 'L')
#define IsUpper() (cpdCurrent.szCategory[1] == 'u')
#define IsLower() (cpdCurrent.szCategory[1] == 'l')
#define IsTitle() (cpdCurrent.szCategory[1] == 't')
		// We must check IsLetter() etc. because the docs say, if it's not Lu/Ll/Tt, ToUpper() etc.
		// don't do case conversion, even if the Unicode database gives a conversion.

		int chUpper = -1, chLower = -1, chTitle = -1;

		// TODO LarsH: some of these should check different locales
		// if such data exists in SpecialCasing.txt

		hr = m_qpropeng->get_ToUpperCh(ch, &chUpper);
		if (FAILED(hr))
			FailureFormat("get_ToUpperCh(0x%x) gave result %s", ch, AsciiHresult(hr));
		int chUExp = (IsLetter() && (IsLower() || IsTitle()) && cpdCurrent.chUpper) ?
			cpdCurrent.chUpper : ch;
		if (chUpper != chUExp)
		{
			FailureFormat("get_ToUpperCh(0x%x {%s}) returned 0x%x instead of 0x%x",
				ch, cpdCurrent.szCategory, chUpper, chUExp);
		}

		hr = m_qpropeng->get_ToLowerCh(ch, &chLower);
		if (FAILED(hr))
			FailureFormat("get_ToLowerCh(0x%x) gave result %s", ch, AsciiHresult(hr));
		int chLExp = (IsLetter() && (IsUpper() || IsTitle()) && cpdCurrent.chLower) ?
			cpdCurrent.chLower : ch;
		if (chLower != chLExp)
		{
			FailureFormat("get_ToLowerCh(0x%x {%s}) returned 0x%x instead of 0x%x",
				ch, cpdCurrent.szCategory, chLower, chLExp);
		}
		hr = m_qpropeng->get_ToTitleCh(ch, &chTitle);
		if (FAILED(hr))
			FailureFormat("get_ToTitleCh(0x%x) gave result %s", ch, AsciiHresult(hr));
#define FIXED_BUG_198 // just for now
#ifdef FIXED_BUG_198
		int chTExp = (IsLetter() && (IsUpper() || IsLower())) ?
			(cpdCurrent.chTitle ? cpdCurrent.chTitle : cpdCurrent.chUpper ? cpdCurrent.chUpper : ch) :
			ch;
		// ToTitleCh() returns the uppercase if there is no titlecase value defined

		if (chTitle != chTExp)
		{
			FailureFormat("get_ToTitleCh(0x%x {%s}) returned 0x%x instead of 0x%x",
				ch, cpdCurrent.szCategory, chTitle, chTExp);
		}
#endif // FIXED_BUG_198

		// TODO LarsH: test get_ToLower, etc. (BSTR functions)
		// These should take into account any special casing (SpecialCasing.txt), by testing
		// different locales (esp. Turkish) and contexts (FINAL/NON_FINAL, MODERN/NON_MODERN).
		wchar pwz[2];
		pwz[0] = (wchar)ch;
		pwz[1] = '\0';
		SmartBstr sbstrFrom(pwz), sbstrTo = L"fish";

		// This one properly gives a warning if ch is half of a surrogate pair.
		if (ch >= 0xd800 && ch <= 0xdfff) // half a surrogate pair
		{
			IgnoreWarnings iw;
			hr = m_qpropeng->ToLower(sbstrFrom, &sbstrTo);
			TestFailZero(sbstrTo, "ToLower");
			if (SUCCEEDED(hr))
				FailureFormat("ToLower with 0x%x (half a surrogate pair) should have failed", ch);
		}
		else
		{
			hr = m_qpropeng->ToLower(sbstrFrom, &sbstrTo);
			TestFailZero(sbstrTo, "ToLower");
			WarnHr(hr);
			// TODO LarsH: check that the return value from get_ToLower is correct
			// TODO LarsH: use smart bstrs where possible
		}


		// TODO LarsH: test get_ToLowerRgch, etc. (Rgch functions)

		// TODO LarsH: test IsUserDefinedClass().  Right now there is no way to define
		// classes, so this will always return false.
		ComBool fRet;
		hr = m_qpropeng->get_IsUserDefinedClass(ch, 'A', &fRet);
		WarnHr(hr);
		if (fRet)
			FailureFormat("Character U+%x is a member of class 'A'??", ch);

		// TODO LarsH: test SoundAlikeKey

		// REVIEW LarsH: is this bstr causing a memory leak on every iteration of ch?
		SmartBstr sbstr = L"foo";

		// TODO LarsH: Remove this kludge once get_CharacterName(Hangul) is working.
		if (ch >= 0xac00 && ch <= 0xd7a3)
			goto skipHangul;

		hr = m_qpropeng->get_CharacterName(ch, &sbstr);
		TestFailZero(sbstr, "get_CharacterName");
		if (FAILED(hr))
			FailureFormat("get_CharacterName(U+%x) failed", ch);
		else if (
#ifndef FIXED_BUG_24
			!(ch >= 0xd800 && ch <= 0xf8ff) &&
#endif
				wcscmp(cpdCurrent.szwName, sbstr))
		{
			FailureFormat(L"get_CharacterName(U+%x) returned \"%s\" instead of \"%s\".",
				ch, sbstr, cpdCurrent.szwName);
		}
		// if (sbstr)
		//  	SysFreeString(sbstr);

#ifdef FIXED_BUG_125
		sbstr = L"foo";
		hr = m_qpropeng->get_Decomposition(ch, &sbstr);
		TestFailZero(sbstr, "get_Decomposition");
		if (FAILED(hr))
			FailureFormat("get_Decomposition(U+%x) failed", ch);
		// REVIEW LarsH: Does wcscmp understand NULL sbstrs?  Apparently...
		else if (sbstr ? wcscmp(cpdCurrent.szwDecomposition, sbstr) :
				cpdCurrent.szwDecomposition[0])
		{
			FailureFormat("Got wrong decomposition for U+%x", ch);
		}
		// if (sbstr)
		// 	SysFreeString(bstr);
#endif // FIXED_BUG_125

		sbstr = NULL;

		// TODO LarsH: test DecompositionRgch
		// That will probably require a separate pass through the whole UnicodeData
		// file to build up a hash table or sthg...



skipHangul:

		int nNumericValue;
		{
			IgnoreWarnings iw;
			hr = m_qpropeng->get_NumericValue(ch, &nNumericValue);
		}
		if (fNum && (cc == kccNd || cc == kccNl || cc == kccNo) && cpdCurrent.nNumericValue > -1)
		{
			if (FAILED(hr))
				FailureFormat("get_NumericValue(U+%x) failed with hr=%s", ch, AsciiHresult(hr));
			else if (nNumericValue != cpdCurrent.nNumericValue)
			{
				FailureFormat("get_NumericValue(U+%x) returned %d instead of %d",
					ch, nNumericValue, cpdCurrent.nNumericValue);
			}
		}
		else if (hr != E_UNEXPECTED)
		{
			FailureFormat("get_NumericValue(U+%x {%s}) gave result %s instead of E_UNEXPECTED",
				ch, cpdCurrent.szCategory, AsciiHresult(hr));
		}

#define FIXED_BUG_18 1  // Seems to be fixed now.
#ifdef FIXED_BUG_18
		int nCombClass;
		hr = m_qpropeng->get_CombiningClass(ch, &nCombClass);
		WarnHr(hr);
		if (nCombClass != cpdCurrent.nCombiningClass)
		{
			FailureFormat("get_CombiningClass(U+%x) gave %d instead of %d",
				ch, nCombClass, cpdCurrent.nCombiningClass);
		}
#endif
		// TODO LarsH: test everything else


		// TODO LarsH: test get_Comment

		// TODO LarsH: test GetLineBreakProps if not obsolete
		// TODO LarsH: test GetLineBreakStatus if not obsolete

	}
}