void PictureControl::Paint()
{
    if (pic_) {
        CDC* d = GetDC();
        if (d) {
            d->SetStretchBltMode(HALFTONE);

            CDC c;
            if (c.CreateCompatibleDC(d)) {
                RECT r;
                GetClientRect(&r);

                BITMAP i = {0};
                GetObject(pic_.get(), sizeof(i), &i);

                c.SelectObject(pic_.get());
                d->StretchBlt(0, 0, r.right, r.bottom, &c, 0, 0, i.bmWidth,
                              i.bmHeight, SRCCOPY);
            }
            ReleaseDC(d);
        }
    }
}