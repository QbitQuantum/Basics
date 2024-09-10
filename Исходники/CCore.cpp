void CCore::DebugEchoColor ( const char* szText, unsigned char R, unsigned char G, unsigned char B )
{
    // Set the color
    CDebugView * pDebugView = m_pLocalGUI->GetDebugView ();
    if ( pDebugView )
    {
        pDebugView->SetTextColor ( CColor ( R, G, B, 255 ) );
    }

    m_pLocalGUI->EchoDebug ( szText );
}