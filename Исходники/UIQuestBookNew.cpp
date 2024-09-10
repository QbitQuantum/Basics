void CUIQuestBook::GiveUpPress()
{
	if (m_nSelectQuestIdx <= 0)
		return;

	CQuestStaticData* pQuestDD = CQuestStaticData::getData(m_nSelectQuestIdx);
	if (pQuestDD == NULL)
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->CloseMessageBox(MSGCMD_QUEST_GIVEUP);
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;	
	MsgBoxInfo.SetMsgBoxInfo( _S( 99, "퀘스트" ), UMBS_OKCANCEL, UI_QUESTBOOK_LIST, MSGCMD_QUEST_GIVEUP);	
	strMessage.PrintF( "%s", pQuestDD->GetTitle() );
	MsgBoxInfo.AddString( strMessage );
	strMessage.PrintF( _S( 7002, "퀘스트를 포기 하시겠습니까?" ));
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
	m_bLockQuestList = TRUE;
}