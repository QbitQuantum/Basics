void genLinuxCorefile(const char *eventMsg)
{
  if (eventMsg)
    SQLMXLoggingArea::logExecRtInfo(__FILE__, __LINE__, eventMsg, 0);
  NAProcessHandle myPhandle;
  myPhandle.getmine();
  myPhandle.decompose();

  char coreFile[PATH_MAX];
  msg_mon_dump_process_name(NULL, myPhandle.getPhandleString(),
                              coreFile);

  char coreLocationMessage[PATH_MAX + 200];
  sprintf(coreLocationMessage, 
            "Core-file for this process created at %s.", coreFile);
  SQLMXLoggingArea::logExecRtInfo(__FILE__, __LINE__,
                                    coreLocationMessage, 0);
}