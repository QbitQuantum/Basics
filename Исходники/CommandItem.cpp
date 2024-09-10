void StringItem::Measure(HDC hDC, SIZE *size)
{
    MenuItem::Measure(hDC, size);
    if (false == Settings_menu.showBroams)
    {
        size->cx = imax(size->cx + 20, 120);
        size->cy += 6;
    }
    SetRectEmpty(&m_textrect);
}