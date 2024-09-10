LldbEngineHost::LldbEngineHost(const DebuggerStartParameters &startParameters)
    :IPCEngineHost(startParameters), m_ssh(0)
{
    showMessage(QLatin1String("setting up coms"));
    setObjectName(QLatin1String("LLDBEngine"));

    if (startParameters.startMode == StartRemoteEngine)
    {
        m_guestProcess = 0;
        QSsh::SshRemoteProcessRunner * const runner = new QSsh::SshRemoteProcessRunner;
        connect (runner, SIGNAL(connectionError(QSsh::SshError)),
                 this, SLOT(sshConnectionError(QSsh::SshError)));
        runner->run(startParameters.serverStartScript.toUtf8(), startParameters.connParams);
        setGuestDevice(new SshIODevice(runner));
    } else  {
        m_guestProcess = new QProcess(this);

        connect(m_guestProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
                this, SLOT(finished(int,QProcess::ExitStatus)));

        connect(m_guestProcess, SIGNAL(readyReadStandardError()), this,
                SLOT(stderrReady()));


        QString a = Core::ICore::resourcePath() + QLatin1String("/qtcreator-lldb");
        if (getenv("QTC_LLDB_GUEST") != 0)
            a = QString::fromLocal8Bit(getenv("QTC_LLDB_GUEST"));

        showStatusMessage(QString(QLatin1String("starting %1")).arg(a));

        m_guestProcess->start(a, QStringList(), QIODevice::ReadWrite | QIODevice::Unbuffered);
        m_guestProcess->setReadChannel(QProcess::StandardOutput);

        if (!m_guestProcess->waitForStarted()) {
            showStatusMessage(tr("qtcreator-lldb failed to start: %1").arg(m_guestProcess->errorString()));
            notifyEngineSpontaneousShutdown();
            return;
        }

        setGuestDevice(m_guestProcess);
    }
}