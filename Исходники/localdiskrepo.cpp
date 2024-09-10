void LocalDiskRepo::putFileComplete(QIODevice* device, QString file_path)
{
    qDebug() << "saving file";
    disconnect(device, SIGNAL(aboutToClose()), this, SLOT(putFileFailed()));
    QFile* f = (QFile*) device;
    if (!QFile::exists(absoluteFilePath(file_path))) {
        qDebug() << "renaming writebuffer and closing";
        f->rename(absoluteFilePath(file_path));
    } else {
        // keeping as temporary
        qCritical() << "file with file_path:" << file_path << " already exists";
        f->close();
    }
}