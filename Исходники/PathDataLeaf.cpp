bool Leaf::rename()
{
    QReadLocker locker(&lock);

    if (!state->allowRename())
        return false;

    QDir dir;

    if (parentComponent)
        dir.setPath(parentComponent->fullPath());

    bool isSucceeded = dir.rename(fileName, newName);

    isSucceeded ? Log::log("rename SUCCEEDED : " + dir.absolutePath() + "/" + fileName + " > " + newName)
                : Log::log("rename ---FAILED : " + dir.absolutePath() + "/" + fileName + " > " + newName);

    locker.unlock();

    isSucceeded ? setStateRenameSucceeded()
                : setStateRenameFailed(dir);

    return isSucceeded;
}