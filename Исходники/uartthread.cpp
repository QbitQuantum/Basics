CUartThread::~CUartThread()
{
    closeport(m_nFD);
}