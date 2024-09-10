QString ContentDisplay::generateFileMD5(QString fileName)
{
    QFile contentFile(fileName);
    if(!contentFile.open(QFile::ReadOnly)) {
        displayErrorMessage("Could not open content file: \n" + fileName);
        return QString("");
    }
    QString hashData(QCryptographicHash::hash(contentFile.readAll(), QCryptographicHash::Md5).toHex().constData());
    contentFile.close();

    return hashData;
}