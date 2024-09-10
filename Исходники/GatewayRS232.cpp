//********************************************************************
BOOL CGatewayRS232ToWin32::OpenPort(CStdString strPortName, CErrorInfo* pErrorInfo)
{
    const int k_MaxPortNameSize = 20;
    const BOOL k_oChangeOnly = FALSE;

	if( !m_Rs232Hndl.OpenPort(strPortName) )
	{
		if(m_pErrorHandling) m_pErrorHandling->GetError(k_Error_I_OpeningPort, pErrorInfo);
        return FALSE;
	}

	//Configure default settings for port
    if(!SetPortSettings(m_dBaudrate, m_dTimeout, k_oChangeOnly, pErrorInfo))
    {
        ClosePort();
        return FALSE;
    }

    return TRUE;
}