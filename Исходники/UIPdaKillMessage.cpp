float CUIPdaKillMessage::InitText(CUIStatic& refStatic, float x, PlayerInfo& info)
{

	if ( 0 == xr_strlen(info.m_name))
		return 0.0f;

	CGameFont* pFont					= GetFont();
	float _eps							= pFont->SizeOf_(' ');
	UI()->ClientToScreenScaledWidth		(_eps); //add one letter

	float height						= pFont->CurrentHeight_();
	float y								= (GetHeight() - height)/2;

	refStatic.SetWndPos					(Fvector2().set(x, y));
	refStatic.SetHeight					(GetHeight());
	refStatic.SetEllipsis				(1, 0);
	refStatic.SetText					(info.m_name.c_str());
	refStatic.AdjustWidthToText			();
	refStatic.SetWidth					(refStatic.GetWidth()+_eps);
	refStatic.SetTextColor				(info.m_color);

	return		refStatic.GetWidth		();
}