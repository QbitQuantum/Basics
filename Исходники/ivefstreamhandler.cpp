void IVEFStreamHandler::connectToServer(QString host, int port, QString user, QString password, QString logFileName, bool slipstream, bool statistics) {


    QString portString;
    portString.setNum(port);
    std::cout << QString("iListen opening connection to %1:%2").arg(host, portString).toLatin1().data() << std::endl;

    // should we use keep track of line load
    m_statistics = statistics;

    // should we use compression
    m_slipstream = slipstream;

    // setup the socket
    m_tcpSocket->connectToHost(host, port);

    // store some info for the login
    m_user = user;
    m_password = password;

#ifdef HAVE_ZLIB
    // setup decompression mechanism
    // we cannot use Qt for decompression since we do not know where the chunk starts or ends.
    if ( m_slipstream ) {
        m_strm.zalloc = Z_NULL;
        m_strm.zfree = Z_NULL;
        m_strm.opaque = Z_NULL;
        m_strm.avail_in = 0;
        m_strm.next_in = Z_NULL;
        if (inflateInit(&m_strm) != Z_OK) {
            std::cout << "iListen error initiating zlib stream" << std::endl;
        }
    }
#endif

    // set a timer to check the bytes in/out every minte
    if ( m_statistics ) {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(slotStatisticsTimerFired()));
        timer->start(TIMER_INTERVAL*1000);
    }

    // setup the logstream if needed
    if (logFileName != "") {
        QFile* file = new QFile(logFileName);
        file->setParent(this); // make sure it gets cleaned up

        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << QString("iListen error opening file: %1 for writing").arg(logFileName).toLatin1().data() << std::endl;
            std::exit(1);
        }

        m_log = new QTextStream(file);
        m_log->setCodec("UTF-8");
        *m_log << "<xml>\n"; // create a start tag
        m_log->flush();
    } else {
        m_log = NULL;
    }
}