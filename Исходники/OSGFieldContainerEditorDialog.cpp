DialogWindowTransitPtr createFCTreeEditorDialog       (FieldContainer* fc, 
                                                                                       CommandManagerPtr CmdManager,
                                                                                       const std::string& editorName)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();



    //Create the FieldEditorComponent
    FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(fc, CmdManager);
    ScrollPanelRefPtr EditorScrollPanel = ScrollPanel::create();
    EditorScrollPanel->setViewComponent(TheEditor);

    //Field Container Tree Model
    FieldContainerTreeModelRefPtr TheTreeModel = FieldContainerTreeModel::create();
    TheTreeModel->setRoot(fc);
    TheTreeModel->setShowInternalFields(true);
    TheTreeModel->setShowPtrFields(true);
    TheTreeModel->setShowDataFields(false);
    TheTreeModel->setShowParentPtrFields(false);
    TheTreeModel->setShowChildPtrFields(true);
    TheTreeModel->setShowAttachments(true);
    TheTreeModel->setShowCallbackFunctors(false);

    //Field Container Tree Component Generator
    FieldContainerFieldPathComponentGeneratorRefPtr TheTreeComponentGenerator = FieldContainerFieldPathComponentGenerator::create();

    //Create the PopupMenu for the tree
    MenuItemRecPtr ExportMenuItem = MenuItem::create();
    ExportMenuItem->setText("Export ...");

    MenuItemRecPtr ImportMenuItem = MenuItem::create();
    ImportMenuItem->setText("Import ...");

    PopupMenuRecPtr TreePopupMenu = PopupMenu::create();
    TreePopupMenu->addItem(ExportMenuItem);
    TreePopupMenu->addItem(ImportMenuItem);


    //Create the Field Container Tree
    TreeRefPtr TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setRootVisible(true);
    TheTree->setModel(TheTreeModel);
    TheTree->setCellGenerator(TheTreeComponentGenerator);
    TheTree->setPopupMenu(TreePopupMenu);

    TheTree->getSelectionModel()->connectSelectionAdded(boost::bind(&handleFCSelectionAdded, _1,
                                                                    TheTree.get(),
                                                                    EditorScrollPanel.get()));

    ExportMenuItem->connectActionPerformed(boost::bind(&handleTreeNodeExport,
                                                       _1,
                                                       TheTree.get()));

    ImportMenuItem->connectActionPerformed(boost::bind(&handleTreeNodeImport,
                                                       _1,
                                                       TheTree.get()));
    //TheDialog->addTransientObject(boost::any(TheTreeEditorSelectionListener));

    ScrollPanelRefPtr TreeScrollPanel = ScrollPanel::create();
    TreeScrollPanel->setViewComponent(TheTree);

    //Ok button
    ButtonRefPtr ConfirmButton = Button::create();
    ConfirmButton->setText("Ok");
    ConfirmButton->connectActionPerformed(boost::bind(&DialogWindow::handleConfirmButtonAction, TheDialog.get(), _1));

    SpringLayoutRefPtr DialogLayout = OSG::SpringLayout::create();

    //SplitPanel
    SplitPanelRefPtr TheSplitPanel = SplitPanel::create();
    TheSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
    TheSplitPanel->setDividerPosition(0.4f);
    TheSplitPanel->setDividerSize(5.0f);
    TheSplitPanel->setMaxDividerPosition(0.8f);
    TheSplitPanel->setMinDividerPosition(0.2f);
    TheSplitPanel->setMinComponent(TreeScrollPanel);
    TheSplitPanel->setMaxComponent(EditorScrollPanel);
    
    //TreeScrollPanel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheSplitPanel, 2, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheSplitPanel, -15, SpringLayoutConstraints::NORTH_EDGE, ConfirmButton);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheSplitPanel, -2, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheSplitPanel, 2, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    
    //ConfirmButton
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ConfirmButton, -15, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, ConfirmButton, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);

    
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(750.0f, 600.0f));
    TheDialog->pushToChildren(TheSplitPanel);
    TheDialog->pushToChildren(ConfirmButton);

    return DialogWindowTransitPtr(TheDialog);
}