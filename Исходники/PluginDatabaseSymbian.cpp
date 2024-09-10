Vector<String> PluginDatabase::defaultPluginDirectories()
{
    Vector<String> directories;
    //find the installation drive
    TDriveList drivelist;
    TChar driveLetter;
    RFs fsSession;
    
    if (fsSession.Connect() == KErrNone && fsSession.DriveList(drivelist) == KErrNone) {
        for (TInt driveNumber = EDriveA; driveNumber <= EDriveZ; driveNumber++) {
            if (drivelist[driveNumber] && fsSession.DriveToChar(driveNumber, driveLetter) == KErrNone) {
                QString driveStringValue(QChar((uint)driveLetter.GetUpperCase()));
                QString stubDirPath;
                stubDirPath.append(driveStringValue);
                stubDirPath.append(QT_PLUGIN_FOLDER);
                if (QFileInfo(stubDirPath).exists())
                    directories.append(stubDirPath);
            }
        }
    }

    fsSession.Close();
    return directories;
}