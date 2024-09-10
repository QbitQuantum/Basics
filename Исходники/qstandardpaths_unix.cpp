QString QStandardPaths::writableLocation(StandardLocation type)
{
    switch (type) {
    case HomeLocation:
        return QDir::homePath();
    case TempLocation:
        return QDir::tempPath();
    case CacheLocation:
    case GenericCacheLocation:
    {
        // http://standards.freedesktop.org/basedir-spec/basedir-spec-0.6.html
        QString xdgCacheHome = QFile::decodeName(qgetenv("XDG_CACHE_HOME"));
        if (isTestModeEnabled())
            xdgCacheHome = QDir::homePath() + QLatin1String("/.qttest/cache");
        if (xdgCacheHome.isEmpty())
            xdgCacheHome = QDir::homePath() + QLatin1String("/.cache");
        if (type == QStandardPaths::CacheLocation)
            appendOrganizationAndApp(xdgCacheHome);
        return xdgCacheHome;
    }
    case DataLocation:
    case GenericDataLocation:
    {
        QString xdgDataHome = QFile::decodeName(qgetenv("XDG_DATA_HOME"));
        if (isTestModeEnabled())
            xdgDataHome = QDir::homePath() + QLatin1String("/.qttest/share");
        if (xdgDataHome.isEmpty())
            xdgDataHome = QDir::homePath() + QLatin1String("/.local/share");
        if (type == QStandardPaths::DataLocation)
            appendOrganizationAndApp(xdgDataHome);
        return xdgDataHome;
    }
    case ConfigLocation:
    case GenericConfigLocation:
    {
        // http://standards.freedesktop.org/basedir-spec/latest/
        QString xdgConfigHome = QFile::decodeName(qgetenv("XDG_CONFIG_HOME"));
        if (isTestModeEnabled())
            xdgConfigHome = QDir::homePath() + QLatin1String("/.qttest/config");
        if (xdgConfigHome.isEmpty())
            xdgConfigHome = QDir::homePath() + QLatin1String("/.config");
        return xdgConfigHome;
    }
    case RuntimeLocation:
    {
        const uid_t myUid = geteuid();
        // http://standards.freedesktop.org/basedir-spec/latest/
        QString xdgRuntimeDir = QFile::decodeName(qgetenv("XDG_RUNTIME_DIR"));
        if (xdgRuntimeDir.isEmpty()) {
            const QString userName = QFileSystemEngine::resolveUserName(myUid);
            xdgRuntimeDir = QDir::tempPath() + QLatin1String("/runtime-") + userName;
            QDir dir(xdgRuntimeDir);
            if (!dir.exists()) {
                if (!QDir().mkdir(xdgRuntimeDir)) {
                    qWarning("QStandardPaths: error creating runtime directory %s: %s", qPrintable(xdgRuntimeDir), qPrintable(qt_error_string(errno)));
                    return QString();
                }
            }
            qWarning("QStandardPaths: XDG_RUNTIME_DIR not set, defaulting to '%s'", qPrintable(xdgRuntimeDir));
        }
        // "The directory MUST be owned by the user"
        QFileInfo fileInfo(xdgRuntimeDir);
        if (fileInfo.ownerId() != myUid) {
            qWarning("QStandardPaths: wrong ownership on runtime directory %s, %d instead of %d", qPrintable(xdgRuntimeDir),
                     fileInfo.ownerId(), myUid);
            return QString();
        }
        // "and he MUST be the only one having read and write access to it. Its Unix access mode MUST be 0700."
        QFile file(xdgRuntimeDir);
        const QFile::Permissions wantedPerms = QFile::ReadUser | QFile::WriteUser | QFile::ExeUser;
        if (file.permissions() != wantedPerms && !file.setPermissions(wantedPerms)) {
            qWarning("QStandardPaths: wrong permissions on runtime directory %s", qPrintable(xdgRuntimeDir));
            return QString();
        }
        return xdgRuntimeDir;
    }
    default:
        break;
    }

#ifndef QT_BOOTSTRAPPED
    // http://www.freedesktop.org/wiki/Software/xdg-user-dirs
    QString xdgConfigHome = QFile::decodeName(qgetenv("XDG_CONFIG_HOME"));
    if (xdgConfigHome.isEmpty())
        xdgConfigHome = QDir::homePath() + QLatin1String("/.config");
    QFile file(xdgConfigHome + QLatin1String("/user-dirs.dirs"));
    if (!isTestModeEnabled() && file.open(QIODevice::ReadOnly)) {
        QHash<QString, QString> lines;
        QTextStream stream(&file);
        // Only look for lines like: XDG_DESKTOP_DIR="$HOME/Desktop"
        QRegExp exp(QLatin1String("^XDG_(.*)_DIR=(.*)$"));
        while (!stream.atEnd()) {
            const QString &line = stream.readLine();
            if (exp.indexIn(line) != -1) {
                const QStringList lst = exp.capturedTexts();
                const QString key = lst.at(1);
                QString value = lst.at(2);
                if (value.length() > 2
                    && value.startsWith(QLatin1Char('\"'))
                    && value.endsWith(QLatin1Char('\"')))
                    value = value.mid(1, value.length() - 2);
                // Store the key and value: "DESKTOP", "$HOME/Desktop"
                lines[key] = value;
            }
        }

        QString key;
        switch (type) {
        case DesktopLocation:
            key = QLatin1String("DESKTOP");
            break;
        case DocumentsLocation:
            key = QLatin1String("DOCUMENTS");
            break;
        case PicturesLocation:
            key = QLatin1String("PICTURES");
            break;
        case MusicLocation:
            key = QLatin1String("MUSIC");
            break;
        case MoviesLocation:
            key = QLatin1String("VIDEOS");
            break;
        case DownloadLocation:
            key = QLatin1String("DOWNLOAD");
            break;
        default:
            break;
        }
        if (!key.isEmpty()) {
            QString value = lines.value(key);
            if (!value.isEmpty()) {
                // value can start with $HOME
                if (value.startsWith(QLatin1String("$HOME")))
                    value = QDir::homePath() + value.mid(5);
                if (value.length() > 1 && value.endsWith(QLatin1Char('/')))
                    value.chop(1);
                return value;
            }
        }
    }
#endif

    QString path;
    switch (type) {
    case DesktopLocation:
        path = QDir::homePath() + QLatin1String("/Desktop");
        break;
    case DocumentsLocation:
        path = QDir::homePath() + QLatin1String("/Documents");
       break;
    case PicturesLocation:
        path = QDir::homePath() + QLatin1String("/Pictures");
        break;

    case FontsLocation:
        path = QDir::homePath() + QLatin1String("/.fonts");
        break;

    case MusicLocation:
        path = QDir::homePath() + QLatin1String("/Music");
        break;

    case MoviesLocation:
        path = QDir::homePath() + QLatin1String("/Videos");
        break;
    case DownloadLocation:
        path = QDir::homePath() + QLatin1String("/Downloads");
        break;
    case ApplicationsLocation:
        path = writableLocation(GenericDataLocation) + QLatin1String("/applications");
        break;

    default:
        break;
    }

    return path;
}