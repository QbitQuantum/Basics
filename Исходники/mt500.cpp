void MT500::testConnection()
{
    for(int i = 0; i < 6; i++) {
        if(!ipArray[i].ip.isEmpty()){
            QString msg = "[" + QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss") + "] ";
            QTcpSocket * test = new QTcpSocket;
            test->connectToHost(QHostAddress(ipArray[i].ip), ipArray[i].port);
            if(test->waitForConnected(2000)) {
                msg += ipArray[i].ip + ": Test Message Sent";
                ui->testBrowser->append("<font color=green>" + msg + "</font>");
                test->abort();
            }
            else {
                msg += ipArray[i].ip + ": Failed to Connect";
                ui->testBrowser->append("<font color=red>" + msg + "</font>");
            }
        }
    }
    if(!initial) {
        QString fips = fipsNo.trimmed().remove("VAZ");
        QString msgToSend = "A 100 " + QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss") + " " + QString::number(boxGID);
        sendBase(msgToSend, true);
        sendRaw(msgToSend);
        sendRawStrtoIflows(QString(encode(msgToSend)));
    }
    else initial = false;
}