	void ToolControl::requestCreateObjectItem(MyGUI::ItemBox* _sender, MyGUI::Widget* _item)
	{
		MyGUI::Button* button = _item->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(0, 0, _item->getWidth(), _item->getHeight()), MyGUI::Align::Stretch);

		button->setTextAlign(MyGUI::Align::Center);
		button->eventMouseButtonClick += MyGUI::newDelegate(this, &ToolControl::notifySelectObjectType);
		//button->setNeedToolTip(true);
		//button->eventToolTip += MyGUI::newDelegate(this, &ToolControl::notifyToolTip);

		_item->setUserData(button);
	}