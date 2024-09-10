QMenu *TikzCommandInserter::getMenu(const TikzCommandList &commandList)
{
	QMenu *menu = new QMenu(commandList.title, m_parentWidget);
	const int numOfCommands = commandList.commands.size();
	QAction *action = new QAction("test", menu);
	int whichSection = 0;

	// get left margin of the menu (to be added to the minimum width of the menu)
	menu->addAction(action);
	QFont actionFont = action->font();
	actionFont.setPointSize(actionFont.pointSize() - 1);
	QFontMetrics actionFontMetrics(actionFont);
	int menuLeftMargin = menu->width() - actionFontMetrics.boundingRect(action->text()).width();
	menu->removeAction(action);
	int menuMinimumWidth = 0;

	for (int i = 0; i < numOfCommands; ++i)
	{
		const QString name = commandList.commands.at(i).name;
		if (name.isEmpty()) // add separator or submenu
		{
			if (commandList.commands.at(i).type == 0)
			{
				action = new QAction(menu);
				action->setSeparator(true);
				menu->addAction(action);
			}
			else // type == -1, so add submenu; this assumes that the i-th command with type == -1 corresponds with the i-th submenu (see getCommands())
			{
				menu->addMenu(getMenu(commandList.children.at(whichSection)));
				++whichSection;
			}
		}
		else // add command
		{
			action = new QAction(name, menu);
			action->setData(commandList.commands.at(i).number); // link to the corresponding item in m_tikzCommandsList
			action->setStatusTip(commandList.commands.at(i).description);
			menuMinimumWidth = qMax(menuMinimumWidth, actionFontMetrics.boundingRect(commandList.commands.at(i).description).width());
			connect(action, SIGNAL(triggered()), this, SLOT(insertTag()));
			connect(action, SIGNAL(hovered()), this, SLOT(updateDescriptionMenuItem()));
			menu->addAction(action);
		}
	}

	// if the menu does not only contain submenus, then we add a menu item
	// at the bottom of the menu which shows the description of the currently
	// highlighted menu item
	if (whichSection < menu->actions().size())
	{
		action = new QAction(this);
		action->setSeparator(true);
		menu->addAction(action);

		action = new QAction(this);
		QFont actionFont = action->font();
		actionFont.setPointSize(actionFont.pointSize() - 1);
		action->setFont(actionFont);
		connect(action, SIGNAL(triggered()), this, SLOT(insertTag()));
		menu->addAction(action);

		// make sure that the menu width does not change when the content
		// of the above menu item changes
		menu->setMinimumWidth(menuMinimumWidth + menuLeftMargin);
	}

	return menu;
}