bool GoBackActionWidget::event(QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick || event->type() == QEvent::Wheel)
	{
		QList<GesturesManager::GesturesContext> contexts;
		contexts << GesturesManager::ToolBarGesturesContext << GesturesManager::GenericGesturesContext;

		if (GesturesManager::startGesture(this, event, contexts))
		{
			return true;
		}
	}

	if (event->type() == QEvent::ContextMenu)
	{
		QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent*>(event);

		if (contextMenuEvent)
		{
			if (contextMenuEvent->reason() == QContextMenuEvent::Mouse)
			{
				contextMenuEvent->accept();

				return true;
			}

			event->accept();

			Window *window = getWindow();
			QMenu menu(this);
			menu.addAction(window ? window->getContentsWidget()->getAction(ActionsManager::ClearTabHistoryAction) : ActionsManager::getAction(ActionsManager::ClearTabHistoryAction, this));
			menu.addAction(window ? window->getContentsWidget()->getAction(ActionsManager::PurgeTabHistoryAction) : ActionsManager::getAction(ActionsManager::PurgeTabHistoryAction, this));

			ToolBarWidget *toolBar = qobject_cast<ToolBarWidget*>(parentWidget());

			if (toolBar)
			{
				menu.addSeparator();
				menu.addActions(ToolBarWidget::createCustomizationMenu(toolBar->getIdentifier(), QList<QAction*>(), &menu)->actions());
			}

			menu.exec(contextMenuEvent->globalPos());

			return true;
		}

		return false;
	}

	if (event->type() == QEvent::ToolTip)
	{
		QHelpEvent *helpEvent = dynamic_cast<QHelpEvent*>(event);

		if (helpEvent)
		{
			const QVector<QKeySequence> shortcuts = ActionsManager::getActionDefinition(ActionsManager::GoBackAction).shortcuts;
			QString toolTip = text() + (shortcuts.isEmpty() ? QString() : QLatin1String(" (") + shortcuts.at(0).toString(QKeySequence::NativeText) + QLatin1Char(')'));

			if (getWindow())
			{
				const WindowHistoryInformation history = getWindow()->getContentsWidget()->getHistory();

				if (!history.entries.isEmpty() && history.index > 0)
				{
					QString title = history.entries.at(history.index - 1).title;
					title = (title.isEmpty() ? tr("(Untitled)") : title.replace(QLatin1Char('&'), QLatin1String("&&")));

					toolTip = title + QLatin1String(" (") + text() + (shortcuts.isEmpty() ? QString() : QLatin1String(" - ") + shortcuts.at(0).toString(QKeySequence::NativeText)) + QLatin1Char(')');
				}
			}

			QToolTip::showText(helpEvent->globalPos(), toolTip);
		}

		return true;
	}

	return ActionWidget::event(event);
}