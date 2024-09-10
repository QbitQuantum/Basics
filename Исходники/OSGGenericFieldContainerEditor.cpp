ComponentTransitPtr GenericFieldContainerEditor::createFCToolTip(const FieldContainerType &FCType)
{
    std::string FieldDoc(doxygenToPlainFormatting(FCType.getDocumentation()));

    //TypeName
    LabelRecPtr TypeLabel = Label::create();
    TypeLabel->setText(FCType.getName());
    TypeLabel->setAlignment(Vec2f(0.5f,0.5f));
    TypeLabel->setBackgrounds(NULL);

    //Separator
    SeparatorRecPtr MainSeparator = Separator::create();
    MainSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    MainSeparator->setSeparatorSize(1.0f);
    MainSeparator->setPreferredSize(Vec2f(1.0f,5.0f));
    MainSeparator->setBackgrounds(NULL);

    //Inheritance Panel Layout
    //LabelRecPtr InheritanceLabel = Label::create();
    //InheritanceLabel->setText("Inheritance");

    //FlowLayoutRecPtr InheritancePanelLayout = FlowLayout::create();
    //InheritancePanelLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
    //InheritancePanelLayout->setVerticalGap(3.0f);
    //InheritancePanelLayout->setMajorAxisAlignment(0.0f);
    //InheritancePanelLayout->setMinorAxisAlignment(0.5f);
    //InheritancePanelLayout->setComponentAlignment(0.5f);

    ////Inheritance Panel
    //PanelRecPtr InheritancePanel = Panel::createEmpty();
    //InheritancePanel->setAllInsets(5.0f);
    //InheritancePanel->setLayout(InheritancePanelLayout);

    //const TypeBase *ParentType(&FCType);
    ////while()
    ////{
        ////ToolTipPanel->pushToChildren(DescriptionTextArea);
    ////}
    //LabelRecPtr TypeNameLabel = Label::create();
    //TypeNameLabel->setText(FCType.getName());
    //TypeNameLabel->setAlignment(Vec2f(0.5f,0.5f));

    //InheritancePanel->pushToChildren(TypeNameLabel);

    //Set the layout constraints
    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Description Panel
    LabelRecPtr DescriptionLabel = Label::create();
    DescriptionLabel->setText("Description:");
    DescriptionLabel->setBackgrounds(NULL);

    TextAreaRecPtr DescriptionTextArea = TextArea::create();
    DescriptionTextArea->setText(FieldDoc);
    DescriptionTextArea->setEditable(false);
    DescriptionTextArea->setBorders(NULL);
    DescriptionTextArea->setBackgrounds(NULL);
    DescriptionTextArea->setConstraints(CenterConstraints);

    //Description Panel
    PanelRecPtr DescriptionPanel = Panel::create();
    BorderLayoutRecPtr DescriptionPanelLayout = BorderLayout::create();
    DescriptionPanel->setAllInsets(5.0f);
    DescriptionPanel->setLayout(DescriptionPanelLayout);
    DescriptionPanel->pushToChildren(DescriptionTextArea);
    DescriptionPanel->setBackgrounds(NULL);


    //ToolTip Layout
    PanelRecPtr ToolTipPanel = Panel::createEmpty();

    SpringLayoutRecPtr MainLayout = SpringLayout::create();

    //TypeLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TypeLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //MainSeparator    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MainSeparator, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, TypeLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MainSeparator, -15,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MainSeparator, 15,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    ////InheritancePanel
    //MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InheritanceLabel, 1,
                              //SpringLayoutConstraints::SOUTH_EDGE, MainSeparator);
    //MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InheritanceLabel, 0,
                              //SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    //MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InheritanceLabel, 0,
                              //SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    ////InheritancePanel
    //MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InheritancePanel, 1,
                              //SpringLayoutConstraints::SOUTH_EDGE, InheritanceLabel);
    //MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InheritancePanel, 0,
                              //SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    //MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InheritancePanel, 0,
                              //SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);


    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionLabel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, MainSeparator);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionPanel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, DescriptionLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::SOUTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionPanel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //ToolTip Panel

    Component* DefaultToolTip(LookAndFeelManager::the()->getLookAndFeel()->getDefaultToolTip());
    ToolTipPanel->setBorders(DefaultToolTip->getBorder());
    ToolTipPanel->setBackgrounds(DefaultToolTip->getBackground());
    ToolTipPanel->setForegrounds(DefaultToolTip->getForeground());
    ToolTipPanel->setLayout(MainLayout);
    ToolTipPanel->pushToChildren(TypeLabel);
    ToolTipPanel->pushToChildren(MainSeparator);
    //ToolTipPanel->pushToChildren(InheritanceLabel);
    //ToolTipPanel->pushToChildren(InheritancePanel);
    ToolTipPanel->pushToChildren(DescriptionLabel);
    ToolTipPanel->pushToChildren(DescriptionPanel);

    Real32 Height(100.0f + DescriptionTextArea->getLineHeight()
                  * (DescriptionTextArea->getText().size()/40));
    ToolTipPanel->setPreferredSize(Vec2f(300.0f,Height));

    return ComponentTransitPtr(ToolTipPanel);
}