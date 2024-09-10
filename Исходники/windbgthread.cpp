void WinDbgThread::pauseProcess()
{
    if (m_state == ProcessRunning)
        DebugBreakProcess(m_pi.hProcess);
}