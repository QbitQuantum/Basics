/* change menu item checkmark */
void
check_menu_item(int menuid, int itemid, BOOL checked)
{
        CheckMenuItem(hmenu, itemid, MF_BYCOMMAND | (checked ? MF_CHECKED : MF_UNCHECKED));
}