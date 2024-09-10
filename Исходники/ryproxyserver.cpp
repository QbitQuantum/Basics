// private functions
RyConnection * RyProxyServer::_getConnection(int handle){
    //QMutexLocker locker(&connectionOpMutex);
    //Q_UNUSED(locker)
    //QDateTime time = QDateTime::currentDateTime();
    //qDebug()<<"getConnection:"
    //          <<time.toMSecsSinceEpoch();
    //if(!_cacheConnections.contains(handle)){
    //qDebug()<<"_lastConnectionId"<<_lastConnectionId;
    _lastConnectionId++;

    QMutexLocker locker(&connectionOpMutex);
    QThread *newThread = new QThread();
    RyConnection *connection = new RyConnection(handle,_lastConnectionId);
    _connections.append(connection);
    _threads[connection] = newThread;
    locker.unlock();

    connect(connection,SIGNAL(idleTimeout()),SLOT(onConnectionIdleTimeout()));

    connect(connection,SIGNAL(pipeBegin(RyPipeData_ptr)),
            SLOT(onPipeBegin(RyPipeData_ptr)));
    connect(connection,SIGNAL(pipeComplete(RyPipeData_ptr)),
            SLOT(onPipeComplete(RyPipeData_ptr)));
    connect(connection,SIGNAL(pipeError(RyPipeData_ptr)),
            SLOT(onPipeError(RyPipeData_ptr)));

    connect(connection,SIGNAL(connectionClose()),
            SLOT(onConnectionClosed()));

    connect(connection,SIGNAL(pipeBegin(RyPipeData_ptr)),
            SIGNAL(pipeBegin(RyPipeData_ptr)));
    connect(connection,SIGNAL(pipeComplete(RyPipeData_ptr)),
            SIGNAL(pipeComplete(RyPipeData_ptr)));
    connect(connection,SIGNAL(pipeError(RyPipeData_ptr)),
            SIGNAL(pipeError(RyPipeData_ptr)));


    connection->moveToThread(newThread);
    connect(newThread,SIGNAL(started()),connection,SLOT(run()));
    connect(newThread,SIGNAL(finished()),SLOT(onThreadTerminated()));
    newThread->start();

    /*
    qDebug()<<"=== create connection cost:"
           <<time.msecsTo(QDateTime::currentDateTime())
           <<time.toMSecsSinceEpoch();
    */
    return connection;
}