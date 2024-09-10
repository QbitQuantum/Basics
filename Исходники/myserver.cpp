MyServer::MyServer()
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));
    if(!server->listen(QHostAddress::Any, 8080))
    {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server listenning...";
    }
}