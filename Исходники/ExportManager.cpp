QUrl ExportManager::tempSave(const QString &mimetype)
{
    // if we already have a temp file saved, use that
    if (mTempFile.isValid()) {
        if (QFile(mTempFile.toLocalFile()).exists()) {
            return mTempFile;
        }
    }

    QTemporaryFile tmpFile(QDir::tempPath() + QDir::separator() + "Spectacle.XXXXXX." + mimetype);
    tmpFile.setAutoRemove(false);
    tmpFile.setPermissions(QFile::ReadUser | QFile::WriteUser);

    if (tmpFile.open()) {
        if(!writeImage(&tmpFile, mimetype.toLatin1())) {
            emit errorMessage(i18n("Cannot save screenshot. Error while writing temporary local file."));
            return QUrl();
        }
        mTempFile = QUrl::fromLocalFile(tmpFile.fileName());
        return mTempFile;
    }

    return QUrl();
}