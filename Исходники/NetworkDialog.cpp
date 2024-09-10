void NetworkDialog::slotOkClicked()
{
        m_okButton->setEnabled(false);
        m_feedback->show();
       
        if (m_client) {
            m_feedback->setText(i18n("Connecting to remote host..."));
            m_socket = new QTcpSocket;
            connect(m_socket, &QTcpSocket::connected, this, &NetworkDialog::clientOK);
            connect(m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &NetworkDialog::clientError);
            m_socket->connectToHost(m_hostname->text(), m_port->value());
        }
        else {
            m_feedback->setText(i18n("Waiting for an incoming connection..."));        
            QTcpServer* server = new QTcpServer;
            connect(server, &QTcpServer::newConnection, this, &NetworkDialog::serverOK);
            m_publisher=new KDNSSD::PublicService(nickname(), QLatin1Literal("_kbattleship._tcp"), m_port->value());
            m_publisher->publishAsync();
            
            server->listen(QHostAddress::Any, static_cast<quint16>(m_port->value()));
        }
}