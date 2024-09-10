int HttpLog::setErrorLogFile(const char *pFileName)
{
    Appender *appender
        = Appender::getAppender(pFileName, "appender.ps");
    if (appender)
    {
        Appender *pOld = logger()->getAppender();
        if ((pOld) && (pOld != appender))
            pOld->close();
        Layout *layout = Layout::getLayout(ERROR_LOG_PATTERN, "layout.pattern");
        appender->setLayout(layout);
        logger()->setAppender(appender);
        return 0;
    }
    else
        return LS_FAIL;
}