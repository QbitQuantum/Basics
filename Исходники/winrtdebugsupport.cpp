RunControl *WinRtDebugSupport::createDebugRunControl(WinRtRunConfiguration *runConfig,
                                                     RunMode mode,
                                                     QString *errorMessage)
{
    // FIXME: This is just working for local debugging;
    using namespace Debugger;
    DebuggerStartParameters params;
    params.startMode = AttachExternal;
    params.languages |= CppLanguage;
    params.breakOnMain = mode == DebugRunModeWithBreakOnMain;
    // The first Thread needs to be resumed manually.
    params.commandsAfterConnect = "~0 m";
    Kit *kit = runConfig->target()->kit();
    params.debuggerCommand = DebuggerKitInformation::debuggerCommand(kit).toString();
    if (ToolChain *tc = ToolChainKitInformation::toolChain(kit))
        params.toolChainAbi = tc->targetAbi();

    QFileInfo debuggerHelper(QCoreApplication::applicationDirPath()
                             + QLatin1String("/winrtdebughelper.exe"));
    if (!debuggerHelper.isExecutable()) {
        *errorMessage = tr("The WinRT debugging helper is missing from your Qt Creator "
                           "installation. It was assumed to be located at %1").arg(
                    debuggerHelper.absoluteFilePath());
        return 0;
    }

    WinRtRunnerHelper *runner = new WinRtRunnerHelper(runConfig, errorMessage);
    if (!errorMessage->isEmpty())
        return 0;

    QLocalServer server;
    server.listen(QLatin1String("QtCreatorWinRtDebugPIDPipe"));

    runner->debug(debuggerHelper.absoluteFilePath());
    if (!runner->waitForStarted()) {
        *errorMessage = tr("Cannot start the WinRT Runner Tool.");
        return 0;
    }

    if (!server.waitForNewConnection(10000)) {
        *errorMessage = tr("Cannot establish connection to the WinRT debugging helper.");
        return 0;
    }

    while (server.hasPendingConnections()) {
        QLocalSocket *connection = server.nextPendingConnection();
        if (connection->waitForReadyRead(1000)) {
            const QByteArray &output = connection->readAll();
            QList<QByteArray> arg = output.split(':');
            if (arg.first() == "PID") {
                bool ok =false;
                params.attachPID = arg.last().toInt(&ok);
                if (!ok) {
                    *errorMessage = tr("Cannot extract the PID from the WinRT debugging helper. "
                                       "(output: %1)").arg(QString::fromLocal8Bit(output));
                    return 0;
                }
                server.close();
                params.runConfiguration = runConfig;
                Debugger::DebuggerRunControl *debugRunControl
                        = createDebuggerRunControl(params, errorMessage);
                runner->setRunControl(debugRunControl);
                new WinRtDebugSupport(debugRunControl, runner);
                return debugRunControl;
            }
        }
    }

    server.close();

    *errorMessage = tr("Cannot create an appropriate run control for "
                       "the current run configuration.");

    return 0;
}