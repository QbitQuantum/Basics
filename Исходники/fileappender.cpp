    bool FileAppender::renameFile(QFile &rFile,
                                  const QString &rFileName) const
	{
        logger()->debug("Renaming file '%1' to '%2'", rFile.fileName(), rFileName);
        if (rFile.rename(rFileName))
        	return true;
        
        LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Unable to rename file '%1' to '%2' for appender '%3'"),
                                         APPENDER_RENAMING_FILE_ERROR);
        e << rFile.fileName() << rFileName << name();
        e.addCausingError(LogError(rFile.errorString(), rFile.error()));
        logger()->error(e);
        return false;
    }