void LiteProcess::terminate()
{
    if (m_useCtrlC) {
        Q_PID processId = this->pid();
#ifdef Q_OS_WIN
        if (processId) {
            EnumWindows(sendShutDownMessageToAllWindowsOfProcess_enumWnd, processId->dwProcessId);
        }
#else
        if (processId > 0) {
            ::kill(processId,SIGINT);
        }
#endif
    } else {
        QProcess::terminate();
    }
}