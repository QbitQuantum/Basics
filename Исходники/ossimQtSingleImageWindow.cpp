ossimQtSingleImageWindow::ossimQtSingleImageWindow(QWidget* parent,
        const char* name,
        Qt::WFlags f)
    : QMainWindow(parent, name, f),
      ossimConnectableObject(),
      ossimConnectableDisplayListener(),
      theImageWidget(0),
      theLastOpenedDirectory(),
      theResolutionLevelMenu(0)
{
    ossimReferenced::ref();
    setCaption("iview");

    QSize size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setBaseSize(size);

    // This set the window's widget size.
    setGeometry(0,0,DEFAULT_WIDTH-1,DEFAULT_HEIGHT-1);

    // Create the image widget parenting it to this.
    theImageWidget = new ossimQtScrollingImageWidget(this, "image_widget");

    // This will clear out any initial garbage in the widget.
    theImageWidget->refresh();

    // Disable random caching scheme.
    theImageWidget->setRandomPriorityQueueEnabledFlag(false);

    // Set the the width and height of the window.
    theImageWidget->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    // Make the image widget the centralized widget.
    setCentralWidget(theImageWidget);

    // Make the "File" pull down menu.
    QMenu* file = new QMenu( this );
    menuBar()->insertItem( "&File", file );
    file->insertItem( "&Open Image",  this, SLOT(openImage()), Qt::CTRL+Qt::Key_O );
    file->insertItem( "&Close Image",  this, SLOT(closeImage()), Qt::CTRL+Qt::Key_C );
    file->insertItem( "&Export",  this, SLOT(exportImage()), Qt::CTRL+Qt::Key_E );
    file->insertItem( "&Quit",  this, SLOT(closeWindow()), Qt::CTRL+Qt::Key_Q );

    // Make the "Edit" pull down menu.
    QMenu* edit = new QMenu( this );
    menuBar()->insertItem( "&Edit", edit );
    edit->insertItem( "Image Chain",  this, SLOT(editImageChain()));

    // Make the "Utilities" pull down menu.
    QMenu* utilities = new QMenu( this );
    menuBar()->insertItem( "&Utilities", utilities );
    utilities->insertItem( "Refresh",  this, SLOT(refreshDisplay()));

    // Make the "Resolution_Level" pull down menu.
    theResolutionLevelMenu = new QMenu( this );
    menuBar()->insertItem( "&Resolution_Level",  theResolutionLevelMenu);

    QAction* rsetAct = new QAction(QString("0"), this);
    rsetAct->setCheckable(true);
    rsetAct->setChecked(true);
    rsetAct->setData(0);
    rsetAct->setEnabled(false);

    theResolutionLevelMenu->addAction( rsetAct );

    // Connect the activated signal to the changeResolutionLevel slot.
    connect( theResolutionLevelMenu, SIGNAL( triggered( QAction * ) ),
             this, SLOT ( changeResolutionLevel( QAction * ) ) );

    // Make the "Help" pull down menu.
    QMenu* help = new QMenu( this );
    menuBar()->insertItem( "&Help", help );
    help->insertItem( "&About",  this, SLOT(about()), Qt::CTRL+Qt::Key_A );

    // Connect up the slot to capture mouse events.
    connect(theImageWidget,
            SIGNAL(scrollingImageWidgetMouseEvent(ossimQtMouseEvent*)),
            this,
            SLOT(trackImageWidget(ossimQtMouseEvent*)));

    // Add us in as a listener for display events like refresh.
    addListener((ossimConnectableDisplayListener*)this);

    //---
    // Connect this display up to "theImageWidget" so that event propagation
    // comes up the chain to us.
    //---
    connectMyInputTo(theImageWidget);

    // Send a dummy message to make the status bar show.
    statusBar()->message( QString(" ") );

    //---
    // Set the last open directory to the current working dir so the open image
    // dialog will come up where you started.
    //---
    theLastOpenedDirectory = getenv("PWD");
}