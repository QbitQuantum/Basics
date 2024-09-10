QList<QAction*> SendFileItemAction::actions(const KFileItemListProperties &fileItemInfos, QWidget *parent)
{
    Q_UNUSED(parent)

    QList<QAction*> list;

    // Don't show the action for files that we can't send
    if (!fileItemInfos.isLocal()) {
        return list;
    }

    m_infos = fileItemInfos;

    QAction *menuAction = new QAction(QIcon::fromTheme(QStringLiteral("preferences-system-bluetooth")), i18n("Send via Bluetooth"), this);
    QMenu *menu = new QMenu();
    menuAction->setMenu(menu);
    loadMenu(menu);

    list.append(menuAction);
    return list;
}