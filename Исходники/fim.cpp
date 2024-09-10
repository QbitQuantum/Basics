void Installer::ex()
{
    emit ok();
    emit finished();
    QDir dir;
    QString path = "C:/private/e6002cd5/" + del;
    dir.remove(path);
    qDebug()<<"install completed and file deleted";
}