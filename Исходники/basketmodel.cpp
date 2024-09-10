bool BasketModel::setModelData(QByteArray &data, QString pwd, bool isEncryptedData)
{
    beginResetModel();
    QByteArray rawData = data;
    if ( isEncryptedData ) {
        BasketUtils butil;
        rawData = butil.decrypt(data, pwd);
    }
    QDomDocument doc;
    QString errMsg;
    int errLine, errCol;

    bool readResult = doc.setContent( rawData, &errMsg, &errLine, &errCol );
    if ( !readResult ) {
        endResetModel();
        return false;
    }

    hashPassword = pwd;
    endResetModel();
    return parseDocument(doc);
}