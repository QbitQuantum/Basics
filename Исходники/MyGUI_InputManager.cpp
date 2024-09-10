	bool InputManager::injectMousePress(int _absx, int _absy, MouseButton _id)
	{
		injectMouseMove(_absx, _absy, mOldAbsZ);

		// если мы щелкнули не на гуй
		if (!isFocusMouse())
		{
			resetKeyFocusWidget();

			return false;
		}

		// если активный элемент заблокирован
		//FIXME
		if (!mWidgetMouseFocus->getInheritedEnabled())
			return true;

		if (MouseButton::None != _id && MouseButton::MAX != _id)
		{
			// start capture
			mMouseCapture[_id.getValue()] = true;
			// remember last pressed position
			if (mLayerMouseFocus != nullptr)
			{
				IntPoint point = mLayerMouseFocus->getPosition(_absx, _absy);
				mLastPressed[_id.getValue()] = point;
			}
		}

		// ищем вверх тот виджет который может принимать фокус
		Widget* item = mWidgetMouseFocus;
		while ((item != nullptr) && (!item->getNeedKeyFocus()))
			item = item->getParent();

		// устанавливаем перед вызовом т.к. возможно внутри ктонить поменяет фокус под себя
		setKeyFocusWidget(item);

		if (isFocusMouse())
		{
			IntPoint point (_absx, _absy);
			if (mLayerMouseFocus != nullptr)
				point = mLayerMouseFocus->getPosition(_absx, _absy);
			mWidgetMouseFocus->_riseMouseButtonPressed(point.left, point.top, _id);

			// после пресса может сброситься
			if (mWidgetMouseFocus)
			{
				// поднимаем виджет, надо подумать что делать если поменялся фокус клавы
				LayerManager::getInstance().upLayerItem(mWidgetMouseFocus);

				// поднимаем пикинг Overlapped окон
				Widget* pick = mWidgetMouseFocus;
				do
				{
					// если оверлаппед, то поднимаем пикинг
					if (pick->getWidgetStyle() == WidgetStyle::Overlapped)
					{
						if (pick->getParent()) pick->getParent()->_forcePick(pick);
					}

					pick = pick->getParent();
				}
				while (pick);
			}
		}

		return true;
	}