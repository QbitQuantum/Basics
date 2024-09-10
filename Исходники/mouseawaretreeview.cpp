bool MouseAwareTreeView::queueDrawIfNeccesary(int32_t x, int32_t y, Glib::ustring* pPath)
{
    Gtk::TreeModel::Path mousePath;
    Gtk::TreeViewColumn* pColumn;
    Gdk::Rectangle rect;

    convert_bin_window_to_widget_coords (x, y, m_MouseInfo.x, m_MouseInfo.y);

    if (get_path_at_pos(x, y, mousePath, pColumn, x, y))
    {
        int32_t offsetX, offsetY;
        convert_bin_window_to_widget_coords(0, 0, offsetX, offsetY);

        m_MouseInfo.x -= offsetX;
        m_MouseInfo.y -= offsetY;

        get_cell_area(mousePath, *pColumn, rect);
        queue_draw_area(rect.get_x() + offsetX, rect.get_y() + offsetY, rect.get_width(), rect.get_height());
        if (rect.get_y() != m_CurrentCell)
        {
            m_CurrentCell = rect.get_y();
            m_CellChanged = true;
        }

        if (pPath)
        {
            *pPath = mousePath.to_string();
        }
        return true;
    }

    return false;
}