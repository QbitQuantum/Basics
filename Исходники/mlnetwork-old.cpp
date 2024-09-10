QString MLNetwork::httpGetBinaryFile(const QString& url)
{
    if (MLUtil::inGuiThread()) {
        qCritical() << "Cannot call MLNetwork::httpGetBinaryFile from within the GUI thread: " + url;
        exit(-1);
    }

    //TaskProgress task("Downloading binary file");
    //task.log(url);
    QTime timer;
    timer.start();
    QString fname = get_temp_fname();
    QNetworkAccessManager manager; // better make it a singleton
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    QFile temp(fname);
    int num_bytes = 0;
    temp.open(QIODevice::WriteOnly);
    QObject::connect(reply, &QNetworkReply::readyRead, [&]() {
        if (MLUtil::threadInterruptRequested()) {
            TaskProgress errtask("Download halted");
            errtask.error("Thread interrupt requested");
            errtask.log(url);
            reply->abort();
        }
        QByteArray X=reply->readAll();
        temp.write(X);
        num_bytes+=X.count();
    });
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //task.setLabel(QString("Downloaded %1 MB in %2 sec").arg(num_bytes * 1.0 / 1e6).arg(timer.elapsed() * 1.0 / 1000));
    printf("RECEIVED BINARY (%d ms, %d bytes) from %s\n", timer.elapsed(), num_bytes, url.toLatin1().data());
    TaskManager::TaskProgressMonitor::globalInstance()->incrementQuantity("bytes_downloaded", num_bytes);
    if (MLUtil::threadInterruptRequested()) {
        return "";
    }
    return fname;
}