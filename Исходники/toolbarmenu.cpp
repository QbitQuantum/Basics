ToolbarMenu::ToolbarMenu(QWidget *parent) : QMenu(parent) {
    MainWindow *w = MainWindow::instance();
    addAction(w->getAction("stopafterthis"));
    addSeparator();
#ifdef APP_SNAPSHOT
    addAction(w->getAction("snapshot"));
#endif
    addAction(w->getAction("findVideoParts"));
    addSeparator();
    addAction(w->getAction("webpage"));
    addAction(w->getAction("videolink"));
    addAction(w->getAction("openInBrowser"));
    addAction(w->getAction("download"));
    addSeparator();
    QWidgetAction *widgetAction = new QWidgetAction(this);
    ShareToolbar *shareToolbar = new ShareToolbar();
    connect(this, &ToolbarMenu::leftMarginChanged, shareToolbar, &ShareToolbar::setLeftMargin);
    widgetAction->setDefaultWidget(shareToolbar);
    addAction(widgetAction);
    addSeparator();

    addAction(w->getAction("compactView"));
    addAction(w->getAction("ontop"));
    addSeparator();

    QToolBar *definitionToolbar = new QToolBar();
    definitionToolbar->setStyleSheet("QToolButton { padding: 0}");
    definitionToolbar->setToolButtonStyle(Qt::ToolButtonTextOnly);
    definitionToolbar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QActionGroup *definitionGroup = new QActionGroup(this);
    const VideoDefinition &preferredDefinition = YT3::instance().maxVideoDefinition();
    int counter = 0;
    for (auto defName : VideoDefinition::getDefinitionNames()) {
        QAction *a = new QAction(defName);
        a->setCheckable(true);
        a->setChecked(preferredDefinition.getName() == defName);
        connect(a, &QAction::triggered, this, [this, defName] {
            MainWindow::instance()->setDefinitionMode(defName);
            close();
        });
        definitionGroup->addAction(a);
        definitionToolbar->addAction(a);
        if (counter == 0) {
            QWidget *w = definitionToolbar->widgetForAction(a);
            w->setProperty("first", true);
            counter++;
        }
    }
    QWidgetAction *definitionAction = new QWidgetAction(this);
    definitionAction->setDefaultWidget(definitionToolbar);
    addAction(definitionAction);
    addSeparator();

    addAction(w->getAction("clearRecentKeywords"));
#ifndef APP_MAC
    addSeparator();
    addAction(w->getAction("toggleMenu"));
    addSeparator();
    addMenu(w->getMenu("help"));
#endif
}