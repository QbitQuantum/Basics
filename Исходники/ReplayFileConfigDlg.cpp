/**
 * \param bEnable TRUE to enable and FALSE to disable
 *
 * To enable/disable replay UI components
 */
VOID CReplayFileConfigDlg::vEnableReplayComps( BOOL bEnable )
{
    // File Name
    m_omEditReplayFileName.EnableWindow( bEnable );
    // Time Mode
    m_omChkRetainDelay.EnableWindow( bEnable );
    // User Specific Msg Delay
    // Retain Delay is enabled. So Disable this edit control
    if( m_omChkRetainDelay.GetCheck() == TRUE )
    {
        m_omEditMsgDelay.EnableWindow( FALSE );
    }
    else
    {
        m_omEditMsgDelay.EnableWindow( bEnable );
    }

    // Delay Between Cycles
    if( m_nReplayMode == 0 )
    {
        m_omEditCycleDelay.EnableWindow( FALSE );
    }
    else
    {
        m_omEditCycleDelay.EnableWindow( bEnable );
    }
    // Interactive Replay Option
    m_omChkInteractive.EnableWindow( bEnable );
    // Repolay Mode Option buttons
    CWnd* pWnd = NULL;
    // Monoshot
    pWnd = GetDlgItem( IDC_RADIO_REPLAY_MODE_MONO );
    if( pWnd != NULL )
    {
        pWnd->EnableWindow( bEnable );
    }
    // Cyclic
    pWnd = GetDlgItem( IDC_RADIO_REPLAY_MODE_CYCLIC );
    if( pWnd != NULL )
    {
        pWnd->EnableWindow( bEnable );
    }
    // Filter Button
    pWnd = GetDlgItem( IDC_BTN_FILTER );
    if( pWnd != NULL )
    {
        pWnd->EnableWindow( bEnable );
    }
    // Msg Button
    pWnd = GetDlgItem( IDC_COMBO_MSG_TYPE );
    if( pWnd != NULL )
    {
        pWnd->EnableWindow( bEnable );
    }
}