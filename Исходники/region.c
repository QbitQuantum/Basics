static GpStatus get_path_hrgn(GpPath *path, GpGraphics *graphics, HRGN *hrgn)
{
    HDC new_hdc=NULL;
    GpGraphics *new_graphics=NULL;
    GpStatus stat;
    INT save_state;

    if (!graphics)
    {
        new_hdc = GetDC(0);
        if (!new_hdc)
            return OutOfMemory;

        stat = GdipCreateFromHDC(new_hdc, &new_graphics);
        graphics = new_graphics;
        if (stat != Ok)
        {
            ReleaseDC(0, new_hdc);
            return stat;
        }
    }
    else if (!graphics->hdc)
    {
        graphics->hdc = new_hdc = GetDC(0);
        if (!new_hdc)
            return OutOfMemory;
    }

    save_state = SaveDC(graphics->hdc);
    EndPath(graphics->hdc);

    SetPolyFillMode(graphics->hdc, (path->fill == FillModeAlternate ? ALTERNATE
                                                                    : WINDING));

    stat = trace_path(graphics, path);
    if (stat == Ok)
    {
        *hrgn = PathToRegion(graphics->hdc);
        stat = *hrgn ? Ok : OutOfMemory;
    }

    RestoreDC(graphics->hdc, save_state);
    if (new_hdc)
    {
        ReleaseDC(0, new_hdc);
        if (new_graphics)
            GdipDeleteGraphics(new_graphics);
        else
            graphics->hdc = NULL;
    }

    return stat;
}