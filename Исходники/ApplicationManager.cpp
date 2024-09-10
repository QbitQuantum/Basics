bool ApplicationManager::acquireApplicationLock()
{
    QFile lockFile(CevirgecConstants::LOCK_FILE_PATH());
    if(lockFile.exists()){
        return false;
    }

    if(!lockFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("@ApplicationManager::acquireApplicationLock: Cannot create lock file");
        return false;
    }

    qDebug() << "@ApplicationManager::acquireApplicationLock: Lock file created at " << CevirgecConstants::LOCK_FILE_PATH();
    lockFile.close();
    return true;
}