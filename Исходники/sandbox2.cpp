LRESULT TMobAttrDlg::InitDialog()
{
	PTEdit pE;
	PTCheckBox pChB;
    PTComboBox pCB;
    char sz[80];

    //init the data that gets passed to flags, dice, etc. dlgs
	NewAction = pMob->ActionFlg;
	NewAffect = pMob->AffectFlg;
	if (pMob->pShop)
		NewShop = *(pMob->pShop);

	//init the controls
	pE = (PTEdit) GetChild(EID_VNUM);
	pE->LimitText(5);
	SetDlgItemInt(hWindow, EID_VNUM, pMob->nVnum, FALSE);
	pE->SetSel(0, 32767);
	pE->SetFocus();

	pE = (PTEdit) GetChild(EID_KEYWORDS);
    pE->LimitText(255);
    pE->SetText(pMob->sKeywords);

	pE = (PTEdit) GetChild(EID_SHORTDESC);
	pE->LimitText(255);
    pE->SetText(pMob->sShortDesc);

	pE = (PTEdit) GetChild(EID_LONGDESC);
	SendMessage(pE->hWindow, WM_SETFONT, (WPARAM) hCourier, 0);
	pE->LimitText(4095);
    pE->SetText(pMob->sLongDesc);

	pE = (PTEdit) GetChild(EID_DESC);
    SendMessage(pE->hWindow, WM_SETFONT, (WPARAM) hCourier, 0); 
	pE->LimitText(4095);
	pE->SetText(pMob->sDesc);

	pE = (PTEdit) GetChild(EID_ALIGN);
	pE->LimitText(5);
	SetDlgItemInt(hWindow, EID_ALIGN, pMob->nAlign, TRUE);

	pE = (PTEdit) GetChild(EID_LEVEL);
    pE->LimitText(5);
	SetDlgItemInt(hWindow, EID_LEVEL, pMob->nLevel, FALSE);

	pE = (PTEdit) GetChild(EID_GOLD);
    pE->LimitText(10);
    SetDlgItemLong(hWindow, EID_GOLD, pMob->lGold, FALSE);

    pCB = (PTComboBox) GetChild(CBID_STARTPOS);
	PosList.ForEach(FillBox, pCB);
	SelectCB(pCB, PosList, pMob->nStartPos);

	pCB = (PTComboBox) GetChild(CBID_DEFPOS);
	PosList.ForEach(FillBox, pCB);
    SelectCB(pCB, PosList, pMob->nDefPos);

	pCB = (PTComboBox) GetChild(CBID_SEX);
	SexList.ForEach(FillBox, pCB);
	SelectCB(pCB, SexList, pMob->nSex);

	pCB = (PTComboBox) GetChild(CBID_SPECFUNC);
	SpecFuncList.ForEach(FillBox, pCB);
    if (!pMob->sSpecial.Len())	//no special function, then select "none" in CB
		SelectCB(pCB, SpecFuncList, "none");
	else
		SelectCB(pCB, SpecFuncList, pMob->sSpecial);

	if (pMob->pShop)
	{
		pChB = (PTCheckBox) GetChild(CHID_SHOP);
		pChB->SetCheck(BF_CHECKED);
	}

    //disable stuff that old-style mobs don't have
	if (pMob->Type() == OLD)
	{
		GetChild(CBID_RACE)->Enable(FALSE);
		GetChild(EID_HITBONUS)->Enable(FALSE);
		GetChild(PBID_HP)->Enable(FALSE);
		GetChild(PBID_MANA)->Enable(FALSE);
		GetChild(PBID_DAMAGE)->Enable(FALSE);
		GetChild(CBID_DAMTYPE)->Enable(FALSE);
		GetChild(PBID_AC)->Enable(FALSE);
		GetChild(CBID_SIZE)->Enable(FALSE);
		GetChild(CBID_MATERIAL)->Enable(FALSE);
	}
	else
	{
		PTMobile pMobile = (PTMobile) pMob;

		//init the data that gets passed to flags, dice, etc. dlgs
		NewHP = pMobile->HP;
		NewMana = pMobile->Mana;
		NewDamage = pMobile->Damage;
		NewAC = pMobile->AC;
		NewOff = pMobile->OffBits;
		NewImm = pMobile->Immune;
		NewRes = pMobile->Resist;
		NewVuln = pMobile->Vuln;
		NewForm = pMobile->Form;
		NewParts = pMobile->Parts;

		pCB = (PTComboBox) GetChild(CBID_RACE);
		RaceList.ForEach(FillBox, pCB);
		SelectCB(pCB, RaceList, pMobile->sRace);

		pE = (PTEdit) GetChild(EID_HITBONUS);
		pE->LimitText(6);
		SetDlgItemInt(hWindow, EID_HITBONUS, pMobile->nHitBonus, TRUE);

		sprintf(sz, "%dd%d+%d", pMobile->HP.nNum, pMobile->HP.nType, pMobile->HP.nBase);
		GetChild(PBID_HP)->SetText(sz);

		sprintf(sz, "%dd%d+%d", pMobile->Mana.nNum, pMobile->Mana.nType, pMobile->Mana.nBase);
		GetChild(PBID_MANA)->SetText(sz);

		sprintf(sz, "%dd%d+%d", pMobile->Damage.nNum, pMobile->Damage.nType, pMobile->Damage.nBase);
		GetChild(PBID_DAMAGE)->SetText(sz);

		pCB = (PTComboBox) GetChild(CBID_DAMTYPE);
		DamTypeList.ForEach(FillBox, pCB);
		SelectCB(pCB, DamTypeList, pMobile->nDamType);

		sprintf(sz, "P:%d  B:%d  S:%d  M:%d", pMobile->AC.nPierce, pMobile->AC.nBash,
		 pMobile->AC.nSlash, pMobile->AC.nMagic);
		GetChild(PBID_AC)->SetText(sz);

		pCB = (PTComboBox) GetChild(CBID_SIZE);
		SizeList.ForEach(FillBox, pCB);
		sprintf(sz, "%c", pMobile->cSize);
		SelectCB(pCB, SizeList, sz);

		pCB = (PTComboBox) GetChild(CBID_MATERIAL);
		MaterialList.ForEach(FillBox, pCB);
		if (!pMobile->sMaterial.Len())
			pCB->SetSelIndex(0);
        else
			SelectCB(pCB, MaterialList, pMobile->sMaterial);
	}
	    
	return 0;
}	//TMobAttrDlg::InitDialog