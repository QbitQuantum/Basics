void NMainMenuBar::setupEditMenu() {
    editMenu = this->addMenu(tr("&Edit"));
    QFont f = global.getGuiFont(QFont());
    editMenu->setFont(f);

    undoAction = new QAction(tr("&Undo"), this);
    setupShortcut(undoAction, QString("Edit_Undo"));
    editMenu->addAction(undoAction);

    redoAction = new QAction(tr("&Redo"), this);
    setupShortcut(redoAction, QString("Edit_Redo"));
    editMenu->addAction(redoAction);

    editMenu->addSeparator();

    cutAction = new QAction(tr("&Cut"), this);
    setupShortcut(cutAction, QString("Edit_Cut"));
    editMenu->addAction(cutAction);

    copyAction = new QAction(tr("C&opy"), this);
    setupShortcut(copyAction, QString("Edit_Copy"));
    editMenu->addAction(copyAction);

    pasteAction = new QAction(tr("&Paste"), this);
    setupShortcut(pasteAction, QString("Edit_Paste"));
    editMenu->addAction(pasteAction);

    pasteAsTextAction = new QAction(tr("Pas&te as Unformatted Text"), this);
    setupShortcut(pasteAsTextAction, QString("Edit_Paste_Without_Formatting"));
    editMenu->addAction(pasteAsTextAction);

    removeFormattingAction = new QAction(tr("Remo&ve Formatting"), this);
    //setupShortcut(removeFormjattingAction, QString("Edit_Remove_Formatting")); // For some reason this one makes the editorButtonBar one ambiguous
    editMenu->addAction(removeFormattingAction);

    editMenu->addSeparator();

    selectAllAction = new QAction(tr("Select &All"), this);
    setupShortcut(selectAllAction, QString("Edit_Select_All"));
    editMenu->addAction(selectAllAction);

    editMenu->addSeparator();

    findReplaceMenu = editMenu->addMenu(tr("F&ind and Replace"));
    findReplaceMenu->setFont(f);

    searchNotesAction = new QAction(tr("&Search Notes"), this);
    setupShortcut(searchNotesAction, QString("Edit_Search_Notes"));
    findReplaceMenu->addAction(searchNotesAction);
    connect(searchNotesAction, SIGNAL(triggered()), parent->searchText, SLOT(setFocus()));

    resetSearchAction = new QAction(tr("&Reset Search"), this);
    setupShortcut(resetSearchAction, QString("Edit_Reset_Search"));
    findReplaceMenu->addAction(resetSearchAction);
    connect(resetSearchAction, SIGNAL(triggered()), parent, SLOT(resetView()));

    findReplaceMenu->addSeparator();

    searchFindAction = new QAction(tr("&Find in Note"), this);
    setupShortcut(searchFindAction, QString("Edit_Search_Find"));
    findReplaceMenu->addAction(searchFindAction);
    connect(searchFindAction, SIGNAL(triggered()), parent, SLOT(findInNote()));


    searchFindNextAction = new QAction(tr("Find &Next"), this);
    setupShortcut(searchFindNextAction, QString("Edit_Search_Find_Next"));
    findReplaceMenu->addAction(searchFindNextAction);
    connect(searchFindNextAction, SIGNAL(triggered()), parent, SLOT(findNextInNote()));

    searchFindPrevAction = new QAction(tr("Find &Previous"), this);
    setupShortcut(searchFindPrevAction, QString("Edit_Search_Find_Prev"));
    findReplaceMenu->addAction(searchFindPrevAction);
    connect(searchFindPrevAction, SIGNAL(triggered()), parent, SLOT(findPrevInNote()));

    findReplaceMenu->addSeparator();

    searchFindReplaceAction = new QAction(tr("Replace &Within Note..."), this);
    setupShortcut(searchFindReplaceAction, QString("Edit_Search_Find_Replace"));
    findReplaceMenu->addAction(searchFindReplaceAction);
    connect(searchFindReplaceAction, SIGNAL(triggered()), parent, SLOT(findReplaceInNote()));

    editMenu->addSeparator();

    createThemeMenu(editMenu);

    preferencesAction = new QAction(tr("Preferences"), this);
    preferencesAction->setMenuRole(QAction::PreferencesRole);
    setupShortcut(preferencesAction, QString("Edit_Preferences"));
    editMenu->addAction(preferencesAction);
    connect(preferencesAction, SIGNAL(triggered()), parent, SLOT(openPreferences()));

}