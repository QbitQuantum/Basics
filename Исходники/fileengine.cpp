/*
 *  Create files/directories based on the provided array
 */
void FileEngine::createEntries(const QString &jsonString)
{
    QVariantList entryList = QJsonDocument::fromJson(QByteArray(jsonString.toLatin1())).array().toVariantList();

    for (int i=0; i < entryList.length(); i++)
    {
        QMap<QString, QVariant> entryMap = entryList.at(i).toMap();

        QString type = entryMap.value("type").toString();
        QString path = entryMap.value("path").toString();
        QString name = entryMap.value("name").toString();

        // Create directories
        if (type == "directory")
        {
            QDir dir(path);
            bool success = dir.mkdir(QString("%1/%2").arg(path, name));
        }
        else if (type == "file")
        {
            QFile file(QString("%1/%2").arg(path, name));
            file.open(QFile::WriteOnly);
        }
    }
}