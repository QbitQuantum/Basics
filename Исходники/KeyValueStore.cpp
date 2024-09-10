/** Public thread methods (clients connect here) */
void KeyValueStore::PublicThread::run()
{
  Thread threads[MAX_CLIENT_THREADS];
  HandleClient threadInst[MAX_CLIENT_THREADS];
  const Config::ServerInformation& info = config.getServerInformation();
  Config::ThreadControl& control = config.getThreadControl();
  int id = 0;
  char full = Protocol::SRV_FULL;
  char conn = Protocol::SRV_CONN;

  ServerSocket server;
  SocketAddress sock(info.address, info.pubPort);
  server.bind(sock, true);
  server.listen(5);

  printKv("Listening for clients on "<< info.address <<":"<< info.pubPort);

  while(control.isLive()) {
    // Simply do thread per client
    StreamSocket client = server.acceptConnection();
    printKv("Received client connection request - waiting for thread to free up");
    
    // Wait five seconds
    try {
      freeThreads.wait(5000); // This beats busy waiting
    } catch(TimeoutException& notUsed(e)) {
      printKv("Server full - closing connection to client");
      client.sendBytes(&full, sizeof(full));
      client.close();
      continue;
    }

    // Send success
    client.sendBytes(&conn, sizeof(conn));

    // tryJoin() doesn't work properly in linux, using isRunning() instead
    // actively search for the next available thread
    while(threads[id].isRunning()){ // Try to get an available thread
      id = (id + 1) % MAX_CLIENT_THREADS;
      Thread::sleep(250); // 250ms between each check
    }

    printKv("Serving client");
    threadInst[id] = HandleClient(client, control);
    threads[id].start(threadInst[id]);
  }

  server.close();
  freeThreads.set(); // Free a thread with semaphore
}