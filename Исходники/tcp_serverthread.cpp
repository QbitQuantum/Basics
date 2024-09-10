void TcpServerThread::run()
{
    TcpServer *server = new TcpServer;
    server->listen(*Host::host,Host::port);
    exec();
}