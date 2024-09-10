    ApplicationPool_Server_PoolTest() {
        createServerInstanceDirAndGeneration(serverInstanceDir, generation);
        socketFilename = generation->getPath() + "/socket";
        accountsDatabase = ptr(new AccountsDatabase());
        accountsDatabase->add("test", "12345", false);

        messageServer = ptr(new MessageServer(socketFilename, accountsDatabase));
        realPool      = ptr(new ApplicationPool::Pool("../helper-scripts/passenger-spawn-server", generation));
        poolServer    = ptr(new ApplicationPool::Server(realPool));
        messageServer->addHandler(poolServer);
        serverThread = ptr(new oxt::thread(
                               boost::bind(&MessageServer::mainLoop, messageServer.get())
                           ));
        pool  = newPoolConnection();
        pool2 = newPoolConnection();
    }