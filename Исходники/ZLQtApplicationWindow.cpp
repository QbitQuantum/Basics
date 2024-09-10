void ZLQtApplicationWindow::addToolbarItem(ZLToolbar::ItemPtr item) {
	QToolBar *tb = toolbar(type(*item));
	QAction *action = 0;

	switch (item->type()) {
		case ZLToolbar::Item::PLAIN_BUTTON:
		case ZLToolbar::Item::TOGGLE_BUTTON:
			action = new ZLQtToolBarAction(this, (ZLToolbar::AbstractButtonItem&)*item);
			tb->addAction(action);
			break;
		case ZLToolbar::Item::MENU_BUTTON:
		{
			ZLToolbar::MenuButtonItem &buttonItem = (ZLToolbar::MenuButtonItem&)*item;
			QToolButton *button = new QToolButton(tb);
			button->setFocusPolicy(Qt::NoFocus);
			button->setDefaultAction(new ZLQtToolBarAction(this, buttonItem));
			button->setMenu(new QMenu(button));
			button->setPopupMode(QToolButton::MenuButtonPopup);
			action = tb->addWidget(button);
			myMenuButtons[&buttonItem] = button;
			shared_ptr<ZLPopupData> popupData = buttonItem.popupData();
			myPopupIdMap[&buttonItem] =
				popupData.isNull() ? (size_t)-1 : (popupData->id() - 1);
			break;
		}
		case ZLToolbar::Item::TEXT_FIELD:
		case ZLToolbar::Item::SEARCH_FIELD:
		{
			ZLToolbar::ParameterItem &textFieldItem =
				(ZLToolbar::ParameterItem&)*item;
			LineEditParameter *para = new LineEditParameter(tb, *this, textFieldItem);
			addVisualParameter(textFieldItem.parameterId(), para);
			action = para->action();
			break;
		}
		case ZLToolbar::Item::SEPARATOR:
			action = tb->addSeparator();
			break;
	}

	if (action != 0) {
		myActions[&*item] = action;
	}
}