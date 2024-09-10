int wxQtEventLoopBase::DoRun()
{
    int ret;

    // This is placed inside of a loop to take into account nested event loops
    while ( !m_shouldExit )
    {
        // This will print Qt warnins if app already started:
        // "QCoreApplication::exec: The event loop is already running"
        // TODO: check the loopLevel (nested) like in wxGTK
        ret = QCoreApplication::exec();
        // process pending events (if exec was started previously)
        // TODO: use a real new QEventLoop() ?
        QCoreApplication::processEvents();
    }
    OnExit();
    return ret;
}