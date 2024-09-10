MainToolBar::MainToolBar(QWidget *parent)
    : QToolBar(parent)
    , mCommandButton(new CommandButton(this))
{
    setObjectName(QLatin1String("MainToolBar"));
    setWindowTitle(tr("Main Toolbar"));
    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    QIcon newIcon(QLatin1String(":images/24x24/document-new.png"));
    QIcon openIcon(QLatin1String(":images/24x24/document-open.png"));
    QIcon saveIcon(QLatin1String(":images/24x24/document-save.png"));
    QIcon undoIcon(QLatin1String(":images/24x24/edit-undo.png"));
    QIcon redoIcon(QLatin1String(":images/24x24/edit-redo.png"));

    newIcon.addFile(QLatin1String(":images/16x16/document-new.png"));
    openIcon.addFile(QLatin1String(":images/16x16/document-open.png"));
    saveIcon.addFile(QLatin1String(":images/16x16/document-save.png"));
    redoIcon.addFile(QLatin1String(":images/16x16/edit-redo.png"));
    undoIcon.addFile(QLatin1String(":images/16x16/edit-undo.png"));

    mNewButton = new QToolButton(this);
    mOpenAction = new QAction(this);
    mSaveAction = new QAction(this);

    QMenu *newMenu = new QMenu(this);
    newMenu->addAction(ActionManager::action("NewMap"));
    newMenu->addAction(ActionManager::action("NewTileset"));
    mNewButton->setMenu(newMenu);
    mNewButton->setPopupMode(QToolButton::InstantPopup);

    QUndoGroup *undoGroup = DocumentManager::instance()->undoGroup();
    mUndoAction = undoGroup->createUndoAction(this, tr("Undo"));
    mRedoAction = undoGroup->createRedoAction(this, tr("Redo"));

    mNewButton->setIcon(newIcon);
    mOpenAction->setIcon(openIcon);
    mSaveAction->setIcon(saveIcon);
    mUndoAction->setIcon(undoIcon);
    mRedoAction->setIcon(redoIcon);

    Utils::setThemeIcon(mNewButton, "document-new");
    Utils::setThemeIcon(mOpenAction, "document-open");
    Utils::setThemeIcon(mSaveAction, "document-save");
    Utils::setThemeIcon(mRedoAction, "edit-redo");
    Utils::setThemeIcon(mUndoAction, "edit-undo");

    mRedoAction->setPriority(QAction::LowPriority);

    addWidget(mNewButton);
    addAction(mOpenAction);
    addAction(mSaveAction);
    addSeparator();
    addAction(mUndoAction);
    addAction(mRedoAction);
    addSeparator();
    addWidget(mCommandButton);

    DocumentManager *documentManager = DocumentManager::instance();
    connect(mOpenAction, &QAction::triggered, documentManager, &DocumentManager::openFileDialog);
    connect(mSaveAction, &QAction::triggered, documentManager, &DocumentManager::saveFile);

    connect(documentManager, &DocumentManager::currentDocumentChanged,
            this, &MainToolBar::currentDocumentChanged);

    connect(this, &MainToolBar::orientationChanged,
            this, &MainToolBar::onOrientationChanged);

    retranslateUi();
}