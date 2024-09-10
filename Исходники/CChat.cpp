LPCTSTR CChatMember::GetChatName()
{
	ADDTOCALLSTACK("CChatMember::GetChatName");
	CClient *pClient = GetClient();
	if ( pClient )
	{
		if ( !pClient->m_UseNewChatSystem && (g_Cfg.m_iChatFlags & CHATF_CUSTOMNAMES) )
			return pClient->m_pAccount->m_sChatName;

		CChar *pChar = pClient->GetChar();
		if ( pChar )
			return pChar->GetName();
	}
	return "<NA>";
}