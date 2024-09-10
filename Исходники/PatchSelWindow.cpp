void PatchSelWindow::patchSelected (GdkEventButton *b)
{
    if (b && b->type == GDK_BUTTON_PRESS)
    {
        Glib::RefPtr<Gtk::TreeView::Selection> refSelection = 
            patchView.get_selection();

        if (refSelection)
        {
            Gtk::TreeModel::iterator iter;
            Gtk::TreeModel::Path path;
            Gtk::TreeViewColumn *col;
            int cell_x, cell_y; 

            if (patchView.get_path_at_pos((int)b->x, (int)b->y, path, col, 
                                      cell_x, cell_y))
                refSelection->select(path);
        }
    }
}