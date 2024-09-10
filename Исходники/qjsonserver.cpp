/*!
  Configure the QJsonServer to listen on a new Unix local socket \a socketname using QJsonAuthority file \a authority.
  If the \a authority is omitted or NULL, all connections will be automatically authorized and
  a unique identifier generated for each new connection. Returns true if the socket could be opened.

  Does \b{not} take ownership of the \a authority object.
 */
bool QJsonServer::listen(const QString &socketname, QJsonAuthority *authority)
{
    QLocalServer::removeServer(socketname);
    QLocalServer *server = new QLocalServer(this);
    Q_D(QJsonServer);
    d->m_localServers.insert(server, authority);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(handleLocalConnection()));
    if (!server->listen(socketname)) {
        qCritical() << Q_FUNC_INFO << "Unable to listen on socket:" << socketname;
        d->m_localServers.remove(server);
        return false;
    }
    return true;
}