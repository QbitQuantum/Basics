	/*static*/
	int Win32MenuItem::GetNativeMenuItemPosition(NativeItemBits* bits)
	{
		int count = GetMenuItemCount(bits->parentMenu);
		for (int i = 0; i < count; i++)
		{

			if ((bits->submenu && GetSubMenu(bits->parentMenu, i) == bits->submenu) ||
				(bits->id == GetMenuItemID(bits->parentMenu, i)))
				return i;
		}

		throw ValueException::FromString("Could not find native item index in native menu.");
	}