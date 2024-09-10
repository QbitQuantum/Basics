void JohnProcess::terminate()
{
#ifdef Q_OS_UNIX
    if (pid() != 0) {
        /* Send sigterm to all processes of the group
         * created previously with setsid()
         * This is done in Johnny because of a bug in john <= 1.8.0
         * where it didn't forward signals to children and we want to keep
         * compatibility with those versions of John for now */
        ::kill(-pid(), SIGTERM);
    }
#elif defined(Q_OS_WIN)
    Q_PID pid = this->pid();
    FreeConsole();
    AttachConsole(pid->dwProcessId);
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
    FreeConsole();
#else
    QProcess::terminate();
#endif
}