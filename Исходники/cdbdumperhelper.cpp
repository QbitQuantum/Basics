void CdbDumperHelper::moduleLoadHook(const QString &module, HANDLE debuggeeHandle)
{
    if (loadDebug > 1)
        qDebug() << "moduleLoadHook" << module << m_state << debuggeeHandle;
    switch (m_state) {
    case Disabled:
    case Initialized:
        break;
    case NotLoaded:
        // Try an inject load as soon as a Qt lib is loaded.
        // for the thread to finish as this would lock up.
        if (m_tryInjectLoad && module.contains(QLatin1String("Qt"), Qt::CaseInsensitive)) {
            // Also shows up in the log window.
            m_manager->showStatusMessage(msgLoading(m_library, true), messageTimeOut);
            QString errorMessage;
            SharedLibraryInjector sh(GetProcessId(debuggeeHandle));
            if (sh.remoteInject(m_library, false, &errorMessage)) {
                m_state = InjectLoading;
            } else {
                m_state = InjectLoadFailed;
                // Ok, try call loading...
                m_manager->showDebuggerOutput(LogMisc, msgLoadFailed(m_library, true, errorMessage));
            }
        }
        break;
    case InjectLoading:
        // check if gdbmacros.dll loaded
        if (module.contains(QLatin1String(dumperModuleNameC), Qt::CaseInsensitive)) {
            m_state = Loaded;
            m_manager->showDebuggerOutput(LogMisc, msgLoadSucceeded(m_library, true));
        }
        break;
    }
}