bool RocketFileSystem::ClearDirectory(QDir dir)
{
    bool ok = true;
    if (!dir.exists())
        return ok;

    // Remove all files
    QFileInfoList entries = dir.entryInfoList(QDir::Files|QDir::NoSymLinks|QDir::NoDotAndDotDot);
    foreach(QFileInfo entry, entries)
    {
        if (entry.isFile())
        {
            if (!dir.remove(entry.fileName()))
            {
                LogWarning("[RocketFileSystem]: Failed to remove file " + entry.absoluteFilePath());
                ok = false;
            }
        }
    }
    // Remove all directories recursively.
    entries = dir.entryInfoList(QDir::AllDirs|QDir::NoSymLinks|QDir::NoDotAndDotDot);
    foreach(QFileInfo entry, entries)
    {
        if (entry.isDir())
        {
            if (!RemoveDirectory(entry.absoluteFilePath()))
                ok = false;
        }
    }
    return ok;
}