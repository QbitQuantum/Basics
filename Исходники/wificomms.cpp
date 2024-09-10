/**
  * @brief Slot to emit signals used by the mainwindow to start the telemetry thread
  * @param Pointer to button from the dialogue box
  */
void wifiComms::buttonBoxChanged(QAbstractButton* btnAbstract)
{
    // Take strings and numbers from the dialogue boxes
    quint16 serverPort = ui->serverPortlineEdit->text().toUInt();
    QString serverIP = ui->serverIPlineEdit->text();
    quint16 clientPort = ui->clientPortlineEdit->text().toUInt();
    QString clientIP = ui->clientIPlineEdit->text();

    AHNS_DEBUG("wifiComms::buttonBoxChanged()");

    if ((btnAbstract->text() == "Close") || (btnAbstract->text() == "&Close"))
    {
        AHNS_DEBUG("wifiComms::buttonBoxChanged() [ Close ]");

        emit ConnectionClose();
    }
    else if (btnAbstract->text() == "Open")
    {
        AHNS_DEBUG("wifiComms::buttonBoxChanged() [ Open ]");

        emit ConnectionStart(serverPort, serverIP, clientPort, clientIP);
    }
    else if (btnAbstract->text() == "Retry")
    {
        AHNS_DEBUG("wifiComms::buttonBoxChanged() [ Retry ]");

        emit ConnectionRetry(serverPort, serverIP, clientPort, clientIP);
    }
    else if (btnAbstract->text() == "Restore Defaults")
    {
        AHNS_DEBUG("wifiComms::buttonBoxChanged() [ Restore Defaults ]");

        ui->serverIPlineEdit->setText(DEFAULT_SERVER_IP);
        ui->serverPortlineEdit->setText(DEFAULT_SERVER_PORT);
        ui->clientIPlineEdit->setText(DEFAULT_CLIENT_IP);
        ui->clientPortlineEdit->setText(DEFAULT_CLIENT_PORT);
    }
    else // ui is wrong
    {
        AHNS_DEBUG("wifiComms::buttonBoxChanged() [ UNDEFINED BUTTON ]");
    }
}