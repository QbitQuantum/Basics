/**
  Returns the best match for the given file url in the project directory.

  The method first checks whether the file inside the project directory exists.
  If not, the leading directory in the path is stripped, and the - now shorter - path is
  checked for existence, and so on. Second, it tries to locate the file in the sysroot
  folder specified. Third, we walk the list of project files, and search for a file name match
  there. If all fails, it returns the original path from the file url.
  */
QString FileInProjectFinder::findFile(const QUrl &fileUrl, bool *success) const
{
    if (debug)
        qDebug() << "FileInProjectFinder: trying to find file" << fileUrl.toString() << "...";

    QString originalPath = fileUrl.toLocalFile();
    if (originalPath.isEmpty()) // e.g. qrc://
        originalPath = fileUrl.path();

    if (originalPath.isEmpty()) {
        if (debug)
            qDebug() << "FileInProjectFinder: malformed url, returning";
        if (success)
            *success = false;
        return originalPath;
    }

    if (!m_projectDir.isEmpty()) {
        if (debug)
            qDebug() << "FileInProjectFinder: checking project directory ...";

        int prefixToIgnore = -1;
        const QChar separator = QLatin1Char('/');
        if (originalPath.startsWith(m_projectDir + separator)) {

#ifdef Q_OS_MAC
            // starting with the project path is not sufficient if the file was
            // copied in an insource build, e.g. into MyApp.app/Contents/Resources
            static const QString appResourcePath = QString::fromLatin1(".app/Contents/Resources");
            if (originalPath.contains(appResourcePath)) {
                // the path is inside the project, but most probably as a resource of an insource build
                // so ignore that path
                prefixToIgnore = originalPath.indexOf(appResourcePath) + appResourcePath.length();
            } else {
#endif
                if (debug)
                    qDebug() << "FileInProjectFinder: found" << originalPath << "in project directory";
                if (success)
                    *success = true;
                return originalPath;
#ifdef Q_OS_MAC
            }
#endif
        }

        if (m_cache.contains(originalPath)) {
            if (debug)
                qDebug() << "FileInProjectFinder: checking cache ...";
            // check if cached path is still there
            QString candidate = m_cache.value(originalPath);
            QFileInfo candidateInfo(candidate);
            if (candidateInfo.exists() && candidateInfo.isFile()) {
                if (success)
                    *success = true;
                if (debug)
                    qDebug() << "FileInProjectFinder: found" << candidate << "in the cache";
                return candidate;
            }
        }

        if (debug)
            qDebug() << "FileInProjectFinder: checking stripped paths in project directory ...";

        // Strip directories one by one from the beginning of the path,
        // and see if the new relative path exists in the build directory.
        if (prefixToIgnore < 0) {
            if (!QFileInfo(originalPath).isAbsolute()
                    && !originalPath.startsWith(separator)) {
                prefixToIgnore = 0;
            } else {
                prefixToIgnore = originalPath.indexOf(separator);
            }
        }
        while (prefixToIgnore != -1) {
            QString candidate = originalPath;
            candidate.remove(0, prefixToIgnore);
            candidate.prepend(m_projectDir);
            QFileInfo candidateInfo(candidate);
            if (candidateInfo.exists() && candidateInfo.isFile()) {
                if (success)
                    *success = true;

                if (debug)
                    qDebug() << "FileInProjectFinder: found" << candidate << "in project directory";

                m_cache.insert(originalPath, candidate);
                return candidate;
            }
            prefixToIgnore = originalPath.indexOf(separator, prefixToIgnore + 1);
        }
    }

    // find (solely by filename) in project files
    if (debug)
        qDebug() << "FileInProjectFinder: checking project files ...";

    const QString fileName = QFileInfo(originalPath).fileName();
    foreach (const QString &f, m_projectFiles) {
        if (QFileInfo(f).fileName() == fileName) {
            m_cache.insert(originalPath, f);
            if (success)
                *success = true;
            if (debug)
                qDebug() << "FileInProjectFinder: found" << f << "in project files";
            return f;
        }
    }

    if (debug)
        qDebug() << "FileInProjectFinder: checking absolute path in sysroot ...";

    // check if absolute path is found in sysroot
    if (!m_sysroot.isEmpty()) {
        const QString sysrootPath = m_sysroot + originalPath;
        if (QFileInfo(sysrootPath).exists() && QFileInfo(sysrootPath).isFile()) {
            if (success)
                *success = true;
            m_cache.insert(originalPath, sysrootPath);
            if (debug)
                qDebug() << "FileInProjectFinder: found" << sysrootPath << "in sysroot";
            return sysrootPath;
        }
    }

    if (success)
        *success = false;

    if (debug)
        qDebug() << "FileInProjectFinder: couldn't find file!";
    return originalPath;
}