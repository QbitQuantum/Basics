void LLNavigationBar::showNavigationPanel(BOOL visible)
{
	bool fpVisible = gSavedSettings.getBOOL("ShowNavbarFavoritesPanel");

	LLFavoritesBarCtrl* fb = getChild<LLFavoritesBarCtrl>("favorite");
	LLPanel* navPanel = getChild<LLPanel>("navigation_panel");

	LLRect nbRect(getRect());
	LLRect fbRect(fb->getRect());

	navPanel->setVisible(visible);

	if (visible)
	{
		if (fpVisible)
		{
			// Navigation Panel must be shown. Favorites Panel is visible.

			nbRect.setLeftTopAndSize(nbRect.mLeft, nbRect.mTop, nbRect.getWidth(), mDefaultNbRect.getHeight());
			fbRect.setLeftTopAndSize(fbRect.mLeft, mDefaultFpRect.mTop, fbRect.getWidth(), fbRect.getHeight());

			// this is duplicated in 'else' section because it should be called BEFORE fb->reshape
			reshape(nbRect.getWidth(), nbRect.getHeight());
			setRect(nbRect);
			// propagate size to parent container
			getParent()->reshape(nbRect.getWidth(), nbRect.getHeight());

			fb->reshape(fbRect.getWidth(), fbRect.getHeight());
			fb->setRect(fbRect);
		}
		else
		{
			// Navigation Panel must be shown. Favorites Panel is hidden.

			S32 height = mDefaultNbRect.getHeight() - mDefaultFpRect.getHeight();
			nbRect.setLeftTopAndSize(nbRect.mLeft, nbRect.mTop, nbRect.getWidth(), height);

			reshape(nbRect.getWidth(), nbRect.getHeight());
			setRect(nbRect);
			getParent()->reshape(nbRect.getWidth(), nbRect.getHeight());
		}
	}
	else
	{
		if (fpVisible)
		{
			// Navigation Panel must be hidden. Favorites Panel is visible.

			nbRect.setLeftTopAndSize(nbRect.mLeft, nbRect.mTop, nbRect.getWidth(), fbRect.getHeight());
			fbRect.setLeftTopAndSize(fbRect.mLeft, fbRect.getHeight(), fbRect.getWidth(), fbRect.getHeight());

			// this is duplicated in 'else' section because it should be called BEFORE fb->reshape
			reshape(nbRect.getWidth(), nbRect.getHeight());
			setRect(nbRect);
			getParent()->reshape(nbRect.getWidth(), nbRect.getHeight());

			fb->reshape(fbRect.getWidth(), fbRect.getHeight());
			fb->setRect(fbRect);
		}
		else
		{
			// Navigation Panel must be hidden. Favorites Panel is hidden.

			nbRect.setLeftTopAndSize(nbRect.mLeft, nbRect.mTop, nbRect.getWidth(), 0);

			reshape(nbRect.getWidth(), nbRect.getHeight());
			setRect(nbRect);
			getParent()->reshape(nbRect.getWidth(), nbRect.getHeight());
		}
	}

	childSetVisible("bg_icon", fpVisible);
	childSetVisible("bg_icon_no_fav", !fpVisible);
}