	void WidgetsWindow::requestCreateWidgetItem(MyGUI::ItemBox* _sender, MyGUI::Widget* _item)
	{
		MyGUI::Button* button = _item->createWidget<MyGUI::Button>(mButtonSkinName, MyGUI::IntCoord(
			mWidgetsButtonOffset,
			mWidgetsButtonOffset,
			_item->getWidth() - mWidgetsButtonOffset - mWidgetsButtonOffset,
			_item->getHeight() - mWidgetsButtonOffset - mWidgetsButtonOffset),
			MyGUI::Align::Stretch);

		button->setTextAlign(MyGUI::Align::Center);
		button->eventMouseButtonClick += MyGUI::newDelegate(this, &WidgetsWindow::notifySelectWidgetType);
		button->setNeedToolTip(true);
		button->eventToolTip += MyGUI::newDelegate(this, &WidgetsWindow::notifyToolTip);

		_item->setUserData(button);
	}