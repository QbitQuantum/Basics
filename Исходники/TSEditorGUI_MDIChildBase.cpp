/*******************************************************************************
  Function Name  : vSaveWinStatus
  Input(s)       : -
  Output         : -
  Functionality  : This function will get window postion and will save it in to
                   the configuration module if it is different from the
                   previously saved value
  Member of      : CMDIChildBase
  Author(s)      : Raja N
  Date Created   : 18.4.2005
  Modifications  : 
*******************************************************************************/
void CMDIChildBase::vSaveWinStatus()
{
    // Use temp structure for comparission
    WINDOWPLACEMENT sCurrentPlacement;
    // Get current window postion
    GetWindowPlacement(&sCurrentPlacement);
    // Set the flag
    sCurrentPlacement.flags |= WPF_SETMINPOSITION;
    // Check for difference
    if( memcmp( &sCurrentPlacement,
                &m_sWindowPlacement,
                sizeof(WINDOWPLACEMENT)) != 0 )
    {
        // Update memeber value
        m_sWindowPlacement = sCurrentPlacement;
        // Set flag to restore minimised postion also
        m_sWindowPlacement.flags |= WPF_SETMINPOSITION;
    }
}