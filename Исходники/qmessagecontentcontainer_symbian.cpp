bool QMessageContentContainerPrivate::createAttachment(const QString& attachmentPath)
{
    //set the attachment data

    if (!QFile::exists(attachmentPath)) {
        return false;
    }

    QFile attachmentFile(attachmentPath);
    if (!attachmentFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    _content = attachmentFile.readAll();
    _available = true;
        
    _size = attachmentFile.size();    
    
    attachmentFile.close();
    QFileInfo fi(attachmentPath);
    _name = fi.fileName().toLatin1();
    
    //set the mime-type
    QByteArray mimeType;
    QString type;
    TBuf8<255> fileBuffer;
    RApaLsSession session;    
    QString fileString = fi.fileName();
    TPtrC16 filePtr(reinterpret_cast<const TUint16*>(fileString.utf16()));
    TBuf8<20> fileType;
    TPtrC8 ptr8((TUint8 *)(_content.constData()), _content.length());
    if(session.Connect() == KErrNone){                        
        TDataRecognitionResult fileDataType;                     
        session.RecognizeData(filePtr, ptr8, fileDataType);                                         
        fileType.Copy(fileDataType.iDataType.Des8());
        mimeType = QByteArray((const char*)fileType.Ptr(), fileType.Length());
        session.Close();                
    }

    QString extension(fi.suffix());
    int index = mimeType.indexOf("/");
    if (index != -1) {
        _type = mimeType.left(index).trimmed();
        _subType = mimeType.mid(index + 1).trimmed();
    }
    
    // set the whole filepath to _filename
    _filename = fi.filePath().toLatin1();
    
    return true;
}