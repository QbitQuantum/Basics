void KonqCopyToMainMenu::slotAboutToShow()
{
    clear();
    KonqCopyToDirectoryMenu* subMenu;
    // Home Folder
    subMenu = new KonqCopyToDirectoryMenu(this, this, QDir::homePath());
    subMenu->setTitle(i18nc("@title:menu", "Home Folder"));
    subMenu->setIcon(QIcon::fromTheme("go-home"));
    addMenu(subMenu);

    // Root Folder
#ifndef Q_OS_WIN
    subMenu = new KonqCopyToDirectoryMenu(this, this, QDir::rootPath());
    subMenu->setTitle(i18nc("@title:menu", "Root Folder"));
    subMenu->setIcon(QIcon::fromTheme("folder-red"));
    addMenu(subMenu);
#else
    foreach ( const QFileInfo& info, QDir::drives() ) {
        uint type = DRIVE_UNKNOWN;
        QString driveIcon = "drive-harddisk";
        QT_WA({ type = GetDriveTypeW((wchar_t *)info.absoluteFilePath().utf16()); },
              { type = GetDriveTypeA(info.absoluteFilePath().toLocal8Bit()); });