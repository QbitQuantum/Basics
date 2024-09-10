bool KArchiveDirectory::copyTo(const QString &dest, bool recursiveCopy) const
{
    QDir root;

    QList<const KArchiveFile *> fileList;
    QMap<qint64, QString> fileToDir;

    // placeholders for iterated items
    QStack<const KArchiveDirectory *> dirStack;
    QStack<QString> dirNameStack;

    dirStack.push(this);       // init stack at current directory
    dirNameStack.push(dest);   // ... with given path
    do {
        const KArchiveDirectory *curDir = dirStack.pop();
        const QString curDirName = dirNameStack.pop();
        if (!root.mkpath(curDirName)) {
            return false;
        }

        const QStringList dirEntries = curDir->entries();
        for (QStringList::const_iterator it = dirEntries.begin(); it != dirEntries.end(); ++it) {
            const KArchiveEntry *curEntry = curDir->entry(*it);
            if (!curEntry->symLinkTarget().isEmpty()) {
                QString linkName = curDirName + QLatin1Char('/') + curEntry->name();
                // To create a valid link on Windows, linkName must have a .lnk file extension.
#ifdef Q_OS_WIN
                if (!linkName.endsWith(QStringLiteral(".lnk"))) {
                    linkName += QStringLiteral(".lnk");
                }
#endif
                QFile symLinkTarget(curEntry->symLinkTarget());
                if (!symLinkTarget.link(linkName)) {
                    //qDebug() << "symlink(" << curEntry->symLinkTarget() << ',' << linkName << ") failed:" << strerror(errno);
                }
            } else {
                if (curEntry->isFile()) {
                    const KArchiveFile *curFile = dynamic_cast<const KArchiveFile *>(curEntry);
                    if (curFile) {
                        fileList.append(curFile);
                        fileToDir.insert(curFile->position(), curDirName);
                    }
                }

                if (curEntry->isDirectory() && recursiveCopy) {
                    const KArchiveDirectory *ad = dynamic_cast<const KArchiveDirectory *>(curEntry);
                    if (ad) {
                        dirStack.push(ad);
                        dirNameStack.push(curDirName + QLatin1Char('/') + curEntry->name());
                    }
                }
            }
        }
    } while (!dirStack.isEmpty());

    qSort(fileList.begin(), fileList.end(), sortByPosition);    // sort on d->pos, so we have a linear access

    for (QList<const KArchiveFile *>::const_iterator it = fileList.constBegin(), end = fileList.constEnd();
            it != end; ++it) {
        const KArchiveFile *f = *it;
        qint64 pos = f->position();
        if (!f->copyTo(fileToDir[pos])) {
            return false;
        }
    }
    return true;
}