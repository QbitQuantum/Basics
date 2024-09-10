void freeLockFile(){
    QFile lockFile(lockFilePathGlob);
    lockFile.open(QIODevice::ReadWrite);
    lockFile.remove();
}