//: Dumps the log out using osPrintf
void OsTimeLog::dumpLog() const
{
    UtlString log;

    getLogString(log);

    osPrintf("%s", log.data());
        log.remove(0);
}