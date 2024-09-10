QString CDTpAvatarUpdate::writeAvatarFile(QFile &avatarFile)
{
    if (not mCacheDir.exists() && not QDir::root().mkpath(mCacheDir.absolutePath())) {
        warning() << "Could not create large avatar cache dir:" << mCacheDir.path();
        return QString();
    }

    QTemporaryFile tempFile(mCacheDir.absoluteFilePath(QLatin1String("pinkpony")));
    const QByteArray data = mNetworkReply->readAll();

    if (tempFile.open() && data.count() == tempFile.write(data)) {
        tempFile.close();

        if (avatarFile.exists()) {
            avatarFile.remove();
        }

        if (tempFile.rename(avatarFile.fileName())) {
            tempFile.setAutoRemove(false);
            return avatarFile.fileName();
        }
    }

    return QString();
}