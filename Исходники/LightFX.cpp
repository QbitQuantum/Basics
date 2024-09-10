// ----------------------------------------------------------------------- //
//
//	ROUTINE:	LightFX::HandleTrigger()
//
//	PURPOSE:	Called when triggered.
//
// ----------------------------------------------------------------------- //
void LightFX::HandleTrigger( HOBJECT hSender, HMESSAGEREAD hRead )
{
	HSTRING hMsg = g_pServerDE->ReadFromMessageHString(hRead);
	char *pszMessage = g_pServerDE->GetStringData( hMsg );

    if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"SWITCH", 6) == 0)
    {
        ToggleLight();
    } 
    else if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"ON", 2) == 0)
    {
        TurnOn();
    }            
    else if ( _mbsncmp((const unsigned char*)pszMessage, (const unsigned char*)"OFF", 3) == 0)
    {
	    TurnOff();
    }        
    
	g_pServerDE->FreeString( hMsg );
}