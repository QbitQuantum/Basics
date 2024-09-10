void CChatSelector::OnContextMenu(CWnd* pWnd, CPoint point)
{ 
	const CChatItem* ci = GetCurrentChatItem();
	if (!ci)
		return;


	bool  isvalidconclient=false;
	if (ci->client &&  ci->client->HasValidHash())
		isvalidconclient=true;

	CTitleMenu ChatMenu;
	ChatMenu.CreatePopupMenu(); 
	ChatMenu.AddMenuTitle(GetResString(IDS_CW_MESSAGES),true);

	ChatMenu.AppendMenu(MF_STRING | isvalidconclient?MF_ENABLED : MF_GRAYED, MP_DETAIL, GetResString(IDS_SHOWDETAILS),_T("CLIENTDETAILS"));
	ChatMenu.AppendMenu(MF_STRING | (isvalidconclient && !ci->client->IsFriend() )? MF_ENABLED : MF_GRAYED , MP_ADDFRIEND, GetResString(IDS_ADDAFRIEND),_T("ADDFRIEND"));
	ChatMenu.AppendMenu(MF_STRING, MP_REMOVE, GetResString(IDS_FD_CLOSE), _T("DELETE") );

	ChatMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
 	VERIFY( ChatMenu.DestroyMenu() );
	
}