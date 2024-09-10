void AndroidRunner::asyncStart()
{
    QMutexLocker locker(&m_mutex);
    forceStop();

    if (m_useCppDebugger) {
        // Remove pong file.
        QProcess adb;
        adb.start(m_adb, selector() << _("shell") << _("rm") << m_pongFile);
        adb.waitForFinished();
    }

    QStringList args = selector();
    args << _("shell") << _("am") << _("start") << _("-n") << m_intentName;

    if (m_useCppDebugger) {
        QProcess adb;
        adb.start(m_adb, selector() << _("forward")
                  << QString::fromLatin1("tcp:%1").arg(m_localGdbServerPort)
                  << _("localfilesystem:") + m_gdbserverSocket);
        if (!adb.waitForStarted()) {
            emit remoteProcessFinished(tr("Failed to forward C++ debugging ports. Reason: %1.").arg(adb.errorString()));
            return;
        }
        if (!adb.waitForFinished(5000)) {
            emit remoteProcessFinished(tr("Failed to forward C++ debugging ports."));
            return;
        }

        args << _("-e") << _("debug_ping") << _("true");
        args << _("-e") << _("ping_file") << m_pingFile;
        args << _("-e") << _("pong_file") << m_pongFile;
        args << _("-e") << _("gdbserver_command") << m_gdbserverCommand;
        args << _("-e") << _("gdbserver_socket") << m_gdbserverSocket;
    }

    if (m_useQmlDebugger || m_useQmlProfiler) {
        // currently forward to same port on device and host
        const QString port = QString::fromLatin1("tcp:%1").arg(m_qmlPort);
        QProcess adb;
        adb.start(m_adb, selector() << _("forward") << port << port);
        if (!adb.waitForStarted()) {
            emit remoteProcessFinished(tr("Failed to forward QML debugging ports. Reason: %1.").arg(adb.errorString()));
            return;
        }
        if (!adb.waitForFinished()) {
            emit remoteProcessFinished(tr("Failed to forward QML debugging ports."));
            return;
        }
        args << _("-e") << _("qml_debug") << _("true");
        args << _("-e") << _("qmljsdebugger") << QString::fromLatin1("port:%1,block").arg(m_qmlPort);
    }
    if (m_useLocalQtLibs) {
        args << _("-e") << _("use_local_qt_libs") << _("true");
        args << _("-e") << _("libs_prefix") << _("/data/local/tmp/qt/");
        args << _("-e") << _("load_local_libs") << m_localLibs;
        args << _("-e") << _("load_local_jars") << m_localJars;
        if (!m_localJarsInitClasses.isEmpty())
            args << _("-e") << _("static_init_classes") << m_localJarsInitClasses;
    }

    QProcess adb;
    adb.start(m_adb, args);
    if (!adb.waitForStarted()) {
        emit remoteProcessFinished(tr("Failed to start the activity. Reason: %1.").arg(adb.errorString()));
        return;
    }
    if (!adb.waitForFinished(5000)) {
        adb.terminate();
        emit remoteProcessFinished(tr("Unable to start '%1'.").arg(m_packageName));
        return;
    }

    if (m_useCppDebugger) {

        // Handling ping.
        for (int i = 0; ; ++i) {
            QTemporaryFile tmp(_("pingpong"));
            tmp.open();
            tmp.close();

            QProcess process;
            process.start(m_adb, selector() << _("pull") << m_pingFile << tmp.fileName());
            process.waitForFinished();

            QFile res(tmp.fileName());
            const bool doBreak = res.size();
            res.remove();
            if (doBreak)
                break;

            if (i == 20) {
                emit remoteProcessFinished(tr("Unable to start '%1'.").arg(m_packageName));
                return;
            }
            qDebug() << "WAITING FOR " << tmp.fileName();
            QThread::msleep(500);
        }

    }

    m_tries = 0;
    m_wasStarted = false;
    QMetaObject::invokeMethod(&m_checkPIDTimer, "start");
}