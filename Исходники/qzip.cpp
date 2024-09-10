void QZip::zipDir(QuaZipFile &outFile,const QString &zipPath,const QString &zipTPath){
    QDir dir(zipPath);
    dir.setCurrent(zipPath);
    QFileInfoList files=dir.entryInfoList();

    QFile inFile;
    char c;
    foreach(QFileInfo file, files) {
        if(file.isDir()){
            if(!file.absoluteFilePath().endsWith(".")){
                QString zipDirecName = zipTPath==""?file.fileName():zipTPath+"\\"+file.fileName();
                zipDir(outFile,file.absoluteFilePath(),zipDirecName);
                dir.setCurrent(zipPath);
            }
            continue;//
        }
        inFile.setFileName(file.fileName());
        if(!inFile.open(QIODevice::ReadOnly)) {
            qWarning("testCreate(): inFile.open(): %s", inFile.errorString().toLocal8Bit().constData());
            return;
        }
        QString zipDirName = zipTPath==""?inFile.fileName():zipTPath+"\\"+inFile.fileName();
        if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(zipDirName, inFile.fileName()))) {
            qWarning("testCreate(): outFile.open(): %d", outFile.getZipError());
            return;
        }
        while(inFile.getChar(&c)&&outFile.putChar(c));
        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.putChar(): %d", outFile.getZipError());
            return;
        }
        outFile.close();
        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.close(): %d", outFile.getZipError());
            return;
        }
        inFile.close();
    }
}