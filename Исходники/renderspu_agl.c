void renderspu_SystemWindowVisibleRegion(WindowInfo *window, GLint cRects, const GLint* pRects)
{
    CRASSERT(window);
    CRASSERT(window->window);

    /* Remember any additional clipping stuff e.g. seamless regions */
    if (window->hVisibleRegion)
    {
        DisposeRgn(window->hVisibleRegion);
        window->hVisibleRegion = 0;
    }

    if (cRects>0)
    {
        int i;
        /* Create some temporary regions */
        RgnHandle rgn = NewRgn();
        SetEmptyRgn (rgn);
        RgnHandle tmpRgn = NewRgn();
        for (i=0; i<cRects; ++i)
        {
            SetRectRgn (tmpRgn,
                        pRects[4*i]  , pRects[4*i+1],
                        pRects[4*i+2], pRects[4*i+3]);
            //DEBUG_MSG_POETZSCH (("visible rect %d %d %d %d\n", pRects[4*i]  , pRects[4*i+1],
            //                     pRects[4*i+2], pRects[4*i+3]));
            UnionRgn (rgn, tmpRgn, rgn);
        }
        DisposeRgn (tmpRgn);
        window->hVisibleRegion = rgn;
    }

    renderspu_SystemWindowApplyVisibleRegion(window);
}