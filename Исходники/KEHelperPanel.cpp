void HelperPanel::createIntrospectionTreeTab(TabPanel* const tabPanel)
{
    BorderLayoutConstraintsRefPtr CenterConstraints = OSG::BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    BorderLayoutConstraintsRefPtr NorthConstraints = OSG::BorderLayoutConstraints::create();
    NorthConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);


    _GlobalLuaIntroTreeModel = LuaIntrospectionTreeModel::create();
    _GlobalLuaIntroTreeModel->setRoot("");

    LuaIntrospectionComponentGeneratorRecPtr LuaIntroTreeComponentGenerator = LuaIntrospectionComponentGenerator::create();

    //Create the Tree
    TreeRecPtr TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(200, 500));
    TheTree->setModel(_GlobalLuaIntroTreeModel);
    TheTree->setCellGenerator(LuaIntroTreeComponentGenerator);

    //Layout Expansion
    TheTree->expandPath(_GlobalLuaIntroTreeModel->getRootPath());

    //Create a scroll panel for the tree
    ScrollPanelRefPtr TreeScrollPanel = ScrollPanel::create();
    TreeScrollPanel->setPreferredSize(Vec2f(200,300));
    TreeScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    TreeScrollPanel->setViewComponent(TheTree);
    TreeScrollPanel->setConstraints(CenterConstraints);

    //Global Label
    LabelRecPtr GlobalTreeLabel = Label::create();
    GlobalTreeLabel->setText("Global");
    GlobalTreeLabel->setConstraints(NorthConstraints);

    BorderLayoutRecPtr BorderPanelLayout = BorderLayout::create();

    //Global Panel
    PanelRecPtr GlobalLuaTreePanel = Panel::createEmpty();
    GlobalLuaTreePanel->pushToChildren(GlobalTreeLabel);
    GlobalLuaTreePanel->pushToChildren(TreeScrollPanel);
    GlobalLuaTreePanel->setLayout(BorderPanelLayout);

    //Local Label
    LabelRecPtr LocalTreeLabel = Label::create();
    LocalTreeLabel->setText("Local");
    LocalTreeLabel->setConstraints(NorthConstraints);

    //Local Panel
    PanelRecPtr LocalLuaTreePanel = Panel::createEmpty();
    LocalLuaTreePanel->pushToChildren(LocalTreeLabel);
    LocalLuaTreePanel->setLayout(BorderPanelLayout);

    //Global/Local Split Panel
    SplitPanelRecPtr GlocalLocalSplitPanel = SplitPanel::create();
    GlocalLocalSplitPanel->setMinComponent(GlobalLuaTreePanel);
    GlocalLocalSplitPanel->setMaxComponent(LocalLuaTreePanel);
    GlocalLocalSplitPanel->setDividerPosition(0.5f);
    GlocalLocalSplitPanel->setDividerSize(5);
    GlocalLocalSplitPanel->setMinDividerPosition(.1);
    GlocalLocalSplitPanel->setMaxDividerPosition(.9);
    

    //Add the Panel to the TabPanel
    LabelRefPtr IntrospectionTreeTabLabel = Label::create();
    IntrospectionTreeTabLabel->setText("Lua Introspection");
    IntrospectionTreeTabLabel->setBorders(NULL);
    IntrospectionTreeTabLabel->setBackgrounds(NULL);

    tabPanel->addTab(IntrospectionTreeTabLabel, GlocalLocalSplitPanel);
}