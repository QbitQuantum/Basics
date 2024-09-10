void CGeneralCRC::OnDelete()
{
	// First check that we selected from the list (using Select menu)
	// else we don't know what to delete
	if (last_selected_ < last_predefined_ || last_selected_ >= settings_.size())
	{
		assert(0);   // Code should prevent this from happening
		return;
	}

	// Delete from the Select menu
	CMenu menu;
	menu.Attach(select_menu_.m_hMenu);
	CString strName = get_menu_text(&menu, last_selected_);  // save mneu item name - used to delete reg value by name

	CString mess;
	mess.Format("Are you sure you want to delete the settings for %s", strName);
	if (TaskMessageBox("Delete CRC Settings", mess, MB_YESNO) != IDYES)
	{
		menu.Detach();
		return;
	}
	menu.DeleteMenu(last_selected_, MF_BYCOMMAND);  // Delete menu item with selected ID
	menu.Detach();

	// Delete from settings_ (where ID == last_selected_ is the index into the array)
	settings_[last_selected_] = CString("");  // clear but don't delete unused entries (else menu item ID's won't mathc array indices)

	// Remove the setting from the registry
	HKEY hkey;
	if (::RegCreateKey(HKEY_CURRENT_USER, reg_locn, &hkey) == ERROR_SUCCESS)
	{
		::RegDeleteValue(hkey, strName);
		::RegCloseKey(hkey);
	}

	// Disable Delete button now as we just deleted it
	GetDlgItem(IDC_CRC_DELETE)->EnableWindow(FALSE);
}