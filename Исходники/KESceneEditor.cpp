PanelPtr SceneEditor::createEditorTab(SceneComponentEditorPtr Editor, IconManagerPtr TheIconManager) const
{
	//Editor Icon
	ImageComponentPtr EditorIcon = TheIconManager->createIconImageComponent(Editor->getPresentationIconName());
    if(EditorIcon == NullFC)
    {
        EditorIcon = ImageComponent::create();
    }

	beginEditCP(EditorIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		EditorIcon->setAlignment(Vec2f(0.5f,0.5f));
		EditorIcon->setScale(ImageComponent::SCALE_MIN_AXIS);
	endEditCP(EditorIcon, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	
	//Editor Label
	LabelPtr TabLabel = Label::create();
	beginEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::AlignmentFieldMask);
		TabLabel->setBorders(NullFC);
		TabLabel->setBackgrounds(NullFC);
		TabLabel->setText(Editor->getPresentationName());
		TabLabel->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(TabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::AlignmentFieldMask);

	//Tab
	PanelPtr Tab = Panel::createEmpty();

	//Layout
	SpringLayoutPtr TabLayout = SpringLayout::create();

	//Editor Icon
    TabLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, EditorIcon, 0, SpringLayoutConstraints::WEST_EDGE, Tab);
    TabLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, EditorIcon, 0, SpringLayoutConstraints::EAST_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, EditorIcon, 0, SpringLayoutConstraints::NORTH_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, EditorIcon, -1, SpringLayoutConstraints::NORTH_EDGE, TabLabel);
	
	//Editor Label
    TabLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TabLabel, 0, SpringLayoutConstraints::WEST_EDGE, Tab);
    TabLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TabLabel, 0, SpringLayoutConstraints::EAST_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TabLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, Tab);
	TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TabLabel, LayoutSpring::height(TabLabel));
    
    //Tab Layout
    //TabLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, Tab, LayoutSpring::max(TabLayout->getConstraint(SpringLayoutConstraints::WIDTH_EDGE,TabLabel),TabLayout->getConstraint(SpringLayoutConstraints::WIDTH_EDGE,EditorIcon)));
    //TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, Tab, LayoutSpring::sum(TabLayout->getConstraint(SpringLayoutConstraints::HEIGHT_EDGE,TabLabel),TabLayout->getConstraint(SpringLayoutConstraints::HEIGHT_EDGE,EditorIcon)));
    TabLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, Tab, LayoutSpring::width(Tab));
    TabLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, Tab, LayoutSpring::height(Tab));

	beginEditCP(Tab, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		Tab->getChildren().push_back(EditorIcon);
		Tab->getChildren().push_back(TabLabel);
		Tab->setLayout(TabLayout);
		Tab->setPreferredSize(Vec2f(70.0f,50.0f));
	endEditCP(Tab, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

	return Tab;
}