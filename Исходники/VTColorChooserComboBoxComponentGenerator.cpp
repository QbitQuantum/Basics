ComponentTransitPtr ColorChooserComboBoxComponentGenerator::getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

	PanelRefPtr TheComponent = Panel::create();//dynamic_pointer_cast<Component>(getDrawObjectPrototype()->shallowCopy());
	TheComponent->setLayout(LayoutRefPtr(FlowLayout::create()));

	LabelRefPtr theColorLabel = Label::create();
	//theColorLabel->setPreferredSize(Vec2f(50.0f,50.0f));
	theColorLabel->setBorders(NULL);

	try
	{
		Color4f theColor = boost::any_cast<Color4f>(Value);

		if(theColor != NULL)
		{
			ColorLayerRefPtr theColorLabelBackground = ColorLayer::create();
			theColorLabelBackground->setColor(theColor);
			theColorLabel->setBackgrounds(theColorLabelBackground);
		}
	}
	catch(boost::bad_any_cast &)
	{
		std::string ValueString;

		try
		{
			ValueString = lexical_cast(Value);
		}
		catch (boost::bad_lexical_cast &)
		{
			//Could not convert to string
			SWARNING << "ColorChooserComboBoxComponentGenerator::getComboBoxComponent - The elements should either be a Color4f value or a std::string\n";
		}

		theColorLabel->setText(ValueString);

		if(IsSelected && HasFocus)
		{
			if(getFocusedTextColorHasPriority())
			{
				theColorLabel->setTextColors(getFocusedTextColor());
			}
			else
			{
				theColorLabel->setTextColors(getSelectedTextColor());
			}
		}
		else if(IsSelected)
		{
				theColorLabel->setTextColors(getSelectedTextColor());
		}
		else if(HasFocus)
		{
				theColorLabel->setTextColors(getFocusedTextColor());
		}
	}

	TheComponent->pushToChildren(theColorLabel);
    
	if(IsSelected && HasFocus)
	{
			if(getFocusedBorderHasPriority())
			{
				TheComponent->setBorders(getFocusedBorder());
			}
			else
			{
				TheComponent->setBorders(getSelectedBorder());
			}
			if(getFocusedBackgroundHasPriority())
			{
				TheComponent->setBackgrounds(getFocusedBackground());
			    TheComponent->setForegrounds(getFocusedForeground());
			}
			else
			{
				TheComponent->setBackgrounds(getSelectedBackground());
			    TheComponent->setForegrounds(getSelectedForeground());
			}
	}
	else if(IsSelected)
	{
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
			TheComponent->setForegrounds(getSelectedForeground());
	}
	else if(HasFocus)
	{
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
			TheComponent->setForegrounds(getFocusedForeground());
	}
	return ComponentTransitPtr(TheComponent.get());
}