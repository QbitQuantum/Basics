bool SystemDraw::ExcludeClipOp(const Rect& r)
{
    GuiLock __;
#ifdef PLATFORM_WINCE
    int q = ExcludeClipRect(handle, r.left, r.top, r.right, r.bottom);
#else
    LTIMING("ExcludeClip");
    if(r.Contains(drawingclip))
        drawingclip = Rect(0, 0, 0, 0);
    Rect rr = LPtoDP(r);
    HRGN hrgn = ::CreateRectRgnIndirect(rr);
    int q = ::ExtSelectClipRgn(handle, hrgn, RGN_DIFF);
    ASSERT(q != ERROR);
    ::DeleteObject(hrgn);
#endif
    return q == SIMPLEREGION || q == COMPLEXREGION;
}