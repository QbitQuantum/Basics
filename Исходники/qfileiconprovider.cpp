QIcon QFileIconProviderPrivate::getWinIcon(const QFileInfo &fileInfo) const
{
    QIcon retIcon;
    static int defaultFolderIIcon = -1;

    QString key;
    QPixmap pixmap;
    // If it's a file, non-{exe,lnk,ico} then we might have it cached already
    if (isCacheable(fileInfo)) {
        const QString fileExtension = QLatin1Char('.') + fileInfo.suffix().toUpper();
        key = QLatin1String("qt_") + fileExtension;
        QPixmapCache::find(key, pixmap);
        if (!pixmap.isNull()) {
            retIcon.addPixmap(pixmap);
            if (QPixmapCache::find(key + QLatin1Char('l'), pixmap))
                retIcon.addPixmap(pixmap);
            return retIcon;
        }
    }

    const bool cacheableDirIcon = fileInfo.isDir() && !fileInfo.isRoot();
    if (!useCustomDirectoryIcons && defaultFolderIIcon >= 0 && cacheableDirIcon) {
        // We already have the default folder icon, just return it
        key = QString::fromLatin1("qt_dir_%1").arg(defaultFolderIIcon);
        QPixmapCache::find(key, pixmap);
        if (!pixmap.isNull()) {
            retIcon.addPixmap(pixmap);
            if (QPixmapCache::find(key + QLatin1Char('l'), pixmap))
                retIcon.addPixmap(pixmap);
            return retIcon;
        }
    }

    /* We don't use the variable, but by storing it statically, we
     * ensure CoInitialize is only called once. */
    static HRESULT comInit = CoInitialize(NULL);
    Q_UNUSED(comInit);

    SHFILEINFO info;
    unsigned long val = 0;

    //Get the small icon
    unsigned int flags =
#ifndef Q_OS_WINCE
        SHGFI_ICON|SHGFI_SYSICONINDEX|SHGFI_ADDOVERLAYS|SHGFI_OVERLAYINDEX;
#else
        SHGFI_SYSICONINDEX;
#endif

    if (cacheableDirIcon && !useCustomDirectoryIcons) {
        flags |= SHGFI_USEFILEATTRIBUTES;
        val = SHGetFileInfo(L"dummy",
                            FILE_ATTRIBUTE_DIRECTORY, &info,
                            sizeof(SHFILEINFO), flags | SHGFI_SMALLICON);
    } else {
        val = SHGetFileInfo((const wchar_t *)QDir::toNativeSeparators(fileInfo.filePath()).utf16(),
                            0, &info, sizeof(SHFILEINFO), flags | SHGFI_SMALLICON);
    }

    // Even if GetFileInfo returns a valid result, hIcon can be empty in some cases
    if (val && info.hIcon) {
        if (fileInfo.isDir() && !fileInfo.isRoot()) {
            if (!useCustomDirectoryIcons && defaultFolderIIcon < 0)
                defaultFolderIIcon = info.iIcon;
            //using the unique icon index provided by windows save us from duplicate keys
            key = QString::fromLatin1("qt_dir_%1").arg(info.iIcon);
            QPixmapCache::find(key, pixmap);
            if (!pixmap.isNull()) {
                retIcon.addPixmap(pixmap);
                if (QPixmapCache::find(key + QLatin1Char('l'), pixmap))
                    retIcon.addPixmap(pixmap);
                DestroyIcon(info.hIcon);
                return retIcon;
            }
        }
        if (pixmap.isNull()) {
#ifndef Q_OS_WINCE
            pixmap = QPixmap::fromWinHICON(info.hIcon);
#else
            pixmap = QPixmap::fromWinHICON(ImageList_GetIcon((HIMAGELIST) val, info.iIcon, ILD_NORMAL));
#endif
            if (!pixmap.isNull()) {
                retIcon.addPixmap(pixmap);
                if (!key.isEmpty())
                    QPixmapCache::insert(key, pixmap);
            }
            else {
              qWarning("QFileIconProviderPrivate::getWinIcon() no small icon found");
            }
        }
        DestroyIcon(info.hIcon);
    }

    //Get the big icon
    val = SHGetFileInfo((const wchar_t *)QDir::toNativeSeparators(fileInfo.filePath()).utf16(),
                0, &info, sizeof(SHFILEINFO), flags | SHGFI_LARGEICON);

    if (val && info.hIcon) {
        if (fileInfo.isDir() && !fileInfo.isRoot()) {
            //using the unique icon index provided by windows save us from duplicate keys
            key = QString::fromLatin1("qt_dir_%1").arg(info.iIcon);
        }
#ifndef Q_OS_WINCE
        pixmap = QPixmap::fromWinHICON(info.hIcon);
#else
        pixmap = QPixmap::fromWinHICON(ImageList_GetIcon((HIMAGELIST) val, info.iIcon, ILD_NORMAL));
#endif
        if (!pixmap.isNull()) {
            retIcon.addPixmap(pixmap);
            if (!key.isEmpty())
                QPixmapCache::insert(key + QLatin1Char('l'), pixmap);
        }
        else {
            qWarning("QFileIconProviderPrivate::getWinIcon() no large icon found");
        }
        DestroyIcon(info.hIcon);
    }
    return retIcon;
}