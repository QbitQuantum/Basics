BOOL CCommsPaint::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRButton* rbutton;
	int decals;
	for(int i=0;i<32;i++)
	{ 
		rbutton=GETDLGITEM(IDC_NOSEART0+i);
		if (DPlay::H2H_Player[_DPlay.mySlot].squadron < PT_GER_FLYABLE)
		{
			rbutton->ShowWindow(SW_SHOW);

			if (i < 16)
				decals = i + FIL_NOSE_STD_1;
			else
				decals = i - 16 + FIL_NOSE_USER_1;

 			rbutton->SetNormalFileNum(decals);
			rbutton->SetPressedFileNum(1);
		}else
		{
			rbutton->ShowWindow(SW_HIDE);
		}
	}

	paintshop_timer=SetTimer(DPlay::TIMER_PAINTSHOP,0,NULL); 

//DeadCode AMM 16Nov99 	_DPlay.UISendInPaintShopMessage();
//DeadCode AMM 16Nov99 	DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PAINTSHOP;
	_DPlay.SendStatusChange(DPlay::CPS_PAINTSHOP);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}