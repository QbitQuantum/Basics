void IdealController::addView(Qt::DockWidgetArea area, View* view)
{
    IdealDockWidget *dock = new IdealDockWidget(this, m_mainWindow);
    // dock object name is used to store toolview settings
    QString dockObjectName = view->document()->title();
    // support different configuration for same docks opened in different areas
    if (m_mainWindow->area())
        dockObjectName += '_' + m_mainWindow->area()->objectName();

    dock->setObjectName(dockObjectName);

    KAcceleratorManager::setNoAccel(dock);
    QWidget *w = view->widget(dock);
    if (w->parent() == 0)
    {
        /* Could happen when we're moving the widget from
           one IdealDockWidget to another.  See moveView below.
           In this case, we need to reparent the widget. */
        w->setParent(dock);
    }

    QList<QAction *> toolBarActions = view->toolBarActions();
    if (toolBarActions.isEmpty()) {
      dock->setWidget(w);
    } else {
      QMainWindow *toolView = new QMainWindow();
      QToolBar *toolBar = new QToolBar(toolView);
      int iconSize = m_mainWindow->style()->pixelMetric(QStyle::PM_SmallIconSize);
      toolBar->setIconSize(QSize(iconSize, iconSize));
      toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
      toolBar->setWindowTitle(i18n("%1 Tool Bar", w->windowTitle()));
      toolBar->setFloatable(false);
      toolBar->setMovable(false);
      toolBar->addActions(toolBarActions);
      toolView->setCentralWidget(w);
      toolView->addToolBar(toolBar);
      dock->setWidget(toolView);
    }

    dock->setWindowTitle(view->widget()->windowTitle());
    dock->setWindowIcon(view->widget()->windowIcon());
    dock->setFocusProxy(dock->widget());

    if (IdealButtonBarWidget* bar = barForDockArea(area)) {
        QAction* action = bar->addWidget(
            view->document()->title(), dock,
            static_cast<MainWindow*>(parent())->area(), view);
        m_dockwidget_to_action[dock] = m_view_to_action[view] = action;

        m_docks->addAction(action);
        connect(dock, &IdealDockWidget::closeRequested, action, &QAction::toggle);
    }

    connect(dock, &IdealDockWidget::dockLocationChanged, this, &IdealController::dockLocationChanged);

    dock->hide();

    docks.insert(dock);
}