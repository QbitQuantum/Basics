void SessionManager::renameSession( const QString & oldName, const QString & newName )
{
    if (mCurrentSession && mCurrentSession->name() == oldName) {
        saveSessionAs(newName);
        removeSession(oldName);
    } else {
        QDir dir = sessionsDir();
        if (dir.path().isEmpty())
            return;

        if (!dir.rename(oldName + ".yaml", newName + ".yaml"))
            qWarning("Could not rename session file!");
    }
}