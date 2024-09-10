static void* serve(void* param)
{
    Socket* listening = static_cast<Socket*>(param);
    listening->listen(5);

    es::Socket* socket;
    while ((socket = listening->accept()) == 0)
    {
    }

    esReport("accepted\n");

    // Let the client fill up its buffer
    // Do not read anything
    while (true)
    {
	esSleep(30000000);
    }
    
    socket->close();
    esReport("close() by serve()\n");
    socket->release();

    // Wait for 2 MSL time wait
    esSleep(2 * 1200000000LL + 100000000LL);

    return 0;   // lint
}