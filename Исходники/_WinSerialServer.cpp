void CSerialServer::CheckModemStatus(BOOL bUpdateNow)
{
    if (!GetCommModemStatus(m_hComPort, &m_dwModemStatus))
        XDEBUG("GetCommModemStatus Error\r\n");

    // Report status if bUpdateNow is true or status has changed
    if (bUpdateNow || (m_dwModemStatus != m_dwOldModemStatus))
        OnUpdateModemStatus(m_dwModemStatus);

    m_dwOldModemStatus = m_dwModemStatus;
}