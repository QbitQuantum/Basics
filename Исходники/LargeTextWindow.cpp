void
LargeTextWindow::OnPaint(Canvas &canvas)
{
    canvas.ClearWhite();

    PixelRect rc(0, 0, canvas.GetWidth() - 1, canvas.GetHeight() - 1);
    canvas.DrawOutlineRectangle(rc.left, rc.top, rc.right, rc.bottom,
                                COLOR_BLACK);

    if (value.empty())
        return;

    const PixelScalar padding = Layout::GetTextPadding();
    rc.Grow(-padding);

    canvas.SetBackgroundTransparent();
    canvas.SetTextColor(COLOR_BLACK);

    rc.top -= origin * GetFont().GetHeight();

#ifndef USE_GDI
    canvas.Select(GetFont());
#endif
    canvas.DrawFormattedText(&rc, value.c_str(), DT_LEFT | DT_WORDBREAK);
}