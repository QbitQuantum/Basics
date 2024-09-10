bool TmpDirChecker::checkWritePermissions(const QString &dirPath) {
    QDir dir(dirPath);
    if (!dir.exists()) {
        return false;
    }

    QFile tmpFile(getNewFilePath(dir.absolutePath(), "checkWritePermissions"));
    if (!tmpFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    tmpFile.close();
    tmpFile.remove();
    return true;
}