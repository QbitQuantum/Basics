bool MPDUser::isRunning()
{
    #ifdef Q_OS_WIN
    return false;
    #else
    int pid=getPid();
    return pid ? 0==::kill(pid, 0) : false;
    #endif
}