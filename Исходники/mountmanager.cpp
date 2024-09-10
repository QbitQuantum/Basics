bool MountManager::unmount()
{
    if(!mountedDirExists()){
        emit errorString(QString(QLatin1String("Already have unmounted in %1 ...continue")).arg(m_mountdir));
        return true;
    }
    QProcess proc;
    proc.setEnvironment(QProcess::systemEnvironment());
    proc.start(QString(QLatin1String("sh -c \"echo %1 | sudo -S umount %2\"")).arg(m_userPassWord).arg(m_mountdir));
    if(!proc.waitForFinished()){
        emit errorString(QString(QLatin1String("Can't unmount image %1")).arg(QString(proc.errorString())));
        return false;
    }
    if(mountedDirExists()){
        proc.waitForReadyRead();
        emit errorString(QLatin1String(proc.readAllStandardError()));
        return false;
    }
    proc.terminate();
    messageString(QString(QLatin1String("Image unmounted.")));
    return true;
}