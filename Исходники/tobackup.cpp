toBackup::toBackup(toTool* tool, QWidget *main, toConnection &connection)
        : toToolWidget(*tool, "backup.html", main, connection, "toBackup")
        , tool_(tool)
{
    QToolBar *toolbar = toAllocBar(this, tr("Backup Manager"));
    layout()->addWidget(toolbar);

    updateAct = new QAction(QPixmap(const_cast<const char**>(refresh_xpm)),
                            tr("Update"), this);
    updateAct->setShortcut(QKeySequence::Refresh);
    connect(updateAct, SIGNAL(triggered()), this, SLOT(refresh(void)));
    toolbar->addAction(updateAct);

    toolbar->addWidget(new toSpacer());

    new toChangeConnection(toolbar, TO_TOOLBAR_WIDGET_NAME);

    Tabs = new QTabWidget(this);
    layout()->addWidget(Tabs);

    QWidget *box = new QWidget(Tabs);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    box->setLayout(vbox);

    vbox->addWidget(new QLabel(tr("Logswitches per day and hour"), box));
    LogSwitches = new toResultTableView(true, false, box);
    LogSwitches->setSQL(SQLLogSwitches);
    vbox->addWidget(LogSwitches);
    Tabs->addTab(box, tr("Redo Switches"));

    LogHistory = new toResultTableView(true, false, Tabs);
    LogHistory->setSQL(SQLLogHistory);
    Tabs->addTab(LogHistory, tr("Archived Logs"));

    box = new QWidget(Tabs);
    vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    box->setLayout(vbox);

    LastLabel = new QLabel(box);
    vbox->addWidget(LastLabel);
    LastBackup = new toResultTableView(true, false, box);
    vbox->addWidget(LastBackup);
    LastBackup->setSQL(SQLLastBackup);
    Tabs->addTab(box, tr("Last Backup"));

    CurrentBackup = new toResultTableView(true, false, Tabs);
    CurrentBackup->setSQL(SQLCurrentBackup);
    Tabs->addTab(CurrentBackup, tr("Backup Progress"));

    ToolMenu = NULL;
    connect(toMainWidget()->workspace(), SIGNAL(subWindowActivated(QMdiSubWindow *)),
            this, SLOT(windowActivated(QMdiSubWindow *)));

    refresh();

    setFocusProxy(Tabs);
}