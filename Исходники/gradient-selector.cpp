bool SPGradientSelector::_checkForSelected(const Gtk::TreePath &path, const Gtk::TreeIter& iter, SPGradient *vector)
{
    bool found = false;

    Gtk::TreeModel::Row row = *iter;
    if ( vector == row[columns->data] )
    {
        treeview->scroll_to_row(path, 0.5);
        Glib::RefPtr<Gtk::TreeSelection> select = treeview->get_selection();
        bool wasBlocked = blocked;
        blocked = true;
        select->select(iter);
        blocked = wasBlocked;
        found = true;
    }

    return found;
}