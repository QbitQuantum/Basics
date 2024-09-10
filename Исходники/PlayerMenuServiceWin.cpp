PlayerMenuItem *PlayerMenuServiceWin::addItem(const std::string &menuId,
                                              const std::string &title,
                                              const std::string &parentId,
                                              int order /* = MAX_ORDER */)
{
    if (menuId.length() == 0 || title.length() == 0)
    {
        CCLOG("MenuServiceWin::addItem() - menuId and title must is non-empty");
        return nullptr;
    }

    // check menu id is exists
    if (_items.find(menuId) != _items.end())
    {
        CCLOG("MenuServiceWin::addItem() - menu id (%s) is exists", menuId.c_str());
        return false;
    }

    // set parent
    PlayerMenuItemWin *parent = &_root;
    if (parentId.length())
    {
        // query parent menu
        auto it = _items.find(parentId);
        if (it != _items.end())
        {
            parent = it->second;
        }
    }

    if (!parent->_hmenu)
    {
        // create menu handle for parent (convert parent to submenu)
        parent->_hmenu = CreateMenu();
        parent->_isGroup = true;
        MENUITEMINFO menuitem;
        menuitem.cbSize = sizeof(menuitem);
        menuitem.fMask = MIIM_SUBMENU;
        menuitem.hSubMenu = parent->_hmenu;
        if (!SetMenuItemInfo(parent->_parent->_hmenu, parent->_commandId, MF_BYCOMMAND, &menuitem))
        {
            DWORD err = GetLastError();
            CCLOG("MenuServiceWin::addItem() - set menu handle failed, menu id (%s). error code = %u", parent->_menuId.c_str(), err);
            return nullptr;
        }
    }

    // create new menu item
    _newCommandId++;
    PlayerMenuItemWin *item = PlayerMenuItemWin::create(menuId, title);
    item->_commandId = _newCommandId;
    item->_parent = parent;
    item->_parent->retain();

    // add menu item to menu bar
    MENUITEMINFO menuitem;
    menuitem.cbSize = sizeof(menuitem);
    menuitem.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
    menuitem.fType = (item->_title.compare("-") == 0) ? MFT_SEPARATOR : MFT_STRING;
    menuitem.fState = (item->_isEnabled) ? MFS_ENABLED : MFS_DISABLED;
    menuitem.fState |= (item->_isChecked) ? MFS_CHECKED : MFS_UNCHECKED;
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(item->_title, u16title);
    menuitem.dwTypeData = (LPTSTR)u16title.c_str();
    menuitem.wID = _newCommandId;

    // check new menu item position
    if (order > parent->_children.size())
    {
        order = parent->_children.size();
    }
    else if (order < 0)
    {
        order = 0;
    }

    // create new menu item
    if (!InsertMenuItem(parent->_hmenu, order, TRUE, &menuitem))
    {
        DWORD err = GetLastError();
        CCLOG("MenuServiceWin::addItem() - insert new menu item failed, menu id (%s). error code = %u", item->_menuId.c_str(), err);
        item->release();
        return nullptr;
    }

    // update menu state
    parent->_children.insert(order, item);
    _items[item->_menuId] = item;
    _commandId2menuId[item->_commandId] = item->_menuId;
    updateChildrenOrder(parent);

    return item;
}