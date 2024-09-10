    /*------------------------------------------------------------------------------*

     *------------------------------------------------------------------------------*/
    WebProxy::WebProxy()
    {
        QTcpServer *proxyServer = new QTcpServer(this);
        proxyServer->listen(QHostAddress::Any, 8080);
        connect(proxyServer, SIGNAL(newConnection()), this, SLOT(manageQuery()));
        qDebug( )  << __FILE__ << __FUNCTION__ << "Proxy server running at port" << proxyServer->serverPort();
    } //WebProxy::WebProxy