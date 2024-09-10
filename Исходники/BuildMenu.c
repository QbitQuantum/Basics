EFI_STATUS
AddMenuItemCheckValue (
  IN CHAR16                       *ItemNameText,
  IN UINTN                        MaxValue,
  IN UINTN                        MinValue,
  IN UINTN                        DefaultValue,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add number range for a number edit menu item in menu page

Arguments:

  ItemNameText  - A name string of the menu item
  MaxValue      - The maximum value of the menu item
  MinValue      - The minimum value of the menu item
  DefaultValue  - The default value of the menu item
  Page          - A pointer to the menu page

Returns:

  EFI_SUCCESS   - Add Edit menu item successfully
  Other Value   - Something failed

--*/
{
  EFI_MENU_ITEM         *MenuItem;

  if (ItemNameText == NULL || Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MenuItem = Page->Body.ItemList;

  //
  //Go through meun item list to search for the required menu item according to its name.
  //
  while(MenuItem != NULL) {
    if (StriCmp (MenuItem->ItemString.Text, ItemNameText) == 0) {

      //
      //Find a menu item matching the name, check its type
      //
      if ((MenuItem->ItemType & EFI_EDIT_SUB_TYPE_MASK) != EFI_ITEM_EDIT_NUMBER) {
        return EFI_INVALID_PARAMETER;
      }
      MenuItem->CheckValue = TRUE;
      MenuItem->MaxValue   = MaxValue;
      MenuItem->MinValue   = MinValue;
      MenuItem->DefaultValue = DefaultValue;
      break;
    }
    MenuItem = MenuItem->Next;
  }

  return EFI_SUCCESS;
}