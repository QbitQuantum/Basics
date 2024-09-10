bool Progress::onProgress(ngsCode status, double complete,
                          const char *format, ...) const
{
    if(nullptr == m_progressFunc) {
        return true; // No cancel from user
    }
    va_list args;
    CPLString message;
    va_start( args, format );
    message.vPrintf( format, args );
    va_end( args );

    double newComplete = complete / m_totalSteps + 1.0 / m_totalSteps * m_step;
    if(status == COD_FINISHED && newComplete < 1.0) {
        status = COD_IN_PROCESS;
    }
    return m_progressFunc(status, newComplete, message, m_progressArguments) == 1;
}