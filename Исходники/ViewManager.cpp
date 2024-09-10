void ViewManager::initializeClass(ExtensionManager* ext)
{
    static bool initialized = false;
    if(!initialized){
        
        mainWindow = MainWindow::instance();
        MenuManager& mm = ext->menuManager();
        QWidget* viewMenu = mm.setPath("/View").current();

        QAction* showViewAction = mm.findItem("Show View");
        showViewMenu = new Menu(viewMenu);
        showViewMenu->sigAboutToShow().connect(boost::bind(onViewMenuAboutToShow, showViewMenu));
        showViewAction->setMenu(showViewMenu);

        QAction* createViewAction = mm.setCurrent(viewMenu).findItem("Create View");
        createViewMenu = new Menu(viewMenu);
        createViewMenu->sigAboutToShow().connect(boost::bind(onViewMenuAboutToShow, createViewMenu));
        createViewAction->setMenu(createViewMenu);

        QAction* deleteViewAction = mm.setCurrent(viewMenu).findItem("Delete View");
        deleteViewMenu = new Menu(viewMenu);
        deleteViewMenu->sigAboutToShow().connect(boost::bind(onViewMenuAboutToShow, deleteViewMenu));
        deleteViewAction->setMenu(deleteViewMenu);
        
        initialized = true;
    }
}