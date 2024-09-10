ProcessHandler::ProcessHandler(const QString & projectPath,
                               const NodePtr& writer)
    : _process(new QProcess)
    , _writer(writer)
    , _ipcServer(0)
    , _bgProcessOutputSocket(0)
    , _bgProcessInputSocket(0)
    , _earlyCancel(false)
    , _processLog()
    , _processArgs()
{
    ///setup the server used to listen the output of the background process
    _ipcServer = new QLocalServer();
    QObject::connect( _ipcServer, SIGNAL(newConnection()), this, SLOT(onNewConnectionPending()) );
    QString tmpFileName;
#if defined(Q_OS_WIN)
    tmpFileName += QString::fromUtf8("//./pipe");
    tmpFileName += QLatin1Char('/');
    tmpFileName += QString::fromUtf8(NATRON_APPLICATION_NAME);
    tmpFileName += QString::fromUtf8("_INPUT_SOCKET");
#endif

    {
#if defined(Q_OS_UNIX)
        QTemporaryFile tmpf(tmpFileName);
        tmpf.open();
        tmpFileName = tmpf.fileName();
        tmpf.remove();
#else
        QTemporaryFile tmpf;
        tmpf.open();
        QString tmpFilePath = tmpf.fileName();
        QString baseName;
        int lastSlash = tmpFilePath.lastIndexOf( QLatin1Char('/') );
        if ( (lastSlash != -1) && (lastSlash < tmpFilePath.size() - 1) ) {
            baseName = tmpFilePath.mid(lastSlash + 1);
        } else {
            baseName = tmpFilePath;
        }
        tmpFileName += baseName;
        tmpf.remove();
#endif
    }
    _ipcServer->listen(tmpFileName);


    _processArgs << QString::fromUtf8("-b") << QString::fromUtf8("-w") << QString::fromUtf8( writer->getScriptName_mt_safe().c_str() );
    _processArgs << QString::fromUtf8("--IPCpipe") <<  tmpFileName;
    _processArgs << projectPath;

    ///connect the useful slots of the process
    QObject::connect( _process, SIGNAL(readyReadStandardOutput()), this, SLOT(onStandardOutputBytesWritten()) );
    QObject::connect( _process, SIGNAL(readyReadStandardError()), this, SLOT(onStandardErrorBytesWritten()) );
    QObject::connect( _process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)) );
    QObject::connect( _process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onProcessEnd(int,QProcess::ExitStatus)) );


    ///start the process
    _processLog.push_back( tr("Starting background rendering: %1 %2")
                           .arg( QCoreApplication::applicationFilePath() )
                           .arg( _processArgs.join( QString::fromUtf8(" ") ) ) );
}