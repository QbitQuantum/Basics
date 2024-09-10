static void removeFilesAndDirs (QDir &dir) {
    //qDebug() << "dir:" << dir.path();
    // files
    QFileInfoList lst = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
    foreach (const QFileInfo &fi, lst) {
        //qDebug() << "removing" << fi.fileName() << fi.absoluteFilePath();
        dir.remove(fi.fileName());
    }