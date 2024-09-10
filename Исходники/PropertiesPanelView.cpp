void PropertiesPanelView::createPropertiesWidgetsPair(MyGUI::WidgetPtr _window, std::string _property, std::string _value, std::string _type,int y)
{
	pairs_counter++;
	int x1 = 0, x2 = 125;
	int w1 = 120;
	int w2 = _window->getWidth() - x2;
	const int h = PropertyItemHeight;

	if (_property == "Position")
	{
		x1 = 66;
		w1 = w1 - x1;
	}

	MyGUI::StaticTextPtr text;
	MyGUI::WidgetPtr editOrCombo;
	//int string_int_float; // 0 - string, 1 - int, 2 - float

	int widget_for_type;// 0 - Edit, 1 - Combo mode drop, 2 - ...
	std::string type_names[2] = {"Edit", "ComboBox"};
	if ("Name" == _type) widget_for_type = 0;
	else if ("Skin" == _type) widget_for_type = 1;
	else if ("Position" == _type) widget_for_type = 0;
	else if ("Layer" == _type) widget_for_type = 1;
	else if ("String" == _type) widget_for_type = 0;
	else if ("Align" == _type) widget_for_type = 1;
	// не совсем правильно FIXME
	else if ("1 int" == _type) widget_for_type = 0;
	else if ("2 int" == _type) widget_for_type = 0;
	else if ("4 int" == _type) widget_for_type = 0;
	else if ("1 float" == _type) widget_for_type = 0;
	else if ("2 float" == _type) widget_for_type = 0;
	// надо сделать проще FIXME
	else if ("Colour" == _type) widget_for_type = 0;//"Colour" хорошо бы колорпикером
	else if ("MessageButton" == _type) widget_for_type = 1;
	else if ("FileName" == _type) widget_for_type = 0;
	else widget_for_type = 1;

	if ((propertiesText.size() < pairs_counter) || (propertiesText[pairs_counter-1]->getParent() != _window))
	{
		text = _window->createWidget<MyGUI::StaticText>("Editor_StaticText", x1, y, w1, h, MyGUI::Align::Default);
		text->setTextAlign(MyGUI::Align::Right);
		if (propertiesText.size() < pairs_counter)
		{
			propertiesText.push_back(text);
		}
		else
		{
			MyGUI::Gui::getInstance().destroyWidget(propertiesText[pairs_counter-1]);
			propertiesText[pairs_counter-1] = text;
		}
	}
	else
	{
		text = propertiesText[pairs_counter-1];
		text->setVisible(true);
		text->setCoord(x1, y, w1, h);
	}
	std::string prop = _property;
	// trim widget name
	std::string::iterator iter = std::find(prop.begin(), prop.end(), '_');
	if (iter != prop.end()) prop.erase(prop.begin(), ++iter);
	text->setCaption(prop);

	if ((propertiesElement.size() < pairs_counter) || (propertiesElement[pairs_counter-1]->getParent() != _window) ||
		(type_names[widget_for_type] != propertiesElement[pairs_counter-1]->getTypeName()))
	{
		if (widget_for_type == 0)
		{
			editOrCombo = _window->createWidget<MyGUI::Edit>("Edit", x2, y, w2, h, MyGUI::Align::Top | MyGUI::Align::HStretch);
			editOrCombo->castType<MyGUI::Edit>()->eventEditTextChange = newDelegate (this, &PropertiesPanelView::notifyTryApplyProperties);
			editOrCombo->castType<MyGUI::Edit>()->eventEditSelectAccept = newDelegate (this, &PropertiesPanelView::notifyForceApplyProperties);
		}
		else if (widget_for_type == 1)
		{
			editOrCombo = _window->createWidget<MyGUI::ComboBox>("ComboBox", x2, y, w2, h, MyGUI::Align::Top | MyGUI::Align::HStretch);
			editOrCombo->castType<MyGUI::ComboBox>()->eventComboAccept = newDelegate (this, &PropertiesPanelView::notifyForceApplyProperties2);

			editOrCombo->castType<MyGUI::ComboBox>()->setComboModeDrop(true);
		}

		if (propertiesElement.size() < pairs_counter)
		{
			propertiesElement.push_back(editOrCombo);
		}
		else
		{
			MyGUI::Gui::getInstance().destroyWidget(propertiesElement[pairs_counter-1]);
			propertiesElement[pairs_counter-1] = editOrCombo;
		}
	}
	else
	{
		editOrCombo = propertiesElement[pairs_counter-1];
		if (widget_for_type == 1) editOrCombo->castType<MyGUI::ComboBox>()->removeAllItems();
		editOrCombo->setVisible(true);
		editOrCombo->setCoord(x2, y, w2, h);
	}

	// fill possible values
	if (widget_for_type == 1)
	{
		std::vector<std::string> values;
		if (_type == "Skin") values = WidgetTypes::getInstance().find(current_widget->getTypeName())->skin;
		else values = WidgetTypes::getInstance().findPossibleValues(_type);

		for (std::vector<std::string>::iterator iter = values.begin(); iter != values.end(); ++iter)
			editOrCombo->castType<MyGUI::ComboBox>()->addItem(*iter);
	}

	editOrCombo->setUserString("action", _property);
	editOrCombo->setUserString("type", _type);

	if (_value.empty()){
		editOrCombo->setCaption(DEFAULT_VALUE);
	}
	else
	{
		editOrCombo->castType<MyGUI::Edit>()->setOnlyText(_value);
		checkType(editOrCombo->castType<MyGUI::Edit>(), _type);
	}
}