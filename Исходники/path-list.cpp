void PathListWin::DrawItem(wal::GC& gc, int n, crect rect)
{
    const PathList::Data* curr = m_dataList.GetData(n);
    if (curr)
    {
		 std::vector<unicode_t> text = GetItemText( curr );

        UiCondList ucl;
        if ((n % 2) == 0)
        {
            ucl.Set(uiOdd, true);
        }

        if (n == this->GetCurrent())
        {
            ucl.Set(uiCurrentItem, true);
        }

        unsigned bg = UiGetColor(uiBackground, uiItem, &ucl, 0xB0B000);
        unsigned color = UiGetColor(uiColor, uiItem, &ucl, 0);
//        unsigned fcColor = UiGetColor(uiFcColor, uiItem, &ucl, 0xFFFF);

        gc.SetFillColor(bg);
        gc.FillRect(rect);

        gc.Set(GetFont());
        gc.SetTextColor(color);
		  gc.TextOutF( rect.left + 10, rect.top + 1, text.data() );
        //gc.SetTextColor(fcColor);
        //gc.TextOutF(rect.left + 10, rect.top + 1, name, 1);
    }
    else
    {
        gc.SetFillColor(UiGetColor(uiBackground, 0, 0, 0xB0B000));
        gc.FillRect(rect);
    }
}