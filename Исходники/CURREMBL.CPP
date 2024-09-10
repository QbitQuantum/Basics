BOOL CCurrEmblem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRButton* rbutton;
	rbutton=GETDLGITEM(IDC_NOSEART0);
	CRStatic* s =   GETDLGITEM(IDC_RSTATICCTRL24);
	
	if (DPlay::H2H_Player[_DPlay.mySlot].squadron < PT_GER_FLYABLE)
	{
		rbutton->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_SHOW);
//DEADCODE AMM 17/01/00 		int decal = DPlay::H2H_Player[_DPlay.mySlot].decal;
		int decal=0;
		assert (decal>=0 && decal<32)
		if (decal < 16)
			decal = decal + FIL_NOSE_STD_1;
		else
			decal = decal - 16 + FIL_NOSE_USER_1;
  
		rbutton->SetNormalFileNum(decal);
		rbutton->SetPressedFileNum(decal);
	}else