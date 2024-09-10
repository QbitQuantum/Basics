void CPipeBase::ClosePipe()
{
    if (m_hPipeClient != INVALID_HANDLE_VALUE)
    {
		DisconnectNamedPipe( m_hPipeClient );
        CloseHandle(m_hPipeClient);
        m_hPipeClient = INVALID_HANDLE_VALUE;
    }

	if (m_hPipeServer != INVALID_HANDLE_VALUE)
    {
		DisconnectNamedPipe( m_hPipeServer );
        CloseHandle(m_hPipeServer);
        m_hPipeServer = INVALID_HANDLE_VALUE;
    }
}