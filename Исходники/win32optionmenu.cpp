//-----------------------------------------------------------------------------
HMENU Win32OptionMenu::createMenu (COptionMenu* _menu, int32_t& offsetIdx)
{
	HMENU menu = CreatePopupMenu ();

	bool multipleCheck = _menu->getStyle () & (kMultipleCheckStyle & ~kCheckStyle);

#if 0
	if (!multipleCheck && !(_menu->getStyle () & kCheckStyle))
	{
		MENUINFO mi = {0};
		mi.cbSize = sizeof (MENUINFO);
		mi.fMask = MIM_STYLE;
		mi.dwStyle = MNS_NOCHECK;
		SetMenuInfo (menu, &mi);
	}
#endif

	MENUINFO mi = {0};
	mi.cbSize = sizeof (MENUINFO);
	mi.dwStyle = MNS_CHECKORBMP;
	SetMenuInfo (menu, &mi);

	int flags = 0;
	int32_t offset = offsetIdx;
	int32_t nbEntries = _menu->getNbEntries ();
	offsetIdx += nbEntries;
	int32_t inc = 0;
	CMenuItemIterator it = _menu->getItems ()->begin ();
	while (it != _menu->getItems ()->end ())
	{
		CMenuItem* item = (*it);
		if (item->isSeparator ())
		{
			AppendMenu (menu, MF_SEPARATOR, 0, 0);
		}
		else
		{
			char* titleWithPrefixNumbers = 0;
			if (_menu->getPrefixNumbers ())
			{
				titleWithPrefixNumbers = (char*)std::malloc (strlen (item->getTitle ()) + 50);
				switch (_menu->getPrefixNumbers ())
				{
					case 2:
					{
						sprintf (titleWithPrefixNumbers, "%1d %s", inc+1, item->getTitle ());
						break;
					}
					case 3:
					{
						sprintf (titleWithPrefixNumbers, "%02d %s", inc+1, item->getTitle ());
						break;
					}
					case 4:
					{
						sprintf (titleWithPrefixNumbers, "%03d %s", inc+1, item->getTitle ());
						break;
					}
				}
			}
			UTF8StringHelper entryText (titleWithPrefixNumbers ? titleWithPrefixNumbers : item->getTitle ());
			flags = MF_STRING;
			if (nbEntries < 160 && _menu->getNbItemsPerColumn () > 0 && inc && !(inc % _menu->getNbItemsPerColumn ()))
				flags |= MF_MENUBARBREAK;

			if (item->getSubmenu ())
			{
				HMENU submenu = createMenu (item->getSubmenu (), offsetIdx);
				if (submenu)
				{
					AppendMenu (menu, flags|MF_POPUP|MF_ENABLED, (UINT_PTR)submenu, (const TCHAR*)entryText);
				}
			}
			else
			{
				if (item->isEnabled ())
					flags |= MF_ENABLED;
				else
					flags |= MF_GRAYED;
				if (item->isTitle ())
					flags |= MF_DISABLED;
				if (multipleCheck && item->isChecked ())
					flags |= MF_CHECKED;
				if (_menu->getStyle () & kCheckStyle && inc == _menu->getCurrentIndex ())
					flags |= MF_CHECKED;
				if (!(flags & MF_CHECKED))
					flags |= MF_UNCHECKED;
				AppendMenu (menu, flags, offset + inc, entryText);
				IPlatformBitmap* platformBitmap = item->getIcon () ? item->getIcon ()->getPlatformBitmap () : 0;
				if (platformBitmap)
				{
					Win32BitmapBase* win32Bitmap = dynamic_cast<Win32BitmapBase*> (platformBitmap);
					if (win32Bitmap)
					{
						MENUITEMINFO mInfo = {0};
						mInfo.cbSize = sizeof (MENUITEMINFO);
						mInfo.fMask = MIIM_BITMAP;
						HBITMAP hBmp = win32Bitmap->createHBitmap ();
						if (hBmp)
						{
							mInfo.hbmpItem = hBmp;
							SetMenuItemInfo (menu, offset + inc, TRUE, &mInfo);
							bitmaps.push_back (hBmp);
						}
					}
				}
			}
			if (titleWithPrefixNumbers)
				std::free (titleWithPrefixNumbers);
		}
		inc++;
		it++;
	}
	return menu;
}