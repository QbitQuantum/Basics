AndroidRunnerWorkerBase::AndroidRunnerWorkerBase(RunControl *runControl, const AndroidRunnable &runnable)
    : m_androidRunnable(runnable)
    , m_adbLogcatProcess(nullptr, deleter)
    , m_psIsAlive(nullptr, deleter)
    , m_logCatRegExp(regExpLogcat)
    , m_gdbServerProcess(nullptr, deleter)
    , m_jdbProcess(nullptr, deleter)

{
    auto runConfig = runControl->runConfiguration();
    auto aspect = runConfig->extraAspect<Debugger::DebuggerRunConfigurationAspect>();
    Core::Id runMode = runControl->runMode();
    const bool debuggingMode = runMode == ProjectExplorer::Constants::DEBUG_RUN_MODE;
    m_useCppDebugger = debuggingMode && aspect->useCppDebugger();
    if (debuggingMode && aspect->useQmlDebugger())
        m_qmlDebugServices = QmlDebug::QmlDebuggerServices;
    else if (runMode == ProjectExplorer::Constants::QML_PROFILER_RUN_MODE)
        m_qmlDebugServices = QmlDebug::QmlProfilerServices;
    else if (runMode == ProjectExplorer::Constants::QML_PREVIEW_RUN_MODE)
        m_qmlDebugServices = QmlDebug::QmlPreviewServices;
    else
        m_qmlDebugServices = QmlDebug::NoQmlDebugServices;
    m_localGdbServerPort = Utils::Port(5039);
    QTC_CHECK(m_localGdbServerPort.isValid());
    if (m_qmlDebugServices != QmlDebug::NoQmlDebugServices) {
        QTcpServer server;
        QTC_ASSERT(server.listen(QHostAddress::LocalHost)
                   || server.listen(QHostAddress::LocalHostIPv6),
                   qDebug() << tr("No free ports available on host for QML debugging."));
        m_qmlServer.setScheme(Utils::urlTcpScheme());
        m_qmlServer.setHost(server.serverAddress().toString());
        m_qmlServer.setPort(server.serverPort());
    }
    m_adb = AndroidConfigurations::currentConfig().adbToolPath().toString();
    m_localJdbServerPort = Utils::Port(5038);
    QTC_CHECK(m_localJdbServerPort.isValid());

    auto target = runConfig->target();
    m_deviceSerialNumber = AndroidManager::deviceSerialNumber(target);
    m_apiLevel = AndroidManager::deviceApiLevel(target);
}