Command *ActionManagerPrivate::registerOverridableAction(QAction *action, const QString &id, bool checkUnique)
{
    OverrideableAction *a = 0;
    const int uid = UniqueIDManager::instance()->uniqueIdentifier(id);

    if (CommandPrivate * c = m_idCmdMap.value(uid, 0)) {
        a = qobject_cast<OverrideableAction *>(c);
        if (!a) {
            qWarning() << "registerAction: id" << id << "is registered with a different command type.";
            return c;
        }
    } else {
        a = new OverrideableAction(uid);
        m_idCmdMap.insert(uid, a);
    }

    if (!a->action()) {
        QAction *baseAction = new QAction(m_mainWnd);
        baseAction->setObjectName(id);
        baseAction->setCheckable(action->isCheckable());
        baseAction->setIcon(action->icon());
        baseAction->setIconText(action->iconText());
        baseAction->setText(action->text());
        baseAction->setToolTip(action->toolTip());
        baseAction->setStatusTip(action->statusTip());
        baseAction->setWhatsThis(action->whatsThis());
        baseAction->setChecked(action->isChecked());
        baseAction->setSeparator(action->isSeparator());
        baseAction->setShortcutContext(Qt::ApplicationShortcut);
        baseAction->setEnabled(false);
        baseAction->setParent(m_mainWnd);
#ifdef Q_WS_MAC
        baseAction->setIconVisibleInMenu(false);
#endif
        a->setAction(baseAction);
        m_mainWnd->addAction(baseAction);
        a->setKeySequence(a->keySequence());
        a->setDefaultKeySequence(QKeySequence());
    } else if (checkUnique) {
        qWarning() << "registerOverridableAction: id" << id << "is already registered.";
    }

    return a;
}