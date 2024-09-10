ComponentTransitPtr PanelListComponentGenerator::getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

	std::string ValueString;

    try
    {
        ValueString = lexical_cast(Value);
		PanelRefPtr theComponent = Panel::create();
	
		GridLayoutRefPtr PanelLayout = OSG::GridLayout::create();
		PanelLayout->setRows(3);
		PanelLayout->setColumns(1);
		PanelLayout->setHorizontalGap(0);
		PanelLayout->setVerticalGap(2);

		

		std::stringstream is;
		is<<Index;
		std::string iss;
		is>>iss;
		TextFieldRefPtr theName = TextField::create();
		theName->setText("Group"+iss);
		theName->setPreferredSize(Vec2f(146,20));
		

		PanelRefPtr rangePanel = Panel::create();
		
		GridLayoutRefPtr rangePanelLayout = OSG::GridLayout::create();
		rangePanelLayout->setRows(1);
		rangePanelLayout->setColumns(4);
		rangePanelLayout->setHorizontalGap(2);
		rangePanelLayout->setVerticalGap(0);

		
		LabelRefPtr rangeLabel = Label::create();
		rangeLabel->setText("Range:");
		rangeLabel->setPreferredSize(Vec2f(35,20));

		TextFieldRefPtr from = TextField::create();
		from->setEmptyDescText("From");
		from->setPreferredSize(Vec2f(35,20));

		LabelRefPtr hiphenLabel = Label::create();
		hiphenLabel->setText(" - ");
		hiphenLabel->setPreferredSize(Vec2f(35,20));

		TextFieldRefPtr to = TextField::create();
		to->setPreferredSize(Vec2f(35,20));
		to->setEmptyDescText("To");

		rangePanel->pushToChildren(rangeLabel);
		rangePanel->pushToChildren(from);
		rangePanel->pushToChildren(hiphenLabel);
		rangePanel->pushToChildren(to);
		rangePanel->setLayout(rangePanelLayout);
		rangePanel->setPreferredSize(Vec2f(146,20));

		DefaultMutableComboBoxModelRefPtr TheComboBoxModel = DefaultMutableComboBoxModel::create();
		TheComboBoxModel->addElement(boost::any(Color4f(1.0,0.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,1.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,1.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(1.0,1.0,1.0,1.0)));
		TheComboBoxModel->addElement(boost::any(std::string("More Colors")));

		ColorChooserComboBoxComponentGeneratorRefPtr TheColorChooserComboBoxComponentGenerator = ColorChooserComboBoxComponentGenerator::create();
		
		//Create the ComboBox
		ComboBoxRefPtr TheComboBox = ComboBox::create();
		TheComboBox->setModel(TheComboBoxModel);
		TheComboBox->setCellGenerator(TheColorChooserComboBoxComponentGenerator);
		TheComboBox->setEditable(false);
		TheComboBox->setSelectedIndex(0);
		TheComboBox->setPreferredSize(Vec2f(146,20));

		theComponent->pushToChildren(theName);
		theComponent->pushToChildren(rangePanel);
		theComponent->pushToChildren(TheComboBox);
		theComponent->setLayout(PanelLayout);
		theComponent->setPreferredSize(Vec2f(146,66));

		Parent->setCellMajorAxisLength(66);

		return ComponentTransitPtr(theComponent.get());

    }
    catch (boost::bad_lexical_cast &)
    {
        return ComponentTransitPtr(NULL);
    }

}