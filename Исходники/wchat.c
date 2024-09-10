// front end
void ChatPopDown()
{
  if(--chatCount <= 0)
	CheckMenuItem(GetMenu(hwndMain), IDM_NewChat, MF_UNCHECKED);
}