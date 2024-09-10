void NetworkManagerThread::run(){

    _server = new QTcpServer();

    int retryCount = 0;
    bool success = false;
    while(!success && retryCount < 40){
        success = this->_server->listen(QHostAddress::Any, Config::current()->serverPort()+1);
        retryCount++;

        if(!success)
            msleep(200);
    }

    if(!success){
        Log::add(tr("Could not listen on port %1").arg(QString::number(Config::current()->serverPort()+1)), Log::Error);
        return;
    }


    bool ok;
    while(true){
        /*
          Eingebauter Stopp 1
          */
        this->checkSuspended();
        if(!_server)
            return;
        _server->waitForNewConnection(1000,&ok);
        if(!ok){
            /*
              Eingebauter Stop 2
              */
            this->checkSuspended();

            QTcpSocket *connection = _server->nextPendingConnection();
            if(connection == 0)
                continue;

            Log::add(tr("New connection from %1").arg(connection->peerAddress().toString()), Log::Information);

            RootConsoleThread *thread = new RootConsoleThread(connection);
            connection->setParent(0);
            connection->moveToThread(thread);

            this->_runningConsoles.append(thread);
            this->_sockets.append(connection);

            thread->start();
        }
    }


}