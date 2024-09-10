CWindowMain::CWindowMain(QWidget *parent)
    : QMainWindow(parent),
      m_executThread(NULL)
{
    m_widgetBFGenerate  = new CWidgetBFGenerate(this);
    m_widgetBFList      = new CWidgetBFList(this);
    m_widgetBFView      = new CWidgetBFView(this);
    m_widgetConsol      = new CWidgetConsol(this);
    m_widgetConsol->setVisible(false);
    m_widgetPanelMode   = new CWidgetPanelMode(this);
    m_widgetTreeSat     = new CWidgetTreeSat(this);

    QWidget *wBFViewBFGenerate = new QWidget();
    QVBoxLayout *boxBFViewBFGenerate = new QVBoxLayout();
    boxBFViewBFGenerate->addWidget(m_widgetBFGenerate);
    boxBFViewBFGenerate->addWidget(m_widgetBFView);
    boxBFViewBFGenerate->setMargin(0);
    boxBFViewBFGenerate->setSpacing(0);
    boxBFViewBFGenerate->setStretch(1,100);
    wBFViewBFGenerate->setLayout(boxBFViewBFGenerate);

    QSplitter *spListBFTreeAlg = new QSplitter(Qt::Vertical);
    spListBFTreeAlg->addWidget(m_widgetBFList);
    spListBFTreeAlg->addWidget(m_widgetTreeSat);

    QSplitter *spTreeView = new QSplitter(Qt::Horizontal);
    spTreeView->addWidget(spListBFTreeAlg);
    spTreeView->addWidget(wBFViewBFGenerate);
    spTreeView->setStretchFactor(1,100);

    QSplitter *spMain = new QSplitter(Qt::Vertical);
    spMain->addWidget(spTreeView);
    spMain->addWidget(m_widgetConsol);
    spMain->setStretchFactor(0,100);

    QWidget *widgetCenter = new QWidget(this);
    setCentralWidget(widgetCenter);

    QHBoxLayout *hbox = new QHBoxLayout();
    centralWidget()->setLayout(hbox);

    hbox->addWidget(m_widgetPanelMode);
    hbox->addWidget(spMain);
    hbox->setMargin(0);
    hbox->setSpacing(0);
    hbox->setStretch(1,100);

    m_actOpen = new QAction(QIcon(":/ico/main_open.png"),tr("&Открыть"),this);
    m_actOpen->setShortcut(QKeySequence::Open);
    connect(m_actOpen,SIGNAL(triggered()),this,SLOT(on_open()));

    m_actSave = new QAction(QIcon(":/ico/main_save.png"),tr("&Сохранить"),this);
    m_actSave->setShortcut(QKeySequence::Save);
    connect(m_actSave,SIGNAL(triggered()),this,SLOT(on_save()));

    m_actSaveAs = new QAction(QIcon(":/ico/main_save_as.png"),tr("&Сохранить как"),this);
    m_actSaveAs->setShortcut(QKeySequence::SaveAs);
    connect(m_actSaveAs,SIGNAL(triggered()),this,SLOT(on_save_as()));

    m_actQuit = new QAction(QIcon("://ico/main_quit.png"),tr("Выйти"),this);
    m_actQuit->setShortcut(QKeySequence::Close);
    m_actQuit->setStatusTip(tr("Выйти из приложения"));
    connect(m_actQuit, SIGNAL(triggered()), this, SLOT(close()));

    mainMenu = menuBar()->addMenu(tr("Файл"));
    mainMenu->addAction(m_actOpen);
    mainMenu->addAction(m_actSave);
    mainMenu->addAction(m_actSaveAs);
    mainMenu->addSeparator();
    mainMenu->addAction(m_actQuit);

    mainMenu = menuBar()->addMenu(tr("Вид"));
    mainMenu->addAction(m_widgetBFGenerate->actVisible());
    mainMenu->addAction(m_widgetConsol->actVisible());

    // m_widgetPanelMode
    connect(m_widgetPanelMode,SIGNAL(run()),
            m_widgetTreeSat,SLOT(on_runChecked()));

    connect(m_widgetPanelMode,SIGNAL(run()),
            m_widgetBFGenerate,SLOT(on_resetTriggered()));

    connect(m_widgetPanelMode,SIGNAL(runLog()),
            m_widgetTreeSat,SLOT(on_runLogChecked()));

    connect(m_widgetPanelMode,SIGNAL(runLog()),
            m_widgetBFGenerate,SLOT(on_resetTriggered()));

    connect(m_widgetPanelMode,SIGNAL(terminate()),
            this,SIGNAL(terminated()));

    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetBFList,SLOT(setVisible(bool)));
    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetBFList,SLOT(on_disabledHide(bool)));

    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetBFGenerate,SLOT(setVisible(bool)));
    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetBFGenerate->actVisible(),SLOT(setChecked(bool)));
    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetBFGenerate->actVisible(),SLOT(setEnabled(bool)));

    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetTreeSat,SLOT(setVisible(bool)));
    connect(m_widgetPanelMode,SIGNAL(toggledRand(bool)),
            m_widgetTreeSat,SLOT(on_disabledHide(bool)));

    // m_widgetBFView
    connect(m_widgetBFView,SIGNAL(message(QString)),
            this,SIGNAL(messageAppend(QString)));

    connect(m_widgetBFView,SIGNAL(getLogSelectSat(bool)),
            m_widgetTreeSat,SLOT(on_returnLogSelectSat(bool)));

    // m_widgetBFList
    connect(m_widgetBFList,SIGNAL(generate()),
            m_widgetBFGenerate,SLOT(on_generate()));

    connect(m_widgetBFList,SIGNAL(selected(QString,CBoolFormula*)),
            m_widgetBFGenerate,SLOT(on_set(QString,CBoolFormula*)));

    connect(m_widgetBFList,SIGNAL(selected(QString,CBoolFormula*)),
            m_widgetTreeSat,SLOT(on_set(QString,CBoolFormula*)));

    connect(m_widgetBFList,SIGNAL(selected(QString,CBoolFormula*)),
            m_widgetBFView,SLOT(on_set(QString,CBoolFormula*)));

    connect(m_widgetBFList,SIGNAL(message(QString)),
            this,SIGNAL(messageAppend(QString)));

    // m_widgetBFGenerate
    connect(m_widgetBFGenerate,SIGNAL(append(QString,CBoolFormula*)),
            m_widgetBFList,SIGNAL(appendgen(QString,CBoolFormula*)));

    connect(m_widgetBFGenerate,SIGNAL(append(QString,CBoolFormula*)),
            m_widgetPanelMode,SLOT(on_resetTriggered()));

    connect(m_widgetBFGenerate,SIGNAL(execut(QList<CExecutObject*>)),
            this,SLOT(on_execut(QList<CExecutObject*>)));

    connect(m_widgetBFGenerate,SIGNAL(replace(QString,CBoolFormula*)),
            m_widgetBFList,SIGNAL(replace(QString,CBoolFormula*)));

    connect(m_widgetBFGenerate,SIGNAL(replace(QString,CBoolFormula*)),
            m_widgetPanelMode,SLOT(on_resetTriggered()));

    connect(m_widgetBFGenerate,SIGNAL(remove(QString)),
            m_widgetBFList,SIGNAL(remove(QString)));

    connect(m_widgetBFGenerate,SIGNAL(terminated()),
            this,SIGNAL(terminated()));

    // m_widgetTreeSat
    connect(m_widgetTreeSat,SIGNAL(execut(QList<CExecutObject*>)),
            this,SLOT(on_execut(QList<CExecutObject*>)));

    connect(m_widgetTreeSat,SIGNAL(logSelectSat(QString)),
            m_widgetBFView,SIGNAL(setText(QString)));

    // main
    connect(this,SIGNAL(messageAppend(QString)),
            m_widgetConsol,SLOT(messageAppend(QString)));

    connect(this,SIGNAL(messageSet(QString)),
            m_widgetConsol,SLOT(messageSet(QString)));

    connect(this,SIGNAL(executingOperation(QString)),
            m_widgetConsol,SLOT(executingOperation(QString)));

    connect(this,SIGNAL(append(QString,CBoolFormula*)),
            m_widgetBFList,SIGNAL(append(QString,CBoolFormula*)));

    connect(this,SIGNAL(locked()),m_widgetPanelMode,SLOT(on_locked()));
    connect(this,SIGNAL(unlocked()),m_widgetPanelMode,SLOT(on_unlocked()));

    connect(this,SIGNAL(locked()),m_widgetBFGenerate,SLOT(on_locked()));
    connect(this,SIGNAL(unlocked()),m_widgetBFGenerate,SLOT(on_unlocked()));

    connect(this,SIGNAL(updateView()),m_widgetBFView,SLOT(on_viewUpdate()));

    m_widgetPanelMode->on_checkedRand();  // set checked Random bool formula state for start application
}