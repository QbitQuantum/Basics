void PlacesPanel::slotItemContextMenuRequested(int index, const QPointF& pos)
{
    PlacesItem* item = m_model->placesItem(index);
    if (!item) {
        return;
    }

    QMenu menu(this);

    QAction* emptyTrashAction = 0;
    QAction* addAction = 0;
    QAction* mainSeparator = 0;
    QAction* editAction = 0;
    QAction* teardownAction = 0;
    QAction* ejectAction = 0;

    const QString label = item->text();

    const bool isDevice = !item->udi().isEmpty();
    if (isDevice) {
        ejectAction = m_model->ejectAction(index);
        if (ejectAction) {
            ejectAction->setParent(&menu);
            menu.addAction(ejectAction);
        }

        teardownAction = m_model->teardownAction(index);
        if (teardownAction) {
            teardownAction->setParent(&menu);
            menu.addAction(teardownAction);
        }

        if (teardownAction || ejectAction) {
            mainSeparator = menu.addSeparator();
        }
    } else {
        if (item->url() == QUrl(QStringLiteral("trash:/"))) {
            emptyTrashAction = menu.addAction(QIcon::fromTheme(QStringLiteral("trash-empty")), i18nc("@action:inmenu", "Empty Trash"));
            emptyTrashAction->setEnabled(item->icon() == QLatin1String("user-trash-full"));
            menu.addSeparator();
        }
        addAction = menu.addAction(QIcon::fromTheme(QStringLiteral("document-new")), i18nc("@item:inmenu", "Add Entry..."));
        mainSeparator = menu.addSeparator();
        editAction = menu.addAction(QIcon::fromTheme(QStringLiteral("document-properties")), i18nc("@item:inmenu", "Edit '%1'...", label));
    }

    if (!addAction) {
        addAction = menu.addAction(QIcon::fromTheme(QStringLiteral("document-new")), i18nc("@item:inmenu", "Add Entry..."));
    }

    QAction* openInNewTabAction = menu.addAction(i18nc("@item:inmenu", "Open '%1' in New Tab", label));
    openInNewTabAction->setIcon(QIcon::fromTheme(QStringLiteral("tab-new")));

    QAction* removeAction = 0;
    if (!isDevice && !item->isSystemItem()) {
        removeAction = menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18nc("@item:inmenu", "Remove '%1'", label));
    }

    QAction* hideAction = menu.addAction(i18nc("@item:inmenu", "Hide '%1'", label));
    hideAction->setCheckable(true);
    hideAction->setChecked(item->isHidden());

    QAction* showAllAction = 0;
    if (m_model->hiddenCount() > 0) {
        if (!mainSeparator) {
            mainSeparator = menu.addSeparator();
        }
        showAllAction = menu.addAction(i18nc("@item:inmenu", "Show All Entries"));
        showAllAction->setCheckable(true);
        showAllAction->setChecked(m_model->hiddenItemsShown());
    }

    menu.addSeparator();
    QMenu* iconSizeSubMenu = new QMenu(i18nc("@item:inmenu", "Icon Size"), &menu);

    struct IconSizeInfo
    {
        int size;
        const char* context;
        const char* text;
    };

    const int iconSizeCount = 4;
    static const IconSizeInfo iconSizes[iconSizeCount] = {
        {KIconLoader::SizeSmall,        I18N_NOOP2_NOSTRIP("Small icon size", "Small (%1x%2)")},
        {KIconLoader::SizeSmallMedium,  I18N_NOOP2_NOSTRIP("Medium icon size", "Medium (%1x%2)")},
        {KIconLoader::SizeMedium,       I18N_NOOP2_NOSTRIP("Large icon size", "Large (%1x%2)")},
        {KIconLoader::SizeLarge,        I18N_NOOP2_NOSTRIP("Huge icon size", "Huge (%1x%2)")}
    };

    QHash<QAction*, int> iconSizeActionMap;
    QActionGroup* iconSizeGroup = new QActionGroup(iconSizeSubMenu);

    for (int i = 0; i < iconSizeCount; ++i) {
        const int size = iconSizes[i].size;
        const QString text = i18nc(iconSizes[i].context, iconSizes[i].text,
                                   size, size);

        QAction* action = iconSizeSubMenu->addAction(text);
        iconSizeActionMap.insert(action, size);
        action->setActionGroup(iconSizeGroup);
        action->setCheckable(true);
        action->setChecked(m_view->iconSize() == size);
    }

    menu.addMenu(iconSizeSubMenu);

    menu.addSeparator();
    foreach (QAction* action, customContextMenuActions()) {
        menu.addAction(action);
    }