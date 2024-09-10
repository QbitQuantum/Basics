// Send saved console adds to the actual gui window
void CConsole::FlushPendingAdd ( void )
{
    if ( !m_strPendingAdd.empty () )
    {
        // Grab the scroll and the max scroll
        float fScroll = m_pHistory->GetVerticalScrollPosition ();
        float fMaxScroll = m_pHistory->GetScrollbarDocumentSize () - m_pHistory->GetScrollbarPageSize ();

        // Make new buffer
        SString strBuffer = m_pHistory->GetText ();
        strBuffer += m_strPendingAdd;
        m_strPendingAdd = "";

        // Trim new buffer
        if ( strBuffer.length () > CONSOLE_SIZE )
        {
            strBuffer = strBuffer.Right ( CONSOLE_SIZE );
            strBuffer = strBuffer.SplitRight ( "\n" );
        }

        // Set new buffer
        m_pHistory->SetText ( strBuffer );

        // If not at the end, keep the scrollbar position
        if ( fScroll < fMaxScroll )
            m_pHistory->SetVerticalScrollPosition ( fScroll );
    }
}