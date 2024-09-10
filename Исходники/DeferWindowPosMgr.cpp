/** 
 * 
 * Calls EndDeferWindowPos.
 * 
 * @param       Nil
 * @return      bool - Returns execution status.
 * @exception   Nil
 * @see         Begin
 * @since       1.0
 */
bool DeferWindowPosMgr::End()
{
    BOOL bResult = FALSE;
    if( m_hdwp )
    {
        bResult = EndDeferWindowPos( m_hdwp );
        m_hdwp = 0;
    }

    // If redraw is enabled then enable drawing.
    IsRedrawEnabled() && m_hRedrawWindow && ::SendMessage( m_hRedrawWindow, WM_SETREDRAW, TRUE, 0 );

    // Return status
    return bResult != FALSE;
}// End