bool SevenZip::extract()
{
    m_sevenz.setProgram(m_sevenZip);

    QTemporaryFile progress;
    progress.open();

    QStringList args;
    args << "x" << "-y"
         << m_archiveFile
         << m_outputDir
#ifndef Q_OS_MAC
         << "-bsp2";
#else
         ;
#endif

    QStringList env = QProcess::systemEnvironment();
    env << "VDPAU_DRIVER=va_gl";

    m_sevenz.setArguments(args);
    m_sevenz.setStandardErrorFile(progress.fileName());

    qDebug() << m_sevenz.program() << m_sevenz.arguments().join(" ");
    m_sevenz.start();
    m_sevenz.waitForStarted(-1);

#ifdef Q_OS_LINUX
    QProcess::execute(QString("ionice -c3 -p %1").arg(m_sevenz.pid()));
#endif

    m_szpp->setProgressName(progress.fileName());
    m_szpp->start();
    m_sevenz.waitForFinished(-1);
    m_szpp->wait();

    progress.close();
    progress.remove();

    qDebug() << m_sevenz.exitStatus() << m_sevenz.exitCode();

    return (m_sevenz.exitStatus() == QProcess::NormalExit) &&
           (0 == m_sevenz.exitCode());
}