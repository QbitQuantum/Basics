/*!
    Returns a list of volume info objects that are mounted as network drive shares.
*/
QList<VolumeInfo> networkVolumeInfosFromMountPoints()
{
    QList<VolumeInfo> volumes;
    QFileInfoList drives = QDir::drives();
    foreach (const QFileInfo &drive, drives) {
        const QString driveLetter = QDir::toNativeSeparators(drive.canonicalPath());
        const uint driveType = GetDriveTypeA(qPrintable(driveLetter));
        switch (driveType) {
            case DRIVE_REMOTE: {
                char buffer[1024] = "";
                DWORD bufferLength = 1024;
                UNIVERSAL_NAME_INFOA *universalNameInfo = (UNIVERSAL_NAME_INFOA*) &buffer;
                if (WNetGetUniversalNameA(qPrintable(driveLetter), UNIVERSAL_NAME_INFO_LEVEL,
                    LPVOID(universalNameInfo), &bufferLength) == NO_ERROR) {
                        VolumeInfo info;
                        info.setMountPath(driveLetter);
                        info.setVolumeDescriptor(QLatin1String(universalNameInfo->lpUniversalName));
                        volumes.append(info);
                }
            }   break;

            default:
                break;
        }
    }
    return volumes;
}