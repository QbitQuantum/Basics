void CIrcChannelTabCtrl::OnContextMenu(CWnd*, CPoint point)
{
    int iCurTab = GetTabUnderMouse(point);
    if (iCurTab < 2)
    {
        return;
    }
    TCITEM item;
    item.mask = TCIF_PARAM;
    GetItem(iCurTab, &item);

    Channel* pChan = FindChannelByName(((Channel*)item.lParam)->m_sName);
    if( !pChan )
    {
        return;
    }

    CTitleMenu menuChat;
    menuChat.CreatePopupMenu();
    menuChat.AddMenuTitle(GetResString(IDS_IRC)+_T(" : ")+pChan->m_sName);
    menuChat.AppendMenu(MF_STRING, Irc_Close, GetResString(IDS_FD_CLOSE));
    if (iCurTab < 2) // no 'Close' for status log and channel list
        menuChat.EnableMenuItem(Irc_Close, MF_GRAYED);

    int iCurIndex = 0;
    int iLength = m_sChannelModeSettingsTypeA.GetLength();
    CString sMode;
    for( int iIndex = 0; iIndex < iLength; iIndex++)
    {
        sMode = m_sChannelModeSettingsTypeA.Mid(iIndex,1);
        if( pChan->m_sModesA.Find(sMode) == -1 )
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex, _T("ModeA Set +") + sMode + _T(" ( Not Supported Yet )") );
            menuChat.EnableMenuItem(Irc_ChanCommands+iCurIndex, MF_GRAYED);
        }
        else
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex+50, _T("ModeA Set -") + sMode + _T(" ( Not Supported Yet )") );
            menuChat.EnableMenuItem(Irc_ChanCommands+iCurIndex+50, MF_GRAYED);
        }
        iCurIndex++;
    }
    iLength = m_sChannelModeSettingsTypeB.GetLength();
    for( int iIndex = 0; iIndex < iLength; iIndex++)
    {
        sMode = m_sChannelModeSettingsTypeB.Mid(iIndex,1);
        if( pChan->m_sModesB.Find(sMode) == -1 )
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex, _T("ModeB Set +") + sMode + _T(" ( Not Supported Yet )") );
            menuChat.EnableMenuItem(Irc_ChanCommands+iCurIndex, MF_GRAYED);
        }
        else
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex+50, _T("ModeB Set -") + sMode + _T(" ( Not Supported Yet )") );
            menuChat.EnableMenuItem(Irc_ChanCommands+iCurIndex+50, MF_GRAYED);
        }
        iCurIndex++;
    }
    iLength = m_sChannelModeSettingsTypeC.GetLength();
    for( int iIndex = 0; iIndex < iLength; iIndex++)
    {
        sMode = m_sChannelModeSettingsTypeC.Mid(iIndex,1);
        if( pChan->m_sModesC.Find(sMode) == -1 )
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex, _T("ModeC Set +") + sMode + _T(" ( Not Supported Yet )") );
            menuChat.EnableMenuItem(Irc_ChanCommands+iCurIndex, MF_GRAYED);
        }
        else
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex+50, _T("ModeC Set -") + sMode + _T(" ( Remove ") + sMode + _T(" )") );
        }
        iCurIndex++;
    }
    iLength = m_sChannelModeSettingsTypeD.GetLength();
    for( int iIndex = 0; iIndex < iLength; iIndex++)
    {
        sMode = m_sChannelModeSettingsTypeD.Mid(iIndex,1);
        if( pChan->m_sModesD.Find(sMode) == -1 )
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex, _T("ModeD Set +") + sMode + _T(" ( Add ") + sMode + _T(" )") );
        }
        else
        {
            menuChat.AppendMenu(MF_STRING, Irc_ChanCommands+iCurIndex+50, _T("ModeD Set -") + sMode + _T(" ( Remove ") + sMode + _T(" )") );
        }
        iCurIndex++;
    }

    menuChat.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
    VERIFY( menuChat.DestroyMenu() );
}