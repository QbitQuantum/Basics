void PopupMenu::checkItem(S32 pos, bool checked)
{
//    U32 flags = checked ? MF_CHECKED : MF_UNCHECKED;
//    CheckMenuItem(mData->mMenu, pos, MF_BYPOSITION|flags);

   MENUITEMINFOA mi;
   mi.cbSize = sizeof(mi);
   mi.fMask = MIIM_STATE;
   mi.fState = checked ? MFS_CHECKED : MFS_UNCHECKED;
   SetMenuItemInfoA(mData->mMenu, pos, TRUE, &mi);
}