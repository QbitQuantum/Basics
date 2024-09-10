bool DjVuEngineImpl::RenderPage(HDC hDC, RectI screenRect, int pageNo, float zoom, int rotation, RectD *pageRect, RenderTarget target, AbortCookie **cookie_out)
{
    bool success = true;
    RectD mediabox = PageMediabox(pageNo);
    HRGN clip = CreateRectRgn(screenRect.x, screenRect.y, screenRect.x + screenRect.dx, screenRect.y + screenRect.dy);
    SelectClipRgn(hDC, clip);

    DjVuAbortCookie *cookie = NULL;
    if (cookie_out)
        *cookie_out = cookie = new DjVuAbortCookie();

    // render in 1 MB bands, as otherwise GDI can run out of memory
    RectD rect = pageRect ? *pageRect : mediabox;
    int bandDy = (int)((1 << 20) / (rect.dy * zoom));
    PointI pt = Transform(rect, pageNo, zoom, rotation).TL().Convert<int>();

    for (int y = 0; y * bandDy < rect.dy; y++) {
        RectD pageBand(rect.x, y * bandDy, rect.dx, bandDy);
        pageBand = pageBand.Intersect(mediabox);
        RectI screenBand = Transform(pageBand, pageNo, zoom, rotation).Round();
        screenBand.Offset(screenRect.x - pt.x, screenRect.y - pt.y);

        RenderedBitmap *bmp = RenderBitmap(pageNo, zoom, rotation, &pageBand, target, cookie_out);
        if (bmp && bmp->GetBitmap())
            success = bmp->StretchDIBits(hDC, screenBand);
        else
            success = false;
        delete bmp;

        if (cookie && cookie->abort) {
            success = false;
            break;
        }
    }

    SelectClipRgn(hDC, NULL);
    return success;
}