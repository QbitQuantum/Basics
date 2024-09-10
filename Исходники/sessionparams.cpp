int SessionParams::openSocket()
{
    qDebug() << "Trying to connect an IGT server:" << getHostname() << ":" << getPort();
    int r = socket->ConnectToServer(getHostname().toStdString().c_str(), getPort());

    if (r != 0)
      qWarning() << "Cannot connect to the server.";

    return r;
}