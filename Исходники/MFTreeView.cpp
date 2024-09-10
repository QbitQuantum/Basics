LRESULT MFTreeView::OnRClick(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
{
   HMENU ctxMenu = CreatePopupMenu();

   WTL::CTreeItem item = GetDropHilightItem();
   if (item.IsNull())
   {
      item = GetSelectedItem();
   }
   MFTreeViewItem* pItem = (MFTreeViewItem*)item.GetData();

   if (pItem == NULL)
   {
      DestroyMenu(ctxMenu);
      return 0;
   }

   unsigned int nextID = pItem->AppendMenuCmd(ctxMenu, 1, item);

   if (GetMenuItemCount(ctxMenu) > 0)
   {
      AppendMenu(ctxMenu, MF_SEPARATOR, 0, NULL);
   }
   unsigned int refreshID = nextID++;
   nextID = AppendMenu(ctxMenu, MF_STRING, refreshID, _T("Refresh"));

   if (GetMenuItemCount(ctxMenu) == 0)
   {
      DestroyMenu(ctxMenu);
      return 0;
   }

   POINT pos;
   GetCursorPos(&pos);

   int command = TrackPopupMenuEx(ctxMenu, TPM_NONOTIFY | TPM_RETURNCMD, pos.x, pos.y, pnmh->hwndFrom, NULL);

   if (!pItem->HandleMenuCmd(command, item))
   {
      if (command == refreshID)
      {
         WTL::CTreeItem parent = item.GetParent();
         parent.Expand(TVE_COLLAPSE | TVE_COLLAPSERESET);
         parent.Expand();
      }
   }

   DestroyMenu(ctxMenu);

   return 1;
}