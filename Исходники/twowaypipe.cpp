// Disconnect server or client side of the pipe.
// true - success, false - failure (use GetLastError() for more details)
bool TwoWayPipe::Disconnect()
{
    if (m_state == ServerConnected)
    {
        DisconnectNamedPipe(m_outboundPipe);
        DisconnectNamedPipe(m_inboundPipe);
        CloseHandle(m_outboundPipe);
        m_outboundPipe = INVALID_HANDLE_VALUE;
        CloseHandle(m_inboundPipe);
        m_inboundPipe = INVALID_HANDLE_VALUE;
        m_state = NotInitialized;
        return true;
    }
    else if (m_state == ClientConnected)
    {
        CloseHandle(m_outboundPipe);
        m_outboundPipe = INVALID_HANDLE_VALUE;
        CloseHandle(m_inboundPipe);
        m_inboundPipe = INVALID_HANDLE_VALUE;
        m_state = NotInitialized;
        return true;
    } 
    else 
    {
        // nothign to do
        return true;
    }
}