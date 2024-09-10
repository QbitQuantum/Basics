void WatchWindow::OnKeyDown(wxTreeEvent& event)
{

    if (event.GetKeyCode() == WXK_DELETE ||
        event.GetKeyCode() == WXK_BACK)
    {
        wxTreeItemId item = GetSelection();

        if (item.IsOk() && GetItemParent(item) == m_root)
        {

            wxTreeItemId next = GetNextSibling(item);

            Delete(item);
            CreateEmptySlotIfNeeded();

            // Select the next item.

            if (!next.IsOk())
            {
                wxTreeItemIdValue cookie;
                next = GetLastChild(GetRootItem(), cookie);
            }

            SelectItem(next);

        }
    }
    else
    {

        // If we're not currently editing a field, begin editing. This
        // eliminates the need to double click to begin editing.

        int code = event.GetKeyCode();

        if (!m_editing && code < 256 && (isgraph(code) || IsSpace(code)))
        {

            // Get the currently selected item in the list.

            wxTreeItemId item = GetSelection();
            
            if (item.IsOk())
            {
                if (IsSpace(code))
                {
                    EditLabel(item, "");
                }
                else
                {
                    EditLabel(item, wxString(static_cast<char>(code)));
                }

                event.Skip(false);
            }

        }
        else
        {
            event.Skip(true);
        }


    }

}