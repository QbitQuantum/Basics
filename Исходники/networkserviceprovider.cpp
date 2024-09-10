void NetworkServiceProvider::run(){

    bool dbAvail = false;

    while(!dbAvail){
        msleep(100);
        QList<ProcessManager::Process*> processes = ProcessManager::instance()->processesFromClassName("SearchStorageThread");
        if(processes.isEmpty()){
            dbAvail = false;
        }else{
            if(processes.first()->description == "Saves search databases"){
                break;
            }
        }
    }

    this->_serverSocket = new QTcpServer(this);

    int retryCount = 0;
    bool success = false;
    while(!success && retryCount < 40){
        success = this->_serverSocket->listen(QHostAddress::Any, Config::current()->serverPort());
        retryCount++;

        if(!success)
            msleep(200);
    }

    if(!success){
        Log::add(tr("Could not listen on port %1").arg(QString::number(Config::current()->serverPort())), Log::Error);
        return;
    }


    Log::add(tr("Bringing search interface up"),Log::Information);

    forever{
        if(_stop){
            break;
        }
        bool ok;
        this->_serverSocket->waitForNewConnection(500,&ok);

        this->checkForFinishedThreads();

        //Kein Timeout sondern verbindung
        if(!ok){

            QTcpSocket *socket = this->_serverSocket->nextPendingConnection();
            if(!socket)
                continue;
            socket->setParent(0);

            SearchRequestHandler *handler = new SearchRequestHandler(socket);
            socket->moveToThread(handler);

            connect(handler,SIGNAL(finished()),handler,SLOT(cleanUp()));
            this->_requests.append(handler);

            handler->start();


        }
    }
    _stopped = true;
}