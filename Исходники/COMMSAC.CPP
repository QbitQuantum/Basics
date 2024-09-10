void CCommsDeathMatchAc::OnTextChangedCurrentac(LPCTSTR text, short Xindex) 
{
#ifndef	BOB_DEMO_VER

  	CRCombo* combo;
	combo=GETDLGITEM(IDC_CURRENTAC);
	int index = combo->GetIndex();	
	if	(_DPlay.GameType == DPlay::DEATHMATCH)
	{
		if (index >= PT_BRIT_NONFLY)
			index +=  (PT_GER_FLYABLE-PT_BRIT_NONFLY);
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index;	
	}else if (_DPlay.Side)
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index;	
	else
		DPlay::H2H_Player[_DPlay.mySlot].squadron = index + PT_GER_FLYABLE;	

// dont need this csquick set up when game is launched

//DeadCode AMM 23Oct00 	CSQuick1::quickdef.UpdateAcType();

//DeadCode JIM 12Jan99 	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//DEADCODE RDH 25/03/99 	FullPanel()->LaunchDial(new CCurrEmblem,1);
	FullPanel()->PaintShopDesc();

#endif
}