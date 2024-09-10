QList<QAction*> CompressFileItemAction::actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget)
{
    // #268163: don't offer compression on already compressed archives.
    if (m_pluginManager->supportedMimeTypes().contains(fileItemInfos.mimeType())) {
        return {};
    }

    QList<QAction*> actions;
    const QIcon icon = QIcon::fromTheme(QStringLiteral("ark"));

    QMenu *compressMenu = new QMenu(parentWidget);

    compressMenu->addAction(createAction(icon,
                                         i18nc("@action:inmenu Part of Compress submenu in Dolphin context menu", "Here (as TAR.GZ)"),
                                         parentWidget,
                                         fileItemInfos.urlList(),
                                         QStringLiteral("ark --changetofirstpath --add --autofilename tar.gz %F")));

    const QMimeType zipMime = QMimeDatabase().mimeTypeForName(QStringLiteral("application/zip"));
    // Don't offer zip compression if no zip plugin is available.
    if (!m_pluginManager->preferredWritePluginsFor(zipMime).isEmpty()) {
        compressMenu->addAction(createAction(icon,
                                             i18nc("@action:inmenu Part of Compress submenu in Dolphin context menu", "Here (as ZIP)"),
                                             parentWidget,
                                             fileItemInfos.urlList(),
                                             QStringLiteral("ark --changetofirstpath --add --autofilename zip %F")));
    }

    compressMenu->addAction(createAction(icon,
                                         i18nc("@action:inmenu Part of Compress submenu in Dolphin context menu", "Compress to..."),
                                         parentWidget,
                                         fileItemInfos.urlList(),
                                         QStringLiteral("ark --add --changetofirstpath --dialog %F")));

    QAction *compressMenuAction = new QAction(i18nc("@action:inmenu Compress submenu in Dolphin context menu", "Compress"), parentWidget);
    compressMenuAction->setMenu(compressMenu);

    // #189177: disable compress menu in read-only folders.
    if (!fileItemInfos.supportsWriting()) {
        compressMenuAction->setEnabled(false);
    }

    actions << compressMenuAction;
    return actions;
}