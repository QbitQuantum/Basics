QList<QAction*> ExtractFileItemAction::actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget)
{
    QList<QAction*> actions;
    const QIcon icon = QIcon::fromTheme(QStringLiteral("archive-extract"));

    bool readOnlyParentDir = false;
    QList<QUrl> supportedUrls;
    // Filter URLs by supported mimetypes.
    foreach (const QUrl &url, fileItemInfos.urlList()) {
        const QMimeType mimeType = determineMimeType(url.path());
        if (m_pluginManager->preferredPluginsFor(mimeType).isEmpty()) {
            continue;
        }
        supportedUrls << url;
        // Check whether we can write in the parent directory of the file.
        const QString directory = url.adjusted(QUrl::RemoveFilename | QUrl::StripTrailingSlash).toLocalFile();
        if (!QFileInfo(directory).isWritable()) {
            readOnlyParentDir = true;
        }
    }

    if (supportedUrls.isEmpty()) {
        return {};
    }

    QMenu *extractMenu = new QMenu(parentWidget);

    extractMenu->addAction(createAction(icon,
                                        i18nc("@action:inmenu Part of Extract submenu in Dolphin context menu", "Extract archive here"),
                                        parentWidget,
                                        supportedUrls,
                                        QStringLiteral("ark --batch --autodestination %F")));

    extractMenu->addAction(createAction(icon,
                                        i18nc("@action:inmenu Part of Extract submenu in Dolphin context menu", "Extract archive to..."),
                                        parentWidget,
                                        supportedUrls,
                                        QStringLiteral("ark --batch --autodestination --dialog %F")));

    extractMenu->addAction(createAction(icon,
                                        i18nc("@action:inmenu Part of Extract submenu in Dolphin context menu", "Extract archive here, autodetect subfolder"),
                                        parentWidget,
                                        supportedUrls,
                                        QStringLiteral("ark --batch --autodestination --autosubfolder %F")));

    QAction *extractMenuAction = new QAction(i18nc("@action:inmenu Extract submenu in Dolphin context menu", "Extract"), parentWidget);
    extractMenuAction->setMenu(extractMenu);
    extractMenuAction->setIcon(icon);

    // #189177: disable extract menu in read-only folders.
    if (readOnlyParentDir) {
        extractMenuAction->setEnabled(false);
    }

    actions << extractMenuAction;
    return actions;
}