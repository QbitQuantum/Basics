bool DataManager::renameFile(int index, const QString &newName, const QString &oldName)
{
    QFile* file = m_fileVec.at(index);
    if( file )
    {
        file->rename(oldName, newName);
        return true;
    }
    return false;
}