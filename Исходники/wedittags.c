VOID TagsPopUp(char *tags, char *msg)
{
  HWND hwnd = GetActiveWindow();
  EitherTagsPopUp(tags, msg, FALSE);
  SetActiveWindow(hwnd);
}