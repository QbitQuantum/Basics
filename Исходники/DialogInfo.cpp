void HideInfoDialog()
{
  if (g_dlgInfo.GetSafeHwnd())
    g_dlgInfo.ShowWindow(SW_HIDE);
}