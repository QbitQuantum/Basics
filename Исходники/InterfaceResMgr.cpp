//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::Init
// Description	    :
// Return type      : LTBOOL
// Argument         : ILTClient* pClientDE
// Argument         : CGameClientShell* pClientShell
//////////////////////////////////////////////////////////////////////
LTBOOL CInterfaceResMgr::Init(ILTClient* pClientDE, CGameClientShell* pClientShell)
{
	if (!pClientDE)
	{
        return LTFALSE;
	}

    HSTRING hString;

	// Set the English flag
    hString = g_pLTClient->FormatString(IDS_GAME_LANGUAGE);
    if (hString && _mbsicmp((const unsigned char*)"english", (const unsigned char*)g_pLTClient->GetStringData(hString)) != 0)
    {
        m_bEnglish=LTFALSE;
	}
	else
    {
        m_bEnglish=LTTRUE;
	}
    g_pLTClient->FreeString(hString);
    hString=LTNULL;

	// Load the virtual key codes for yes responses
    hString=g_pLTClient->FormatString(IDS_MENU_VKEY_YES);
	if (hString)
	{
        m_nYesVKeyCode=atoi(g_pLTClient->GetStringData(hString));
        g_pLTClient->FreeString(hString);
        hString=LTNULL;
	}

	// Load the virtual key codes for no responses
    hString=g_pLTClient->FormatString(IDS_MENU_VKEY_NO);
	if (hString)
	{
        m_nNoVKeyCode=atoi(g_pLTClient->GetStringData(hString));
        g_pLTClient->FreeString(hString);
        hString=LTNULL;
	}

	// Init the InterfaceSurfMgr class
    m_InterfaceSurfMgr.Init(g_pLTClient);

	// set resolution dependant variables
	ScreenDimsChanged();


	// Initialize the fonts
    if (!InitFonts())
	{
        return LTFALSE;
	}

    return LTTRUE;
}