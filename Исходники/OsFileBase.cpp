OsStatus OsFileBase::readLine(UtlString &str)
{
#ifdef DEBUG_FS
   pthread_t nTaskId = 0;
   OsTask* pTask = OsTask::getCurrentTask();
   if (pTask) pTask->id(nTaskId);
   Os::Logger::instance().log(FAC_KERNEL, PRI_DEBUG, "OsFileBase::readLine ENTER threadid=%ld\n", nTaskId);
#endif
    char buf[2];
    size_t bytesRead;
    OsStatus retstat = OS_INVALID;

    buf[1] = '\0';
    str.remove(0);
    do
    {
        retstat = read(buf, 1, bytesRead);

        if (retstat == OS_SUCCESS && (*buf != '\n' && *buf != '\r'))
        {
            str.append(buf, 1);
        }

    } while (retstat == OS_SUCCESS && bytesRead == 1 && *buf != '\n');


#ifdef DEBUG_FS
   Os::Logger::instance().log(FAC_KERNEL, PRI_DEBUG, "OsFileBase::readLine EXIT threadid=%ld\n", nTaskId);
#endif

   return retstat;
}