LRESULT TPResetDlg::InitDialog()
{
	PTEdit pE;

	pE = (PTEdit) GetChild(EID_VNUM);
	SetDlgItemInt(hWindow, EID_VNUM, pPReset->nVnum, FALSE);
	pE->LimitText(5);
	pE->SetSel(0, 32767);
	pE->SetFocus();

	pE = (PTEdit) GetChild(EID_LIMIT);
	SetDlgItemInt(hWindow, EID_LIMIT, pPReset->nLimit, TRUE);
	pE->LimitText(5);

	pE = (PTEdit) GetChild(EID_AMOUNT);
	SetDlgItemInt(hWindow, EID_AMOUNT, pPReset->nAmount, TRUE);
	pE->LimitText(5);

	return 0;
}	//TPResetDlg::InitDialog