bool TabNavigation::OnEventKeyDown(const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& args = static_cast<const CEGUI::KeyEventArgs&>(e);
	if (args.scancode == CEGUI::Key::Tab) // Tab or Shift+Tab
	{
		WidgetList::iterator itCurrent = Containers::find(mTabOrder.begin(), mTabOrder.end(), args.window);
		OC_ASSERT(itCurrent != mTabOrder.end());
		WidgetList::iterator itFocus = itCurrent;
		CEGUI::Window* newWidget = 0;
		do
		{
			if (args.sysKeys & CEGUI::Shift)
			{
				// Set previous
				if (itFocus == mTabOrder.begin())
					itFocus = mTabOrder.end();
				--itFocus;
			}
			else
			{
				// Set next
				++itFocus;
				if (itFocus == mTabOrder.end())
					itFocus = mTabOrder.begin();
			}
			newWidget = *itFocus;
		}
		while ((!newWidget->isVisible() || newWidget->isDisabled() || newWidget->getProperty("ReadOnly") == "True" ) && itFocus != itCurrent);
		newWidget->activate();

		// Make sure active widget will be visible
		if (mScrollablePane)
		{
			CEGUI::Window* w = newWidget;
			CEGUI::Vector2 widgetOffset(0, 0);
			do
			{
				widgetOffset += w->getPosition().asAbsolute(w->getParentPixelSize());
				w = w->getParent();
			}
			while (w != mScrollablePane && w != 0);

			float32 scrollViewTop = mScrollablePane->getContentPaneArea().getSize().d_height * mScrollablePane->getVerticalScrollPosition();
			float32 scrollViewBottom = scrollViewTop + mScrollablePane->getClipRect().getHeight();
			
			if (widgetOffset.d_y < scrollViewTop || widgetOffset.d_y + newWidget->getPixelSize().d_height > scrollViewBottom)
			{
				// We need to scroll
				mScrollablePane->setVerticalScrollPosition(widgetOffset.d_y / mScrollablePane->getContentPaneArea().getSize().d_height);
			}
		}

		return true;
	}
	return false;
}