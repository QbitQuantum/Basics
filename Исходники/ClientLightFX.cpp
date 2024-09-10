// ----------------------------------------------------------------------- //
//
//	ROUTINE:	ClientLightFX::HandleTrigger()
//
//	PURPOSE:	Called when triggered.
//
// ----------------------------------------------------------------------- //
void ClientLightFX::HandleTrigger( HOBJECT hSender, HMESSAGEREAD hRead )
{
	HSTRING hMsg = g_pServerDE->ReadFromMessageHString(hRead);
	char *pszMessage = g_pServerDE->GetStringData( hMsg );

	DDWORD dwUsrFlags = g_pServerDE->GetObjectUserFlags(m_hObject);

    if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"TOGGLE", 6) == 0)
    {
		// Toggle the flag
		if (dwUsrFlags & USRFLG_VISIBLE)
			dwUsrFlags &= ~USRFLG_VISIBLE;
		else
			dwUsrFlags |= USRFLG_VISIBLE;
		m_bOn = !m_bOn;
    } 
    else if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"ON", 2) == 0)
    {
		dwUsrFlags |= USRFLG_VISIBLE;
		m_bOn = DTRUE;
    }            
    else if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"OFF", 3) == 0)
    {
		dwUsrFlags &= ~USRFLG_VISIBLE;
		m_bOn = DFALSE;
    }        
    
	g_pServerDE->SetObjectUserFlags(m_hObject, dwUsrFlags);

	g_pServerDE->FreeString( hMsg );
}