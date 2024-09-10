CClientNotificationSink::~CClientNotificationSink()
{
    DeleteCriticalSection( &m_printfCriticalSection );
}