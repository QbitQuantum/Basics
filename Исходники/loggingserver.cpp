/// \brief LoggerBase deconstructor.  Removes the logger instance from the
///        loggerMap.
LoggerBase::~LoggerBase()
{
    QMutexLocker locker(&loggerMapMutex);
    loggerMap.remove(QString(m_handle));

    if (m_handle)
        free(m_handle);
}