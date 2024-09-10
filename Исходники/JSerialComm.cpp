void JSerialComm::Close()
{
    if( !m_bOpen ) {
        return;
    }
    m_cs.Enter();
    ClosePort();
    m_bOpen = false;
    m_cs.Leave();
}