void GLUTAPIENTRY
glutChangeToMenuEntry(int num, const char *label, int value)
{
  GLUTmenuItem *item;
  int i;

  if (__glutMappedMenu) {
    menuModificationError();
  }
  i = __glutCurrentMenu->num;
  item = __glutCurrentMenu->list;
  while (item) {
    if (i == num) {
      if (item->isTrigger) {
        /* If changing a submenu trigger to a menu entry, we
           need to account for submenus.  */
        item->menu->submenus--;
	/* Nuke the Win32 menu. */
	DestroyMenu((HMENU) item->win);
      }
      free(item->label);

      item->label = strdup(label);
      if (!item->label)
	__glutFatalError("out of memory");
      item->isTrigger = FALSE;
      item->len = (int) strlen(label);
      item->value = value;
      item->unique = uniqueMenuHandler++;
      ModifyMenuA((HMENU) __glutCurrentMenu->win, (UINT) i - 1,
        MF_BYPOSITION | MFT_STRING, item->unique, label);

      return;
    }
    i--;
    item = item->next;
  }
  __glutWarning("Current menu has no %d item.", num);
}