MenuRef IGraphicsCarbon::CreateMenu(IPopupMenu* pMenu)
{
  MenuRef menuRef = 0;
  ResID menuID = UniqueID ('MENU');

  int numItems = pMenu->GetNItems();

  if (numItems && CreateNewMenu(menuID, kMenuAttrCondenseSeparators, &menuRef) == noErr)
  {
    for (int i = 0; i < numItems; ++i)
    {
      IPopupMenuItem* menuItem = pMenu->GetItem(i);

      if (menuItem->GetIsSeparator())
      {
        AppendMenuItemTextWithCFString(menuRef, CFSTR(""), kMenuItemAttrSeparator, 0, NULL);
      }
      else
      {
        CFStringRef itemString = CFStringCreateWithCString(NULL, menuItem->GetText(), kCFStringEncodingUTF8);

        if (pMenu->GetPrefix())
        {
          CFStringRef prefixString = 0;

          switch (pMenu->GetPrefix())
          {
            case 0:
              prefixString = CFStringCreateWithFormat(NULL, 0, CFSTR(""),i+1); break;
            case 1:
              prefixString = CFStringCreateWithFormat(NULL, 0, CFSTR("%1d: "),i+1); break;
            case 2:
              prefixString = CFStringCreateWithFormat(NULL, 0, CFSTR("%02d: "),i+1); break;
            case 3:
              prefixString = CFStringCreateWithFormat(NULL, 0, CFSTR("%03d: "),i+1); break;
          }

          CFMutableStringRef newItemString = CFStringCreateMutable(0, 0);
          CFStringAppend (newItemString, prefixString);
          CFStringAppend (newItemString, itemString);
          CFRelease (itemString);
          CFRelease (prefixString);
          itemString = newItemString;
        }

        if (itemString == 0)
          continue;

        MenuItemAttributes itemAttribs = kMenuItemAttrIgnoreMeta;

        if (!menuItem->GetEnabled())
        {
          itemAttribs |= kMenuItemAttrDisabled;
        }

        if (menuItem->GetIsTitle())
        {
          itemAttribs |= kMenuItemAttrSectionHeader;
        }

        InsertMenuItemTextWithCFString(menuRef, itemString, i, itemAttribs, 0);

        if (menuItem->GetChecked())
        {
          CheckMenuItem(menuRef, i+1, true);
        }

        if (menuItem->GetSubmenu())
        {
          MenuRef submenu = CreateMenu(menuItem->GetSubmenu());

          if (submenu)
          {
            SetMenuItemHierarchicalMenu(menuRef, i+1, submenu);
            CFRelease (submenu);
          }
        }

        CFRelease (itemString);
      }
    }

    //  if (pMenu->getStyle() & kCheckStyle && !multipleCheck)
    //    CheckMenuItem (menuRef, pMenu->getCurrentIndex (true) + 1, true);
    SetMenuItemRefCon(menuRef, 0, (int32_t)pMenu);
    //swell collision
    #undef InsertMenu
    InsertMenu(menuRef, kInsertHierarchicalMenu);
    #define InsertMenu SWELL_InsertMenu
  }

  return menuRef;
}