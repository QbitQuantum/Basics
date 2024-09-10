/**
 ****************************************************************************
 * @brief Returns the application's data directory
 *
 *   This returns c:\documents and settings\[user]\application data\mysql on
 * on Windows and ~/.mysql on Linux
 *
 * @param param nil
 * @param data pointer to the Grt
 * 
 * @return the application's data directory
 *****************************************************************************/
MYX_GRT_VALUE * get_app_data_dir(MYX_GRT_VALUE *param, void *data)
{
  MYX_GRT_VALUE *value;
  char *data_dir;
#if defined(__WIN__) || defined(_WIN32) || defined(_WIN64)
  LPITEMIDLIST pidl;
  char path[MAX_PATH];

  SHGetFolderLocation(NULL, CSIDL_APPDATA, NULL, 0, &pidl);

  SHGetPathFromIDList(pidl, path);

  CoTaskMemFree(pidl);

  data_dir= g_strdup_printf("%s\\MySQL\\", path);

#elif defined(__APPLE__)
  data_dir= g_strdup_printf("%s/Library/Application Support/MySQL/", g_get_home_dir());
#else
  data_dir= g_strdup_printf("%s/.mysqlgui/", g_get_home_dir());
#endif

  value= myx_grt_value_from_string(data_dir);

  g_free(data_dir);

  return make_return_value(value);
}