QDomElement BookmarkWidget::findElementbyUUID(QDomDocument& doc, QString uuid, int type, const QString xmlPath)
{
    QString path;
    if (xmlPath == QString())
        path = getBookmarkFilepath();
    else
        path = xmlPath;
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug()<<"File cannot be opened.";
        showFileOpenError();
        file.close();
        return doc.createElement(QString());
    }

    doc.setContent(&file);
    QDomNodeList list = doc.elementsByTagName(BOOKMARK_XML_ROOT);
    if(list.isEmpty()) {
        showInvalidFileError();
        file.close();
        return doc.createElement(QString());
    }

    QDomElement root = list.at(0).toElement();
    QDomNodeList nodes;
    if(type == BOOKMARK) nodes = root.elementsByTagName(BOOKMARK_NAME);
    else if(type == FOLDER) nodes = root.elementsByTagName(FOLDER_NAME);

    QDomElement elt;
    QString value;
    for(int i = 0; i < nodes.length(); i++) {
        elt = nodes.at(i).toElement();
        value = elt.attribute(UUID_NAME);

        if(value == uuid) break;
        value.clear();
    }
    file.close();
    if(!value.isEmpty()) return elt;
    else return doc.createElement(QString());
}