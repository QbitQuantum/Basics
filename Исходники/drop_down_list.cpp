bool DropDownList::onCharInParent(wxKeyEvent& ev) {
    // keyboard codes
    int k = ev.GetKeyCode();
    if (IsShown()) {
        if (open_sub_menu) {
            // sub menu always takes keys
            return open_sub_menu->onCharInParent(ev);
        } else {
            switch (k) {
            case WXK_UP:
                return selectItem(selected_item - 1);
            case WXK_DOWN:
                return selectItem(selected_item + 1);
            case WXK_RETURN:
                if (!showSubMenu() && (selected_item == NO_SELECTION || itemEnabled(selected_item))) {
                    hide(true, false); // don't veto; always close
                }
                break;
            case WXK_SPACE:
                if (!showSubMenu() && (selected_item == NO_SELECTION || itemEnabled(selected_item))) {
                    hide(true);
                }
                break;
            case WXK_ESCAPE:
                hide(false);
                break;
            case WXK_LEFT:
                if (parent_menu) hide(false);
                break;
            case WXK_RIGHT:
                return showSubMenu();
            default:
                // match first character of an item, start searching just after the current selection
                size_t si = selected_item != NO_SELECTION ? selected_item + 1 : 0;
                size_t count = itemCount();
                for (size_t i = 0 ; i < count ; ++i) {
                    size_t index = (si + i) % count;
                    if (!itemEnabled(index)) continue;
                    String c = itemText(index);
#ifdef UNICODE
                    if (!c.empty() && toUpper(c.GetChar(0)) == toUpper(ev.GetUnicodeKey())) {
#else
                    if (!c.empty() && toUpper(c.GetChar(0)) == toUpper(ev.GetKeyCode())) {
#endif
                        // first character matches
                        selected_item = index;
                        showSubMenu();
                        selectItem(index);
                        return true;
                    }
                }
            }
        }
        return true;
    }
    else if (k==WXK_SPACE || k==WXK_RETURN || k==WXK_DOWN) {
        // drop down list is not shown yet, show it now
        show(false, wxPoint(0,0));
        return true;
    }
    return false;
}