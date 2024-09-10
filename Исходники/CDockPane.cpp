bool CDockPane::HandleChar (char chChar)

//	HandleChar
//
//	Handle a character

	{
	//	Deal with input fields

	SControl *pControl;
	if (pControl = GetControlByType(controlTextInput))
		{
		CGTextArea *pTextArea = pControl->AsTextArea();
		if (chChar >= ' ' && chChar <= '~')
			{
			CString sText = pTextArea->GetText();
			sText.Append(CString(&chChar, 1));
			pTextArea->SetText(sText);
			pTextArea->SetCursor(0, sText.GetLength());
			return true;
			}
		}
	else if (pControl = GetControlByType(controlCounter))
		{
		CGTextArea *pTextArea = pControl->AsTextArea();

		switch (chChar)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (pControl->bReplaceInput)
					{
					pTextArea->SetText(strFromInt(chChar - '0', false));
					pControl->bReplaceInput = false;
					}
				else
					{
					CString sCounter = pTextArea->GetText();
					sCounter.Append(strFromInt(chChar - '0', false));
					pTextArea->SetText(sCounter);
					}
				return true;
			}
		}

	//	Deal with accelerators
	//	Check to see if one of the key matches one of the accelerators

	int iAction;
	if (m_Actions.FindByKey(CString(&chChar, 1), &iAction))
		{
		g_pUniverse->PlaySound(NULL, g_pUniverse->FindSound(UNID_DEFAULT_SELECT));
		m_Actions.Execute(iAction, m_pDockScreen);
		return true;
		}

	//	Didn't handle it

	return false;
	}