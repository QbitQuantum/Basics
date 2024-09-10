QmlProfilerApplication::QmlProfilerApplication(int &argc, char **argv) :
    QCoreApplication(argc, argv),
    m_runMode(LaunchMode),
    m_process(0),
    m_tracePrefix(QLatin1String("trace")),
    m_hostName(QLatin1String("127.0.0.1")),
    m_port(3768),
    m_verbose(false),
    m_quitAfterSave(false),
    m_qmlProfilerClient(&m_connection),
    m_v8profilerClient(&m_connection),
    m_connectionAttempts(0),
    m_qmlDataReady(false),
    m_v8DataReady(false)
{
    m_connectTimer.setInterval(1000);
    connect(&m_connectTimer, SIGNAL(timeout()), this, SLOT(tryToConnect()));

    connect(&m_connection, SIGNAL(connected()), this, SLOT(connected()));
    connect(&m_connection, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(connectionStateChanged(QAbstractSocket::SocketState)));
    connect(&m_connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionError(QAbstractSocket::SocketError)));

    connect(&m_qmlProfilerClient, SIGNAL(enabledChanged()), this, SLOT(traceClientEnabled()));
    connect(&m_qmlProfilerClient, SIGNAL(recordingChanged(bool)), this, SLOT(recordingChanged()));
    connect(&m_qmlProfilerClient, SIGNAL(range(QQmlProfilerService::RangeType,QQmlProfilerService::BindingType,qint64,qint64,QStringList,QmlEventLocation)),
            &m_profilerData, SLOT(addQmlEvent(QQmlProfilerService::RangeType,QQmlProfilerService::BindingType,qint64,qint64,QStringList,QmlEventLocation)));
    connect(&m_qmlProfilerClient, SIGNAL(traceFinished(qint64)), &m_profilerData, SLOT(setTraceEndTime(qint64)));
    connect(&m_qmlProfilerClient, SIGNAL(traceStarted(qint64)), &m_profilerData, SLOT(setTraceStartTime(qint64)));
    connect(&m_qmlProfilerClient, SIGNAL(frame(qint64,int,int)), &m_profilerData, SLOT(addFrameEvent(qint64,int,int)));
    connect(&m_qmlProfilerClient, SIGNAL(complete()), this, SLOT(qmlComplete()));

    connect(&m_v8profilerClient, SIGNAL(enabledChanged()), this, SLOT(profilerClientEnabled()));
    connect(&m_v8profilerClient, SIGNAL(range(int,QString,QString,int,double,double)),
            &m_profilerData, SLOT(addV8Event(int,QString,QString,int,double,double)));
    connect(&m_v8profilerClient, SIGNAL(complete()), this, SLOT(v8Complete()));

    connect(&m_profilerData, SIGNAL(error(QString)), this, SLOT(logError(QString)));
    connect(&m_profilerData, SIGNAL(dataReady()), this, SLOT(traceFinished()));

}