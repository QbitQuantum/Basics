KFilePlacesModel::KFilePlacesModel(QObject *parent)
    : QAbstractItemModel(parent), d(new Private(this))
{
    const QString file = KStandardDirs::locateLocal("data", "kfileplaces/bookmarks.xml");
    d->bookmarkManager = KBookmarkManager::managerForFile(file, "kfilePlaces");

    // Let's put some places in there if it's empty. We have a corner case here:
    // Given you have bookmarked some folders (which have been saved on
    // ~/.local/share/user-places.xbel (according to freedesktop bookmarks spec), and
    // deleted the home directory ~/.kde, the call managerForFile() will return the
    // bookmark manager for the fallback "kfilePlaces", making root.first().isNull() being
    // false (you have your own items bookmarked), resulting on only being added your own
    // bookmarks, and not the default ones too. So, we also check if kfileplaces/bookmarks.xml
    // file exists, and if it doesn't, we also add the default places. (ereslibre)
    KBookmarkGroup root = d->bookmarkManager->root();
    if (root.first().isNull() || !QFile::exists(file)) {

        // NOTE: The context for these I18N_NOOP2 calls has to be "KFile System Bookmarks".
        // The real i18nc call is made later, with this context, so the two must match.
        //
        // createSystemBookmark actually does nothing with its third argument,
        // but we have to give it something so the I18N_NOOP2 calls stay here for now.
        //
        // (coles, 13th May 2009)

        KFilePlacesItem::createSystemBookmark(d->bookmarkManager,
                                              "Home", I18N_NOOP2("KFile System Bookmarks", "Home"),
                                              KUrl(KUser().homeDir()), "user-home");
        KFilePlacesItem::createSystemBookmark(d->bookmarkManager,
                                              "Network", I18N_NOOP2("KFile System Bookmarks", "Network"),
                                              KUrl("remote:/"), "network-workgroup");
#ifdef Q_OS_WIN
        // adding drives
        foreach ( const QFileInfo& info, QDir::drives() ) {
#ifndef _WIN32_WCE
            uint type = DRIVE_UNKNOWN;
#endif
            QString driveIcon = "drive-harddisk";
#ifndef _WIN32_WCE
            QT_WA({ type = GetDriveTypeW((wchar_t *)info.absoluteFilePath().utf16()); },
                  { type = GetDriveTypeA(info.absoluteFilePath().toLocal8Bit()); });