/////////////////////////////////////////////////////////////////////
// 
// Function:    LogProgress
//
// Description: 
//
/////////////////////////////////////////////////////////////////////
UINT BOINCCABase::LogProgress( 
    const tstring strProgress
    )
{
    UINT uiReturnValue = 0;

    MsiRecordSetString(m_phActionDataRec, 2, strProgress.c_str());

    // returns IDOK if successful
    uiReturnValue = MsiProcessMessage( m_hMSIHandle, INSTALLMESSAGE_ACTIONDATA, m_phActionDataRec );
	if ((uiReturnValue == IDCANCEL))
		return ERROR_INSTALL_USEREXIT;

    // Give the UI a chance to refresh.
    Sleep(0);

    return ERROR_SUCCESS;
}