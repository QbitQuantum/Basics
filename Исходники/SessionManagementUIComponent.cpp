SessionManagementUIComponent::SessionManagementUIComponent(Corrade::PluginManager::AbstractPluginManager* manager, const std::string& plugin): AbstractUIComponent(manager, plugin) {
    /* Open session */
    QIcon openSessionIcon;
    openSessionIcon.addFile(":/open-session-16.png");
    openSessionIcon.addFile(":/open-session-64.png");
    QAction* openSessionAction = new QAction(openSessionIcon, tr("Restore saved session"), this);
    openSessionAction->setData("openSession");

    _actions << openSessionAction;

    /* Session list menu */
    sessionMenu = new QMenu(MainWindow::instance());
    openSessionAction->setMenu(sessionMenu);
    QAction* separator = sessionMenu->addSeparator();
    sessionMenu->addAction(tr("Session manager"), this, SLOT(sessionManagerDialog()));
    new SessionMenuView(MainWindow::instance()->sessionManager(), sessionMenu, separator, this);
}