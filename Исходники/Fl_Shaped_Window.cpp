void Fl_Shaped_Window::draw()
{
    if ((lw != w() || lh != h() || changed) && shape_)
    {
        // size of window has change since last time
        lw = w(); lh = h();
        Fl_Bitmap* mask = resize_bitmap(shape_, w(), h());
#ifdef _WIN32
        HRGN region = bitmap2region(mask);
        SetWindowRgn(fl_xid(this), region, TRUE);
#elif defined(__APPLE__)
        // not yet implemented for Apple
#else
        Pixmap pmask = XCreateBitmapFromData(fl_display, fl_xid(this),
                                             (const char*)mask->data(), mask->width(), mask->height());
        hide();
        XShapeCombineMask(fl_display, fl_xid(this), ShapeBounding, 0, 0,
                          pmask, ShapeSet);
        show();
        if (pmask != None) XFreePixmap(fl_display, pmask);
#endif
        changed = 0;
    }
    Fl_Double_Window::draw();
}