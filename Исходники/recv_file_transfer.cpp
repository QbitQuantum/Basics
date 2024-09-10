bool RecvFileTransfer::parseHeader(QByteArray &recvBlock, struct TransferFile &transferFile)
{
    bool ok;
    int headerSize
        = recvBlock.left(TRANSFER_FILE_HEADER_SIZE_LENGTH).toInt(&ok, 16);
    if (!ok)
    {
        m_errorString = "RecvFileTransfer::parseHeader: get headerSize error";
        return false;
    }

    QByteArray header = recvBlock.left(headerSize);

    QList<QByteArray> list = header.split(':');

#define TRANSFERFILE_NAME_POS           1
#define TRANSFERFILE_SIZE_POS           2
#define TRANSFERFILE_TYPE_POS           3
#define TRANSFERFILE_ATTR_BEGIN_POS     4

    // XXX NOTE: canParseHeader() make sure we have enough items in list,
    // so we do not need to check size of list before call list.at()
//    transferFile.name = Macai::transferCodec->codec()->toUnicode(list.at(TRANSFERFILE_NAME_POS));
    QTextCodec* codec = QTextCodec::codecForName("SYSTEM");
    transferFile.name = codec->toUnicode(list.at(TRANSFERFILE_NAME_POS));

    transferFile.size = list.at(TRANSFERFILE_SIZE_POS).toLongLong(&ok, 16);
    if (!ok)
    {
        m_errorString = "RecvFileTransfer::parseHeader: get file size error";
        return false;
    }
    transferFile.type = list.at(TRANSFERFILE_TYPE_POS).toInt(&ok, 16);
    if (!ok)
    {
        m_errorString = "RecvFileTransfer::parseHeader: get file type error";
        return false;
    }

    // Extended file attribution like mtime, atime...
    for (int i = TRANSFERFILE_ATTR_BEGIN_POS; i < list.size(); ++i)
    {
        QString s = list.at(i);
        QStringList l = s.split(QChar('='));
        if (l.size() == 2)
        {
            int i = l.at(0).toInt(&ok, 16);
            if (ok)
            {
                transferFile.extendAttr.insert(i, l.at(1));
            }
        }
    }

    recvBlock.remove(0, headerSize);

    return true;
}