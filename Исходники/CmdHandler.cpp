CCmdHandler::~CCmdHandler()
{
#ifdef USE_TCP_NOT_SERIAL
    StopWork();
#else
    ClosePort();
#endif
    SAFEDELETEP(m_pRecvBuffer);
}