void QtTestPlugin::extensionsInitialized()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Core::ICore *core = Core::ICore::instance();
    Core::ActionManager *am = core->actionManager();

    m_messageOutputWindow = new TestOutputWindow();
    pm->addObject(m_messageOutputWindow);

    m_testResultsWindow = TestResultsWindow::instance();
    connect(m_testResultsWindow, SIGNAL(stopTest()), this, SLOT(stopTesting()));
    connect(m_testResultsWindow, SIGNAL(retryFailedTests(QStringList)),
        this, SLOT(retryTests(QStringList)));
    connect(TestExecuter::instance(), SIGNAL(testStarted()),
        m_testResultsWindow, SLOT(onTestStarted()));
    connect(TestExecuter::instance(), SIGNAL(testStop()),
        m_testResultsWindow, SLOT(onTestStopped()));
    connect(TestExecuter::instance(), SIGNAL(testFinished()),
        m_testResultsWindow, SLOT(onTestFinished()));
    pm->addObject(m_testResultsWindow);
    connect(testResultsPane(), SIGNAL(defectSelected(TestCaseRec)),
        this, SLOT(onDefectSelected(TestCaseRec)));

    // Add context menu to CPP editor
    Core::ActionContainer *mcontext = am->actionContainer(CppEditor::Constants::M_CONTEXT);
    m_contextMenu->init(mcontext->menu(), 2, this);

    // Add context menu to JS editor
    mcontext = am->actionContainer(QmlJSEditor::Constants::M_CONTEXT);
    m_contextMenu->init(mcontext->menu(), 2, this);

    // Add a Test menu to the menu bar
    Core::ActionContainer* ac = am->createMenu("QtTestPlugin.TestMenu");
    ac->menu()->setTitle(tr("&Test"));
    m_contextMenu->init(ac->menu(), 0, 0);

    // Insert the "Test" menu between "Window" and "Help".
    QMenu *windowMenu = am->actionContainer(Core::Constants::M_TOOLS)->menu();
    QMenuBar *menuBar = am->actionContainer(Core::Constants::MENU_BAR)->menuBar();
    menuBar->insertMenu(windowMenu->menuAction(), ac->menu());

    ProjectExplorer::ProjectExplorerPlugin *explorer =
        ProjectExplorer::ProjectExplorerPlugin::instance();

    connect(explorer->session(), SIGNAL(startupProjectChanged(ProjectExplorer::Project*)),
        this, SLOT(onStartupProjectChanged(ProjectExplorer::Project *)));

    connect(core->progressManager(), SIGNAL(allTasksFinished(QString)),
        this, SLOT(onAllTasksFinished(QString)));

    connect(explorer->session(), SIGNAL(aboutToRemoveProject(ProjectExplorer::Project *)),
        this, SLOT(onProjectRemoved(ProjectExplorer::Project *)));

    m_contextMenu->init(0, 3, this);
}