qlonglong DeviceInfo::availableDiskSpace() const
{
    QStorageInfo info;
    qlonglong diskSpace = 0;
    QStringList drives = info.allLogicalDrives();

    drives.removeDuplicates();

    foreach (const QString &drive, drives)
    {
        if (info.driveType(drive) == QStorageInfo::InternalDrive)
        {
            diskSpace += info.availableDiskSpace(drive);
        }
    }

    return diskSpace;
}