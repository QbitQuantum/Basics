void CClientWarpGateSFX::HandleTrigger(HOBJECT hSender, HMESSAGEREAD hRead)
{
	HSTRING hMsg = g_pServerDE->ReadFromMessageHString(hRead);
	char *pszMessage = g_pServerDE->GetStringData(hMsg);
	DDWORD dwUsrFlags = g_pServerDE->GetObjectUserFlags(m_hObject);

    if( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"TOGGLE", 6) == 0)
		bOn = !bOn;
    else if( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"ON", 2) == 0)
		bOn = DTRUE;
    else if( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"OFF", 3) == 0)
		bOn = DFALSE;
    
	g_pServerDE->SetObjectUserFlags(m_hObject, dwUsrFlags);
	g_pServerDE->FreeString(hMsg);
}