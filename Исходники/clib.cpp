//////////////////////////////////////
// new gui methods
clibwindow* clib::open_window(int x, int y, int w, int h, unsigned short bgc, unsigned short fgc)
{
    // before drawing the window, we save the contents of the screen
    // where the window will be drawn so that we can redraw the screen
    // when the window is closed.
    clibwindow* wnd = new clibwindow(x, y, w, h);

    _COORD		w_sz;
    _COORD		w_p;
    _SMALL_RECT w_b;
    w_p.X		= 0;
    w_p.Y		= 0;
    w_sz.X		= w;
    w_sz.Y		= h;
    w_b.Left	= x;
    w_b.Top		= y;
    w_b.Right	= x + w-1;
    w_b.Bottom	= y + h-1;

    //if(!ReadConsoleOutputA(screen_, (_CHAR_INFO*)_window_buffer_, w_sz, w_p, &w_b))
    if(!ReadConsoleOutputA(screen_, (_CHAR_INFO*)wnd->buffer_, w_sz, w_p, &w_b))
    {
        char eb[1024];
        sprintf_s(eb,1024,"ReadConsoleOutputA failed!\n\nError Code: %d",GetLastError());
        ::MessageBox(0,eb,"Error",MB_OK|MB_ICONEXCLAMATION);
    }


    // draw the window
    //this->set_bgcolor(4);		// blue background
    //this->set_fgcolor(1|2|4|8); // bright white foreground

    this->set_bgcolor(bgc);
    this->set_fgcolor(fgc);

    for (int cy = 1; cy < h - 1; cy++)
    {
        for (int cx = 1; cx < w - 1; cx++)
        {
            this->outchar(x+cx, y+cy, ' ');
        }
    }

    // draw top and bottom edge
    {   for (int cx = 0; cx < w; cx++)
        {
            this->outchar(x+cx, y, (char)205);
            this->outchar(x+cx, y+(h-1), (char)205);
        }
    }

    // draw left and right edge
    {   for (int cy = 0; cy < h; cy++)
        {
            this->outchar(x, y+cy, (char)186);
            this->outchar(x+(w-1), y+cy, (char)186);
        }
    }

    // draw corners
    this->outchar(x, y, (char)201);
    this->outchar(x, y+(h-1), (char)200);
    this->outchar(x+(w-1), y, (char)187);
    this->outchar(x+(w-1), y+(h-1), (char)188);

    // return the saved window
    return wnd;
}