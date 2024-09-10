	bool ControllerEdgeHide::addTime(Widget* _widget, float _time)
	{
		const IntSize& view_size = _widget->getParentSize();
		// do nothing if we have minimized window
		if (view_size.width <= 1 && view_size.height <= 1)
			return true;

		Widget* keyFocus = InputManager::getInstance().getKeyFocusWidget();
		Widget* mouseFocus = InputManager::getInstance().getMouseFocusWidget();

		while ((keyFocus != nullptr) && (_widget != keyFocus))
			keyFocus = keyFocus->getParent();
		while ((mouseFocus != nullptr) && (_widget != mouseFocus))
			mouseFocus = mouseFocus->getParent();

		// if our widget or its children have focus
		bool haveFocus = ((keyFocus != nullptr) || (mouseFocus != nullptr)) || (_widget->getVisible() == false);

		mElapsedTime += haveFocus ? -_time : _time;

		if (mElapsedTime >= mTime)
		{
			mElapsedTime = mTime;
		}
		if (mElapsedTime <= 0)
		{
			mElapsedTime = 0.0f;
			return true;
		}

		float k = sin(M_PI * mElapsedTime / mTime - M_PI / 2);
		if (k < 0) k = (-pow(-k, 0.7f) + 1) / 2;
		else k = (pow(k, 0.7f) + 1) / 2;

		MyGUI::IntCoord coord = _widget->getCoord();
		// if widget was moved
		if (coord != mLastCoord)
		{
			// if still moving - leave it alone
			if (haveFocus)
				return true;
			else
				recalculateTime(_widget);
		}

		bool nearBorder = false;

		if ((coord.left <= 0) && !(coord.right() >= view_size.width - 1))
		{
			coord.left = - int( float(coord.width - mRemainPixels - mShadowSize) * k);
			nearBorder = true;
		}
		if ((coord.top <= 0) && !(coord.bottom() >= view_size.height - 1))
		{
			coord.top = - int( float(coord.height - mRemainPixels - mShadowSize) * k);
			nearBorder = true;
		}
		if ((coord.right() >= view_size.width - 1) && !(coord.left <= 0))
		{
			coord.left = int(float(view_size.width - 1) - float(mRemainPixels) * k - float(coord.width) * (1.f - k));
			nearBorder = true;
		}
		if ((coord.bottom() >= view_size.height - 1) && !(coord.top <= 0))
		{
			coord.top = int(float(view_size.height - 1) - float(mRemainPixels) * k - float(coord.height) * (1.f - k));
			nearBorder = true;
		}

		if (nearBorder)
		{
			_widget->setCoord(coord);
		}
		else
		{
			mElapsedTime = 0;
		}
		mLastCoord = coord;

		eventUpdateAction(_widget, this);

		return true;
	}