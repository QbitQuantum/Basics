void UpdatingWindow::startDownload()
{

    QDir dir;
    QStringList path = pathToDownload.split("/");
    path.removeLast();
    QString oldPath = path.join("/")+"_old/";

    QString resourcesPath = pathToDownload;
    if(osName() == "win")
    {
        resourcesPath = AppData::Instance()->executablePath(pathToDownload).replace(".exe", "")+ "/";
    }
    QDir old(oldPath);
    dir.mkpath(oldPath);
    if(!dir.rename(resourcesPath+"settings.json", oldPath+"settings.json"))
    {
        qDebug() << "Move failed!" << resourcesPath;
    }
    if(!dir.rename(resourcesPath+"list.json", oldPath+"list.json"))
    {
        qDebug() << "Move failed!" << resourcesPath+"list.json" << oldPath+"list.json";
    }

    connect(&manager, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));
    writeToFile = new QFile(pathToDownload + fileToDownload);
    writeToFile->open(QIODevice::ReadWrite | QIODevice::Truncate);
    //writeToFile->resize(0);
    QNetworkRequest request(AppData::Instance()->settings["url"].toString() + "download_update.php?file=" + fileToDownload + "&os="+ osName());
    qDebug() << AppData::Instance()->settings["url"].toString() + "download_update.php?file=" + fileToDownload + "&os="+ osName();
   this->reply =  manager.get(request);
    connect(this->reply, SIGNAL(downloadProgress(qint64,qint64)),
                SLOT(downloadProgress(qint64,qint64)));
    connect(this->reply, SIGNAL(readyRead()),
                this, SLOT(readyRead()));
}