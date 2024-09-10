static IShellItem *
get_shell_item_for_uri (const char *uri)
{
  IShellItem *item;
  HRESULT hr;
  gunichar2 *uri_w = g_utf8_to_utf16 (uri, -1, NULL, NULL, NULL);

  hr = SHCreateItemFromParsingName(uri_w, 0, &IID_IShellItem, (LPVOID *) &item);
  if (SUCCEEDED (hr))
    return item;
  else
    g_warning_hr ("Can't create shell item from shortcut", hr);

  return NULL;
}