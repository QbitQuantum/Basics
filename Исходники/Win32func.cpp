/**
 * General function for changing registry entries, creates if they dont already exist
 *
 * @param const char *reg_path - Path of key
 * @param const char *keyname  - Name of subkey
 * @param int reg_type		   - HKEY_CLASSES_ROOT, HKEY_CURRENT_CONFIG, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_USERS
 * @param void *data		   - Pointer to the data
 * @param int data_len		   - Length of data in buffer
 *
 * @return bool - states if value set happened OK
 */
bool reg_set_value(const char *reg_path, const char *keyname, int reg_type, void *data, int data_len)
{
	// Try to open the correct registry dir
	HKEY hkey = reg_open_dir(reg_path);

	if(hkey == NULL)
	{
		return false;
	}

	if(RegSetValueEx(hkey, keyname, 0, reg_type, (BYTE *) data, data_len) != ERROR_SUCCESS)
	{
		RegCloseKey(hkey);
		return false;
	}

	RegFlushKey(hkey);
  	RegCloseKey(hkey);
	return true;
}