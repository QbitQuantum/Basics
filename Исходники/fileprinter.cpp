bool FilePrinter::detectCupsService()
{
    QTcpSocket qsock;
    qsock.connectToHost("localhost", 631);
    bool rtn = qsock.waitForConnected() && qsock.isValid();
    qsock.abort();
    return rtn;
}