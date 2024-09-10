void DoNothingPlugin::createMenus()
{
    // Fetch the action manager
    Core::ActionManager* am = Core::ICore::instance()->actionManager();

    // Create a DoNothing menu
    Core::ActionContainer* ac = am->createMenu("DoNothingPlugin.DoNothingMenu");
    ac->menu()->setTitle(tr("DoNothing"));

    // Create a command for "About DoNothing".
    Core::Command* cmd = am->registerAction(new QAction(this), "DoNothingPlugin.AboutDoNothing", QList<int>() << 0);
    cmd->action()->setText("About DoNothing");

    // Add DoNothing menu to the beginning of the menu bar
    am->actionContainer(Core::Constants::MENU_BAR)->addMenu(ac);

    // Add the "About DoNothing" action to the DoNothing menu
    ac->addAction(cmd);

    // Connect the action
    connect(cmd->action(), SIGNAL(triggered(bool)), this, SLOT(about()));

    // Create a DoNothing2 menu
    Core::ActionContainer* ac2 = am->createMenu("DoNothingPlugin.DoNothing2Menu");
    ac2->menu()->setTitle(tr("DoNothing2"));

    // Create a command for "About DoNothing 2".
    Core::Command* cmd2 = am->registerAction(new QAction(this), "DoNothingPlugin.AboutDoNothing2", QList<int>() << 0);
    cmd2->action()->setText("About DoNothing 2");

    // Insert the "DoNothing" menu between "Window" and "Help".
    QMenu* helpMenu = am->actionContainer(Core::Constants::M_HELP)->menu();
    QMenuBar* menuBar = am->actionContainer(Core::Constants::MENU_BAR)->menuBar();
    menuBar->insertMenu(helpMenu->menuAction(), ac2->menu());

    // Add the "About DoNothing 2" action to the DoNothing2 menu
    ac2->addAction(cmd2);

    // Connect the action
    connect(cmd2->action(), SIGNAL(triggered(bool)), this, SLOT(about()));
}