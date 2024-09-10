MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "MainForm" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
    MainFormLayout = new QVBoxLayout( centralWidget(), 11, 6, "MainFormLayout"); 

    listView = new QListView( centralWidget(), "listView" );
    listView->addColumn( tr( "Type" ) );
    listView->addColumn( tr( "Name" ) );
    listView->addColumn( tr( "Login" ) );
    listView->addColumn( tr( "Password" ) );
    listView->addColumn( tr( "Description" ) );
    listView->setResizeMode( QListView::AllColumns );
    listView->setSorting(-1);
    MainFormLayout->addWidget( listView );

    // actions
    createProfileAction = new QAction( this, "createProfileAction" );
    createProfileAction->setIconSet( QPixmap::fromMimeSource("new.png") );
    openProfileAction = new QAction(this, "openProfileAction" );
    openProfileAction->setIconSet( QPixmap::fromMimeSource("open.png") );
    tb_openProfileAction = new QAction(this, "tb_openProfileAction");
    tb_openProfileAction->setIconSet( QPixmap::fromMimeSource("tb_open.png") );
    closeProfileAction = new QAction( this, "closeProfileAction" );
    closeProfileAction->setIconSet( QPixmap::fromMimeSource("close.png") );
    tb_closeProfileAction = new QAction( this, "tb_closeProfileAction" );
    tb_closeProfileAction->setIconSet( QPixmap::fromMimeSource("tb_close.png") );
    deleteProfileAction = new QAction( this, "deleteProfileAction" );
    deleteProfileAction->setIconSet( QPixmap::fromMimeSource("delete_all.png") );
    changeProfileAction = new QAction( this, "changeProfileAction" );
    fileQuitAction = new QAction( this, "fileQuitAction" );
    fileSaveAction = new QAction( this, "fileSaveAction" );
    fileSaveAction->setIconSet( QPixmap::fromMimeSource("save.png") );
    tb_fileSaveAction = new QAction( this, "tb_fileSaveAction" );
    tb_fileSaveAction->setIconSet( QPixmap::fromMimeSource("tb_save.png") );
    editUndoAction = new QAction( this, "editUndoAction" );
    editUndoAction->setIconSet( QPixmap::fromMimeSource("undo.png") );
    tb_editUndoAction = new QAction( this, "editUndoAction" );
    tb_editUndoAction->setIconSet( QPixmap::fromMimeSource("tb_undo.png") );
    editRedoAction = new QAction( this, "editRedoAction" );
    editRedoAction->setIconSet( QPixmap::fromMimeSource("redo.png") );
    tb_editRedoAction = new QAction( this, "tb_editRedoAction" );
    tb_editRedoAction->setIconSet( QPixmap::fromMimeSource("tb_redo.png") );
    editNewField = new QAction( this, "editNewField" );
    editNewField->setIconSet( QPixmap::fromMimeSource("new.png") );
    editEditField = new QAction( this, "editEditField" );
    editEditField->setIconSet( QPixmap::fromMimeSource("edit.png") );
    tb_editEditField = new QAction( this, "tb_editEditField" );
    tb_editEditField->setIconSet( QPixmap::fromMimeSource("tb_edit.png") );
    tb_editNewField = new QAction( this, "tb_editNewField" );
    tb_editNewField->setIconSet( QPixmap::fromMimeSource("tb_new.png") );
    editDeleteField = new QAction( this, "editDeleteField" );
    editDeleteField->setIconSet( QPixmap::fromMimeSource("delete.png") );
    tb_editDeleteField = new QAction( this, "tb_editDeleteField" );
    tb_editDeleteField->setIconSet( QPixmap::fromMimeSource("tb_delete.png") );
    editDeleteAll = new QAction( this, "editDeleteAll" );
    editDeleteAll->setIconSet( QPixmap::fromMimeSource("delete_all.png") );
    helpAboutAction = new QAction( this, "helpAboutAction" );


    // toolbars
    fileToolbar = new QToolBar( tr("File"), this, DockTop );
    tb_openProfileAction->addTo( fileToolbar);
    tb_fileSaveAction->addTo( fileToolbar);
    tb_closeProfileAction->addTo( fileToolbar );
    
    editToolbar = new QToolBar( tr("Edit"), this, DockTop );
    tb_editUndoAction->addTo( editToolbar );
    tb_editRedoAction->addTo( editToolbar );
    editToolbar->addSeparator();
    tb_editNewField->addTo( editToolbar );
    tb_editEditField->addTo( editToolbar );
    tb_editDeleteField->addTo( editToolbar );

    // menubar
    MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


    File = new QPopupMenu( this );
    createProfileAction->addTo( File );
    openProfileAction->addTo( File );
    fileSaveAction->addTo( File );
    closeProfileAction->addTo( File );
    deleteProfileAction->addTo( File );
    changeProfileAction->addTo( File );
    File->insertSeparator();
    fileQuitAction->addTo( File );
    MenuBarEditor->insertItem( QString(""), File, 1 );
    
    Edit = new QPopupMenu( this );
    editUndoAction->addTo( Edit );
    editRedoAction->addTo( Edit );
    Edit->insertSeparator();
    editNewField->addTo( Edit );
    editEditField->addTo( Edit );
    editDeleteField->addTo( Edit );
    editDeleteAll->addTo(Edit);
    MenuBarEditor->insertItem( QString(""), Edit, 2 );
    
    Help = new QPopupMenu( this );
    helpAboutAction->addTo( Help );
    MenuBarEditor->insertItem( QString(""), Help, 3 );
    
    rmbMenu = new QPopupMenu( this );
    editUndoAction->addTo( rmbMenu );
    editRedoAction->addTo( rmbMenu );
    rmbMenu->insertSeparator();
    editNewField->addTo( rmbMenu );
    editEditField->addTo( rmbMenu );
    editDeleteField->addTo( rmbMenu );

    languageChange();
    resize( QSize(700, 400).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    connect(createProfileAction, SIGNAL( activated() ), this, SLOT( createProfile() )  );
    connect(openProfileAction, SIGNAL( activated() ), this, SLOT( openProfile() )  );
    connect(tb_openProfileAction, SIGNAL( activated() ), this, SLOT( openProfile() ) );
    connect(closeProfileAction, SIGNAL( activated() ), this, SLOT( closeProfile() )  );
    connect(tb_closeProfileAction, SIGNAL( activated() ), this, SLOT( closeProfile() )  );
    connect(deleteProfileAction, SIGNAL( activated() ), this, SLOT( deleteProfile() ) );
    connect(changeProfileAction, SIGNAL( activated() ), this, SLOT( changeProfile() ) );
    connect(fileSaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(tb_fileSaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(fileQuitAction, SIGNAL( activated() ), this, SLOT( close() ) );
    connect(editUndoAction, SIGNAL( activated() ), this, SLOT( undo() ) );
    connect(tb_editUndoAction, SIGNAL( activated() ), this, SLOT( undo() ) );
    connect(editRedoAction, SIGNAL( activated() ), this, SLOT( redo() ) );
    connect(tb_editRedoAction, SIGNAL( activated() ), this, SLOT( redo() ) );
    connect(editNewField, SIGNAL( activated() ), this, SLOT( newField() ) );
    connect(tb_editNewField, SIGNAL( activated() ), this, SLOT( newField() ) );
    connect(editEditField, SIGNAL(activated() ), this, SLOT( editField() ) );
    connect(tb_editEditField, SIGNAL(activated() ), this, SLOT( editField() ) );
    connect(editDeleteField, SIGNAL( activated() ), this, SLOT( deleteField() ) );
    connect(tb_editDeleteField, SIGNAL( activated() ), this, SLOT( deleteField() ) );
    connect(editDeleteAll, SIGNAL( activated() ), this, SLOT( deleteAll() ) );
    connect(helpAboutAction, SIGNAL( activated() ), this, SLOT( about() ) );
    
    connect(listView, SIGNAL( doubleClicked(QListViewItem *) ), this, SLOT( edit(QListViewItem *) ) );
    connect(listView, SIGNAL( contextMenuRequested( QListViewItem *, const QPoint&, int) ), this, SLOT( slotRMB( QListViewItem*, const QPoint &, int ) ) );
    
    modified = false;
    Caption();
    
    if(!ifProfileExists())
	    createProfile();
    else
	    setEnabledActions(1);
}