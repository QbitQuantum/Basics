bool CGpgExec::gpgExecute(QString request, QString param1, QString param2, QString *result)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    QString cmdPath = pathToGnuPG;
    QProcess coprocess;
    QString filePath;
    QString keyid;
    bool stat = false;

    coprocess.setProcessChannelMode(QProcess::MergedChannels);

    if(request == "check"){
        filePath = param1;
        coprocess.start(cmdPath, QStringList() << "-n" << "--verbose" << "--import" << filePath);
        //coprocess.start(cmdPath, QStringList() << "--batch" << "--interactive" << "--import" << filePath);
    }
    else if(request == "import"){
        filePath = param1;
        coprocess.start(cmdPath, QStringList() << "--verbose" << "--import" << filePath);
    }
    else if(request == "fingerprint"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--fingerprint" << keyid);
    }
    else if(request == "list-sigs"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--list-sigs" << keyid);
    }
    else if(request == "delete-keys"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--batch" << "--yes" << "--delete-keys" << keyid);
    }
//    else if(request == "encrypt"){
//        keyid = param1;
//        filePath = param2;
//        QProcess coprocess1;
//        coprocess1.setStandardOutputProcess(&coprocess);
//        coprocess1.start("cmd.exe", QStringList() << "/c" << "echo" << "y");
//        coprocess.start(cmdPath, QStringList() << "--command-fd" << "0" << "--encrypt" << "--recipient" << keyid << filePath);
//    }

    if (coprocess.waitForStarted()){
        int timeoutSec = 60;
        if(! processExecutionTimeoutSeconds.isEmpty()){
            bool ok;
            timeoutSec = processExecutionTimeoutSeconds.toInt(&ok, 10);
            if(timeoutSec == 0){
                timeoutSec = 60;
            }
        }
        if (!coprocess.waitForFinished(timeoutSec * 1000)){
            QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(coprocess.readAll()));
        }
        else{
            *result = QString(coprocess.readAll());
//            if(request == "encrypt"){
//                if(result->isEmpty()
//                        || result->mid(15, 56) == "There is no assurance this key belongs to the named user"
//                        || result->mid(15, 56) == "この鍵が本当に本人のものである、という兆候が、ありません"
//                        ){
//                    sleepCount = timeoutSec;
//                    waitingFilePath = filePath + ".gpg";
//                    timer->start(1000);
//                    stat = true;
//               }
//                else{
//                    stat = false;
//                }
//            }
//            else{
                stat = true;
//            }
        }
    }
    else{
        QString errmsg = coprocess.errorString();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("Error"),
                                        tr("Can't start GNU PG."),
                                        QMessageBox::Abort);
        if (reply == QMessageBox::Abort){
            close();
        }
    }
    return stat;
}