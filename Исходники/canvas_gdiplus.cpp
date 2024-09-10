    // static
    void CanvasGdiplus::InitializeDC(HDC context)
    {
        // Enables world transformation.
        // If the GM_ADVANCED graphics mode is set, GDI always draws arcs in the
        // counterclockwise direction in logical space. This is equivalent to the
        // statement that, in the GM_ADVANCED graphics mode, both arc control points
        // and arcs themselves fully respect the device context's world-to-device
        // transformation.
        BOOL res = SetGraphicsMode(context, GM_ADVANCED);
        DCHECK(res != 0);

        // Enables dithering.
        res = SetStretchBltMode(context, HALFTONE);
        DCHECK(res != 0);
        // As per SetStretchBltMode() documentation, SetBrushOrgEx() must be called
        // right after.
        res = SetBrushOrgEx(context, 0, 0, NULL);
        DCHECK(res != 0);

        // Sets up default orientation.
        res = SetArcDirection(context, AD_CLOCKWISE);
        DCHECK(res != 0);

        // Sets up default colors.
        res = SetBkColor(context, RGB(255, 255, 255));
        DCHECK(res != CLR_INVALID);
        res = SetTextColor(context, RGB(0, 0, 0));
        DCHECK(res != CLR_INVALID);
        res = SetDCBrushColor(context, RGB(255, 255, 255));
        DCHECK(res != CLR_INVALID);
        res = SetDCPenColor(context, RGB(0, 0, 0));
        DCHECK(res != CLR_INVALID);

        // Sets up default transparency.
        res = SetBkMode(context, OPAQUE);
        DCHECK(res != 0);
        res = SetROP2(context, R2_COPYPEN);
        DCHECK(res != 0);
    }