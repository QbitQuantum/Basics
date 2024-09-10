// This function tries to prevent the user from entering invalid
// amounts in the CArborEditCurrency text control.  This is difficult
// to do here because you really need the amount string after the edit,
// not before.  This function attempts to construct the new amount string,
// but it's risky business trying to predict what Windows will REALLY do...
//
// A better approach might be to construct a DDV_Currency function that
// checks for valid amounts after the user selects "OK" from the dialog box.
void CArborEditCurrency::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// If the control is read only, beep and exit
	if (GetStyle() & ES_READONLY)
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	// Get the decimal delimiter for this currency.  Beep and exit if problem
	// getting currency info (invalid currency or init_currency_formats
	// not called)
	char cDelimiter = get_currency_decimal_delimiter(m_iCurrencyCode);
	if (cDelimiter == -1)
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	// If the input character is not a control character,
	// digit, or decimal delimiter, then beep and exit
	if (!(nChar < 0x20) &&
		!isdigit(nChar) &&
		!(nChar == (UINT)cDelimiter))
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	// Now attempt to construct what the new text string will look like.
	// Only try this for "normal" edits; i.e., edits that don't involve
	// control characters other than paste (0x16).
	if (nChar == 0x16 || nChar > 0x19)
	{
		// Get the old string
		CString oldString;
		GetWindowText(oldString);

		// Get the inserted string.  This is a single character unless
		// text is being pasted from the clipboard.
		CString insertedString;
		if (nChar != 0x16)
		{
			insertedString = (char)nChar;
		}
		else
		{
			// Get pasted text from the clipboard
			if (OpenClipboard())
			{
				HGLOBAL hData = ::GetClipboardData(CF_TEXT);
				if (hData)
				{
					insertedString = (LPCTSTR) GlobalLock(hData);
					GlobalUnlock(hData);
				}
			}
			CloseClipboard();
		}

		// Construct the new string.
		// Replace any text that is currently selected.
		int iStartSel, iEndSel;
		GetSel(iStartSel, iEndSel);
		CString newString = oldString.Left(iStartSel) + insertedString
			+ oldString.Right(oldString.GetLength() - iEndSel);

		// Count the number of minus signs, decimal delimiters,
		// integer digits, and decimal digits
		int nMinusSigns = 0;
		int nDelimiters = 0;
		int nIntegerDigits = 0;
		int nDecimalDigits = 0;

		for (int i = 0; i < newString.GetLength(); i++)
		{
			if (newString[i] == '-')
				nMinusSigns++;
			if (newString[i] == cDelimiter)
				nDelimiters++;
			if (isdigit(newString[i]) && nDelimiters == 0)
				nIntegerDigits++;
			if (isdigit(newString[i]) && nDelimiters > 0)
				nDecimalDigits++;
		}

		// Determine the maximum number of integer and decimal digits
		// based on Arb_numeric and the currency.  If problem getting
		// currency info (perhaps invalid currency or init_currency_formats
		// not called), beep and exit.
		int maxDecimalDigits = get_currency_implied_decimal(m_iCurrencyCode);
		if (maxDecimalDigits == -1)
		{
			MessageBeep(MB_ICONEXCLAMATION);
			return;
		}
		int maxIntegerDigits = ARB_NUMERIC_LEN - 3 - maxDecimalDigits;

		// Beep and exit if this is not a valid amount string
		// - Minus sign (not allowed during user input)
		// - More than one decimal delimiter
		// - More than the maximum number of integer digits
		// - More than the maximum number of decimal digits
		if ((nMinusSigns > 0) ||
			(nDelimiters > 1) ||
			(nIntegerDigits > maxIntegerDigits) ||
			(nDecimalDigits > maxDecimalDigits))
		{
			MessageBeep(MB_ICONEXCLAMATION);
			return;
		}
	}

	// Pass the character onto CEdit for processing
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}