	void WidgetSelectorManager::selectWidget(const MyGUI::IntPoint& _mousePosition)
	{
		if (mLastClickPoint != _mousePosition)
		{
			mSelectDepth = 0;
			mLastClickPoint = _mousePosition;
		}

		// здесь кликать вглубь
		MyGUI::Widget* item = getTopWidget(_mousePosition);
		if (nullptr != item)
		{
			// find widget registered as container
			while ((nullptr == EditorWidgets::getInstance().find(item)) && (nullptr != item))
				item = item->getParent();
			MyGUI::Widget* oldItem = item;

			// try to selectin depth
			size_t depth = mSelectDepth;
			while (depth && (nullptr != item))
			{
				item = item->getParent();
				while ((nullptr == EditorWidgets::getInstance().find(item)) && (nullptr != item))
					item = item->getParent();
				MYGUI_ASSERT(depth != 0, "depth != 0");
				depth--;
			}

			if (nullptr == item)
			{
				item = oldItem;
				mSelectDepth = 0;
			}

			// found widget
			if (nullptr != item)
			{
				depth =  mSelectDepth;
				WidgetSelectorManager::getInstance().setSelectedWidget(item);
				mSelectDepth = depth + 1;
			}
			else
			{
				WidgetSelectorManager::getInstance().setSelectedWidget(nullptr);
			}
		}
		else
		{
			WidgetSelectorManager::getInstance().setSelectedWidget(nullptr);
		}
	}