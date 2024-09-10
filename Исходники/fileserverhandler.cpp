QList<FileSystemInfo> FileServerHandler::QueryFileSystems(void)
{
    QStringList groups(StorageGroup::kSpecialGroups);
    groups.removeAll("LiveTV");
    QString specialGroups = groups.join("', '");

    MSqlQuery query(MSqlQuery::InitCon());
    query.prepare(QString("SELECT MIN(id),dirname "
                            "FROM storagegroup "
                           "WHERE hostname = :HOSTNAME "
                             "AND groupname NOT IN ( '%1' ) "
                           "GROUP BY dirname;").arg(specialGroups));
    query.bindValue(":HOSTNAME", gCoreContext->GetHostName());

    QList<FileSystemInfo> disks;
    if (query.exec() && query.isActive())
    {
        if (!query.size())
        {
            query.prepare("SELECT MIN(id),dirname "
                            "FROM storagegroup "
                           "WHERE groupname = :GROUP "
                           "GROUP BY dirname;");
            query.bindValue(":GROUP", "Default");
            if (!query.exec())
                MythDB::DBError("BackendQueryFileSystems", query);
        }

        QDir checkDir("");
        QString currentDir;
        FileSystemInfo disk;
        QMap <QString, bool>foundDirs;

        while (query.next())
        {
            disk.clear();
            disk.setHostname(gCoreContext->GetHostName());
            disk.setLocal();
            disk.setBlockSize(0);
            disk.setGroupID(query.value(0).toInt());

            /* The storagegroup.dirname column uses utf8_bin collation, so Qt
             * uses QString::fromAscii() for toString(). Explicitly convert the
             * value using QString::fromUtf8() to prevent corruption. */
            currentDir = QString::fromUtf8(query.value(1)
                                           .toByteArray().constData());
            disk.setPath(currentDir);

            if (currentDir.right(1) == "/")
                currentDir.remove(currentDir.length() - 1, 1);

            checkDir.setPath(currentDir);
            if (!foundDirs.contains(currentDir))
            {
                if (checkDir.exists())
                {
                    disk.PopulateDiskSpace();
                    disk.PopulateFSProp();
                    disks << disk;

                    foundDirs[currentDir] = true;
                }
                else
                    foundDirs[currentDir] = false;
            }
        }
    }

    return disks;
}