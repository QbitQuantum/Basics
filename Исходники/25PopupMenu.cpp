int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************
            
                Create PopupMenu Components
        
        -MenuItem: These are items that are contained
            within a Menu; they are the things you click
            on to cause something to occur
        -SeperatorMenuItem:  These place a seperator 
            line between items in a Menu
        -Menu: These are sub-menus within another Menu;
            MenuItems and SeperatorMenuItems
            are added to a Menu

    ******************************************************/

    MenuItemRefPtr MenuItem1 = MenuItem::create();
    MenuItemRefPtr MenuItem2 = MenuItem::create();
    MenuItemRefPtr MenuItem3 = MenuItem::create();
    MenuItemRefPtr MenuItem4 = MenuItem::create();
    MenuItemRefPtr SubMenuItem1 = MenuItem::create();
    MenuItemRefPtr SubMenuItem2 = MenuItem::create();
    MenuItemRefPtr SubMenuItem3 = MenuItem::create();
    MenuRefPtr ExampleSubMenu = Menu::create();
    
    /******************************************************
            
            Edit the MenuItems

            -setText("TEXT"): Sets the text on the 
                item to be TEXT
            -setEnabled(Boolean): sets the menu item
                to be either enabled or disabled

    ******************************************************/

        MenuItem1->setText("Menu Item 1");
    
        MenuItem2->setText("Menu Item 2");
    
        MenuItem3->setText("Menu Item 3");
    
        MenuItem4->setText("Menu Item 4");
        MenuItem4->setEnabled(false);
    
        SubMenuItem1->setText("SubMenu Item 1");
    
        SubMenuItem2->setText("SubMenu Item 2");
    
        SubMenuItem3->setText("SubMenu Item 3");
    
        ExampleSubMenu->setText("Sub Menu");

    // This adds three MenuItems to the Menu,
    // creating a submenu.  Note this does not
    // involve begin/endEditCPs to do

    ExampleSubMenu->addItem(SubMenuItem1);
    ExampleSubMenu->addItem(SubMenuItem2);
    ExampleSubMenu->addItem(SubMenuItem3);
    
    /******************************************************
            
            Create the PopupMenu itself.

            Items are added in the order in which
            they will be displayed (top to bottom)
            via addItem(ItemToBeAdded)

            The PopupMenu is attached to a 
			Button below using 
			setPopupMenu(PopupMenuName).  
			
			Note: PopupMenus can be added to any
			Component.

    ******************************************************/
    PopupMenuRefPtr ExamplePopupMenu = PopupMenu::create();
    ExamplePopupMenu->addItem(MenuItem1);
    ExamplePopupMenu->addItem(MenuItem2);
    ExamplePopupMenu->addItem(MenuItem3);
    ExamplePopupMenu->addSeparator();
    ExamplePopupMenu->addItem(ExampleSubMenu);
    ExamplePopupMenu->addItem(MenuItem4);
    
    // Create a Button and Font
    UIFontRefPtr PopupMenuButtonFont = OSG::UIFont::create();
        PopupMenuButtonFont->setSize(16);

    ButtonRefPtr PopupMenuButton = OSG::Button::create();
        PopupMenuButton->setText("RightClickMe!");
        // Add the PopupMenu to PopupMenuButton so that when right clicked,
        // the PopupMenu will appear
        PopupMenuButton->setPopupMenu(ExamplePopupMenu);
        PopupMenuButton->setPreferredSize(Vec2f(200,100));
        PopupMenuButton->setFont(PopupMenuButtonFont);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(PopupMenuButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}