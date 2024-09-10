bool KDLockFile::Private::unlock()
{
    errorString.clear();
    if (!locked)
        return true;

    if (!UnlockFile(handle, 0, 0, QFileInfo(filename).size(), 0)) {
        errorString = QCoreApplication::translate("KDLockFile", "Cannot release the lock for "
            "file \"%1\": %2").arg(QDir::toNativeSeparators(filename), QInstaller::windowsErrorString(GetLastError()));
    } else {
        locked = false;
        CloseHandle(handle);
    }
    return !locked;
}