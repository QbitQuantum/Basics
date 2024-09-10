bool ItemView::isHit(GdkEventButton* event, Gdk::Rectangle& rect)
{
    const int left = rect.get_x();
    const int top = rect.get_y();
    const int right = left + rect.get_width();
    const int bottom = top + rect.get_height();

    if (event->x > left && event->x < right)
        if (event->y > top && event->y < bottom)
            return true;

    return false;}