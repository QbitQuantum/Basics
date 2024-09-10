WEBC_BOOL DisplayManager::RectVisible (WebRect *pRect)
{
	if (mViewRect.Overlaps(pRect))
	{
		DisplayManager *parentManager = GetManager();

		if (parentManager)
		{
			PresetWebRect rect(pRect);
			rect.And(&mViewRect);

			WebRect padding;
			GetPaddingWidth(&padding);

			DISPLAY_INT x = mRect.left, y = mRect.top;
			if (mpParent)
			{
				mpParent->GetDisplayPosition(this, &x, &y);
			}

			rect.Shift(x + padding.left - mViewRect.left, y + padding.top - mViewRect.top);

			return (parentManager->RectVisible(&rect));
		}
		else
		{
			return (WEBC_TRUE);
		}
	}

	return (WEBC_FALSE);
}