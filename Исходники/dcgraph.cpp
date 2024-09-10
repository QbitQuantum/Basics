void wxGCDC::DoDrawText(const wxString& str, wxCoord x, wxCoord y)
{
    wxCHECK_RET( Ok(), wxT("wxGCDC(cg)::DoDrawRotatedText - invalid DC") );

    if ( str.length() == 0 )
        return;

    if ( !m_logicalFunctionSupported )
        return;

    if ( m_backgroundMode == wxTRANSPARENT )
        m_graphicContext->DrawText( str, x ,y);
    else
        m_graphicContext->DrawText( str, x ,y , m_graphicContext->CreateBrush( wxBrush(m_textBackgroundColour,wxSOLID) ) );
}