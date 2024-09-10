LRESULT CSetPgSizePos::OnEditChanged(HWND hDlg, WORD nCtrlId)
{
	switch (nCtrlId)
	{
	case tWndX:
	case tWndY:
		if (isChecked(hDlg, rNormal) == BST_CHECKED)
		{
			wchar_t *pVal = GetDlgItemTextPtr(hDlg, nCtrlId);
			bool bValid = (pVal && isDigit(*pVal));
			enableDlgItem(hDlg, cbApplyPos, bValid);
			SafeFree(pVal);
		}
		break; // case tWndX: case tWndY:
	case tWndWidth:
	case tWndHeight:
		if (isChecked(hDlg, rNormal) == BST_CHECKED)
		{
			CESize sz = {0};
			wchar_t *pVal = GetDlgItemTextPtr(hDlg, nCtrlId);
			bool bValid = (pVal && sz.SetFromString(false, pVal));
			enableDlgItem(hDlg, cbApplyPos, bValid);
			SafeFree(pVal);
		}
		break; // case tWndWidth: case tWndHeight:

	case tPadSize:
	{
		BOOL bPadOk = FALSE;
		UINT nNewPad = GetDlgItemInt(hDlg, nCtrlId, &bPadOk, FALSE);

		if (nNewPad >= CENTERCONSOLEPAD_MIN && nNewPad <= CENTERCONSOLEPAD_MAX)
			gpSet->nCenterConsolePad = nNewPad;
		else if (nNewPad > CENTERCONSOLEPAD_MAX)
			SetDlgItemInt(hDlg, nCtrlId, CENTERCONSOLEPAD_MAX, FALSE);
		// Если юзер ставит "бордюр" то нужно сразу включить опцию, чтобы он работал
		if (gpSet->nCenterConsolePad && !isChecked(hDlg, cbTryToCenter))
		{
			gpSet->isTryToCenter = true;
			checkDlgButton(hDlg, cbTryToCenter, BST_CHECKED);
		}
		// Update window/console size
		if (gpSet->isTryToCenter)
			gpConEmu->OnSize();
		break;
	}

	case tLongOutputHeight:
	{
		BOOL lbOk = FALSE;
		wchar_t szTemp[16];
		UINT nNewVal = GetDlgItemInt(hDlg, nCtrlId, &lbOk, FALSE);

		if (lbOk)
		{
			if (nNewVal >= LONGOUTPUTHEIGHT_MIN && nNewVal <= LONGOUTPUTHEIGHT_MAX)
				gpSet->DefaultBufferHeight = nNewVal;
			else if (nNewVal > LONGOUTPUTHEIGHT_MAX)
				SetDlgItemInt(hDlg, nCtrlId, gpSet->DefaultBufferHeight, FALSE);
		}
		else
		{
			SetDlgItemText(hDlg, nCtrlId, _ltow(gpSet->DefaultBufferHeight, szTemp, 10));
		}
		break;
	} //case tLongOutputHeight:

	default:
		_ASSERTE(FALSE && "EditBox was not processed");
	}

	return 0;
}