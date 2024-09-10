void VcsManager::registerActions()
{
    ActionManager *manager = ActionManager::instance();

    ActionContainer* mVcs = manager->createMenu("VCS");

    manager->actionContainer(Constants::MENU_BAR)->addMenu(mVcs, Constants::M_VCS);

    QAction* commitChanges = new QAction("Commit changes...");
    manager->registerAction(commitChanges);

    QAction* updateProject = new QAction("Update project...");
    manager->registerAction(updateProject);


    QAction* createPatch = new QAction("Create Patch...");
    manager->registerAction(updateProject);

    QAction* applyPatch = new QAction("Apply Patch...");
    manager->registerAction(applyPatch);


}