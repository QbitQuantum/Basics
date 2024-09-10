void DriveTransfer::TransferFile(QString sourcePath, QString relativeFilePath, QString targetPath, int64_t& checksum)
{
    QFile source(sourcePath + "/" + relativeFilePath);

    _subTaskDescription = "Copying " + relativeFilePath.toStdString();

    // TODO: Ensure trailing slash to remove need of appending it in multiple places
    if (QFile::exists(targetPath + relativeFilePath))
    {
        QFile::remove(targetPath + "/" + relativeFilePath);
    }

    QFile target(targetPath + "/" + relativeFilePath);

    OC_LOG_INFO("From: " + source.fileName().toStdString() + " To: " + target.fileName().toStdString());
    source.open(QIODevice::ReadOnly);
    target.open(QIODevice::WriteOnly);

    if (source.error() || target.error())
    {
        OC_LOG_ERROR("DriveTransfer failed.");
        return;
    }

    int TRANSFER_BLOCK_SIZE = 1024 * 1024; // 1MB

    float progressBlock = source.size() / 100.0f;
    int totalRead = 0;
    int progress = 0;

    const std::unique_ptr<IHashGenerator> hashGenerator(new xxHashAdapter());
    hashGenerator->Initialize();

    // TODO: Error handling
    char* buffer = new char[TRANSFER_BLOCK_SIZE];
    while (!source.atEnd())
    {
        qint64 readSize = source.read(buffer, TRANSFER_BLOCK_SIZE);
        target.write(buffer, readSize);

        hashGenerator->Update(buffer, readSize);

        totalRead += readSize;

         //progress = totalRead / progressBlock;

        if (totalRead > progressBlock * progress)
        {
            progress += totalRead / progressBlock;

            ProgressChanged(progress);
        }
    }

    checksum = hashGenerator->Retrieve();
}