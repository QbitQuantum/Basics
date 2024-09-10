/**
 * Méthode initialisant l'icône de la zone de notification
 *
 * @return void
 * @since  1.0.0
 */
void ConvertWindow::initIcon()
{
    tray_icon = new QSystemTrayIcon(this);

    QMenu* menu = new QMenu(this);

    QAction* action_show = new QAction(QString::fromUtf8("Afficher"), this);
    QAction* action_hide = new QAction(QString::fromUtf8("Réduire"), this);
    QAction* action_about = new QAction(QString::fromUtf8("A propos de QOpenConvert"), this);
    QAction* action_close = new QAction(QString::fromUtf8("Fermer QOpenConvert"), this);

    connect(action_show, SIGNAL(triggered()), this, SLOT(showWindow()));
    connect(action_hide, SIGNAL(triggered()), this, SLOT(hideWindow()));
    connect(action_close, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(action_about, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    menu->addAction(action_show);
    menu->addAction(action_hide);
    menu->addAction(action_about);
    menu->addAction(action_close);

    tray_icon->setContextMenu(menu);

    QIcon image = QIcon(":/images/icon.png");
    tray_icon->setIcon(image);

    tray_icon->show();
}