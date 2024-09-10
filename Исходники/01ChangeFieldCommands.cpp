PanelUnrecPtr createMultiPtrFieldPanel(void)
{
    //Buttons for Inner Panel
    ButtonRefPtr AButton = Button::create();
    AButton->setText("A");

    ButtonRefPtr BButton = Button::create();
    BButton->setText("B");

    //Inner Panel
    LayoutRefPtr MultiPtrFieldInnerPanelLayout = OSG::FlowLayout::create();

    MultiPtrFieldInnerPanel = OSG::Panel::create();
    MultiPtrFieldInnerPanel->setLayout(MultiPtrFieldInnerPanelLayout);
    MultiPtrFieldInnerPanel->setPreferredSize(Vec2f(200.0f, 200.0f));
    MultiPtrFieldInnerPanel->pushToChildren(AButton);
    MultiPtrFieldInnerPanel->pushToChildren(BButton);

    //Popup Menu
    MenuItemRefPtr RemoveIndexMenuItem = MenuItem::create();
    RemoveIndexMenuItem->setText("Remove Index");
    RemoveIndexMenuItem->addActionListener(new RemoveMultiPtrFieldActionListener());

    MenuItemRefPtr SetValueMenuItem = MenuItem::create();
    SetValueMenuItem->setText("Set Value");
    SetValueMenuItem->addActionListener(new SetMultiPtrFieldActionListener());
    
    MenuItemRefPtr AddValueMenuItem = MenuItem::create();
    AddValueMenuItem->setText("Add Value");
    AddValueMenuItem->addActionListener(new AddMultiPtrFieldActionListener());
    
    MenuItemRefPtr InsertIndexMenuItem = MenuItem::create();
    InsertIndexMenuItem->setText("Insert Value");
    InsertIndexMenuItem->addActionListener(new InsertMultiPtrFieldActionListener());
    
    MenuItemRefPtr MoveIndexMenuItem = MenuItem::create();
    MoveIndexMenuItem->setText("Move Value");
    MoveIndexMenuItem->addActionListener(new MoveMultiPtrFieldActionListener());
    
    MenuItemRefPtr SwapIndexMenuItem = MenuItem::create();
    SwapIndexMenuItem->setText("Swap Value");
    SwapIndexMenuItem->addActionListener(new SwapMultiPtrFieldActionListener());

    PopupMenuRefPtr MultiPtrFieldListPopupMenu = PopupMenu::create();
    MultiPtrFieldListPopupMenu->addItem(SetValueMenuItem);
    MultiPtrFieldListPopupMenu->addItem(AddValueMenuItem);
    MultiPtrFieldListPopupMenu->addItem(InsertIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(MoveIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(SwapIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(RemoveIndexMenuItem);

    //Multi-field List Model
	MultiPtrFieldListModel = MFieldListModel::create();
    MultiPtrFieldListModel->setContainer(MultiPtrFieldInnerPanel);
    MultiPtrFieldListModel->setFieldId(Panel::ChildrenFieldId);

    //List
    MultiPtrFieldList = List::create();
    MultiPtrFieldList->setPreferredSize(Vec2f(200, 300));
    MultiPtrFieldList->setOrientation(List::VERTICAL_ORIENTATION);
	MultiPtrFieldList->setModel(MultiPtrFieldListModel);
    ListSelectionModelPtr MultiPtrFieldListSelectionModel(new DefaultListSelectionModel());
    MultiPtrFieldList->setSelectionModel(MultiPtrFieldListSelectionModel);
    MultiPtrFieldList->setPopupMenu(MultiPtrFieldListPopupMenu);

    // Create a ScrollPanel for easier viewing of the List
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(MultiPtrFieldList);


    LayoutRefPtr ThePanelLayout = OSG::FlowLayout::create();

    PanelRefPtr ThePanel = Panel::createEmpty();
    ThePanel->setLayout(ThePanelLayout);
    ThePanel->pushToChildren(MultiPtrFieldInnerPanel);
    ThePanel->pushToChildren(ExampleScrollPanel);

    return ThePanel;
    
}