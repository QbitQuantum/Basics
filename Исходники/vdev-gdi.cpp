static void vdev_gdi_enqueue(void *ctxt)
{
    DEVGDICTXT *c = (DEVGDICTXT*)ctxt;
    RECT        rect;

    GetClientRect(c->hwnd, &rect);
    if (memcmp(&c->rtlast, &rect, sizeof(RECT))) {
        memcpy(&c->rtlast, &rect, sizeof(RECT));

        int x, y, sw, sh, dw, dh;
        sw = dw = rect.right;
        sh = dh = rect.bottom;

        //++ keep picture w/h ratio when stretching ++//
        if (c->width * sh > c->height * sw) {
            dh = dw * c->height / c->width;
        } else {
            dw = dh * c->width / c->height;
        }
        x = (sw - dw) / 2;
        y = (sh - dh) / 2;
        //-- keep picture w/h ratio when stretching --//

        c->rtview.left   = x;
        c->rtview.top    = y;
        c->rtview.right  = x + dw;
        c->rtview.bottom = y + dh;

        RECT rect1, rect2, rect3, rect4;
        rect1.left = 0;    rect1.top = 0;    rect1.right = sw; rect1.bottom = y;
        rect2.left = 0;    rect2.top = y;    rect2.right = x;  rect2.bottom = y+dh;
        rect3.left = x+dw; rect3.top = y;    rect3.right = sw; rect3.bottom = y+dh;
        rect4.left = 0;    rect4.top = y+dh; rect4.right = sw; rect4.bottom = sh;
        InvalidateRect(c->hwnd, &rect1, TRUE);
        InvalidateRect(c->hwnd, &rect2, TRUE);
        InvalidateRect(c->hwnd, &rect3, TRUE);
        InvalidateRect(c->hwnd, &rect4, TRUE);
    }

    if (c->texttick > GetTickCount()) {
        SetBkMode   (c->hdcsrc, TRANSPARENT);
        SetTextColor(c->hdcsrc, RGB(255,255,255));
        TextOut(c->hdcsrc, c->textposx, c->textposy, c->textstr, (int)strlen(c->textstr));
    } else {
        c->priority = 0;
    }

    // bitblt picture to window witch stretching
    StretchBlt(c->hdcdst, c->rtview.left, c->rtview.top,
               c->rtview.right - c->rtview.left,
               c->rtview.bottom - c->rtview.top,
               c->hdcsrc, 0, 0, c->width, c->height, SRCCOPY);
}