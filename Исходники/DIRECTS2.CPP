void CDirects2::Redraw()
{
		char buffer[10];

	CDialog::OnInitDialog();
	CRCombo* combo;
	CREdtBt* b;
	b=GETDLGITEM(IDC_DIRECTIVEBUTTON);
	CRStatic*   s=GETDLGITEM(IDC_RESTING);

	
	int index;
	int string = IDS_L_AIRSUP + CComit_e::This->dir_ctrl.directives[linenum].type;
	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
	{
		b->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_HIDE);
		b->SetCaption(LoadResString(string));
	}else
	{
		b->ShowWindow(SW_HIDE);
		s->ShowWindow(SW_SHOW);
		s->SetString(LoadResString(string));
	}
	int combosteps;
	combo=GETDLGITEM(IDC_COMBO_STRIKEAC);
	s=GETDLGITEM(IDC_BLANK2);
	if (CComit_e::This->dir_ctrl.directives[linenum].type == SupplyTree::D_AIRSUPERIORITY)
	{
		s->ShowWindow(SW_SHOW);
		combo->ShowWindow(SW_HIDE);
	}else
	{
		combo->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_HIDE);
		combosteps = (CComit_e::This->dir_ctrl.TotalStrikeAc/4)+1;
		if ((combosteps*4-1) < CComit_e::This->dir_ctrl.directives[linenum].strikeac)
			index = combosteps-1;
		else
			index = CComit_e::This->dir_ctrl.directives[linenum].strikeac/4;
		combo->Clear()->MakeNumList(combosteps,0,4)->SetIndex(index);
	}
	combo=GETDLGITEM(IDC_COMBO_FIGHTERAC);
	combosteps = (CComit_e::This->dir_ctrl.TotalFighterAC/4)+1;
	if ((combosteps*4-1) < CComit_e::This->dir_ctrl.directives[linenum].fighterac)
		index = combosteps-1;
	else
		index = CComit_e::This->dir_ctrl.directives[linenum].fighterac/4;
 	combo->Clear()->MakeNumList(combosteps,0,4)->SetIndex(index);


	if (CComit_e::This->dir_ctrl.directives[linenum].type != SupplyTree::D_RESTING)
	{
	 	int x = CComit_e::This->dir_ctrl.directives[linenum].targets;
		_itoa(x,buffer,10);
		CRStatic*   s=GETDLGITEM(IDC_TARGETS);
		s->SetString(buffer);
		x = CComit_e::This->dir_ctrl.directives[linenum].missionsset;
		_itoa(x,buffer,10);
		s=GETDLGITEM(IDC_MISSIONS);
		s->SetString(buffer);
	}else
	{
		CRStatic*   s=GETDLGITEM(IDC_TARGETS);
		s->ShowWindow(SW_HIDE);
		s=GETDLGITEM(IDC_MISSIONS);
		s->ShowWindow(SW_HIDE);

	}

}