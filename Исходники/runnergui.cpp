    void RunnerGUI::doubleClickedOnDetails(int para, int /*pos*/)
    {
        static QRegExp reFileAndLine("^(.*)\\[([0-9]+)\\]:");

        QString line = m_testerWidget->details()->text(para);
        m_testerWidget->details()->setSelection(para, 0, para, line.length()-1);

        if ( reFileAndLine.search(line) != -1 )
        {
            DCOPClient client;
            client.attach();
            QByteArray data;
            QDataStream arg(&data, QIODevice::WriteOnly);
            bool ok;
            arg << QString(reFileAndLine.cap(1)) << (reFileAndLine.cap(2).toInt(&ok) - 1);
            client.send("kdevelop-*", "KDevPartController", "editDocument(QString,int)", data);
            client.send("kdevelop-*", "MainWindow", "raise()", "");

            client.detach();
        }
    }