    bool moveAndRename(QDir &dest, const QString &newName)
    {
        if (!dest.exists()) {
            qCDebug(LIBMAILDIR_LOG) << "Destination does not exist";
            return false;
        }
        if (dest.exists(newName) || dest.exists(subDirNameForFolderName(newName))) {
            qCDebug(LIBMAILDIR_LOG) << "New name already in use";
            return false;
        }

        if (!dest.rename(path, newName)) {
            qCDebug(LIBMAILDIR_LOG) << "Failed to rename maildir";
            return false;
        }
        const QDir subDirs(Maildir::subDirPathForFolderPath(path));
        if (subDirs.exists() && !dest.rename(subDirs.path(), subDirNameForFolderName(newName))) {
            qCDebug(LIBMAILDIR_LOG) << "Failed to rename subfolders";
            return false;
        }

        path = dest.path() + QDir::separator() + newName;
        return true;
    }