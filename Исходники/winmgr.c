int FindNCHit(
    PWND pwnd,
    LONG lPt)
{
    POINT pt;
    RECT rcWindow;
    RECT rcClient;
    RECT rcClientAdj;
    int cBorders;
    int dxButton;

    pt.x = LOWORD(lPt);
    pt.y = HIWORD(lPt);

    if (!PtInRect(&pwnd->rcWindow, pt))
        return HTNOWHERE;

    if (TestWF(pwnd, WFMINIMIZED)) {
        CopyInflateRect(&rcWindow, &pwnd->rcWindow,
            -(SYSMET(CXFIXEDFRAME) + SYSMET(CXBORDER)), -(SYSMET(CYFIXEDFRAME) + SYSMET(CYBORDER)));

        if (!PtInRect(&rcWindow, pt))
            return HTCAPTION;

        goto CaptionHit;
    }

    // Get client rectangle
    rcClient = pwnd->rcClient;
    if (PtInRect(&rcClient, pt))
        return HTCLIENT;

    // Are we in "pseudo" client, i.e. the client & scrollbars & border
    if (TestWF(pwnd, WEFCLIENTEDGE))
        CopyInflateRect(&rcClientAdj, &rcClient, SYSMET(CXEDGE), SYSMET(CYEDGE));
    else
        rcClientAdj = rcClient;

    if (TestWF(pwnd, WFVPRESENT))
        rcClientAdj.right += SYSMET(CXVSCROLL);
    if (TestWF(pwnd, WFHPRESENT))
        rcClientAdj.bottom += SYSMET(CYHSCROLL);

    if (!PtInRect(&rcClientAdj, pt))
    {
        // Subtract out window borders
        cBorders = GetWindowBorders(pwnd->style, pwnd->ExStyle, TRUE, FALSE);
        CopyInflateRect(&rcWindow, &pwnd->rcWindow,
            -cBorders*SYSMET(CXBORDER), -cBorders*SYSMET(CYBORDER));

        // Are we on the border?
        if (!PtInRect(&rcWindow, pt))
        {
            // On a sizing border?
            if (!TestWF(pwnd, WFSIZEBOX)) {
                //
                // Old compatibility thing:  For 3.x windows that just had
                // a border, we returned HTNOWHERE, believe it or not,
                // because our hit-testing code was so brain dead.
                //
                if (!TestWF(pwnd, WFWIN40COMPAT) &&
                        !TestWF(pwnd, WFDLGFRAME)    &&
                        !TestWF(pwnd, WEFDLGMODALFRAME)) {
                    return(HTNOWHERE);

                } else {
                    return(HTBORDER);  // We are on a dlg frame.
                }
            } else {

                int ht;

                //
                // Note this improvement.  The HT codes are numbered so that
                // if you subtract HTSIZEFIRST-1 from them all, they sum up.  I.E.,
                // (HTLEFT - HTSIZEFIRST + 1) + (HTTOP - HTSIZEFIRST + 1) ==
                // (HTTOPLEFT - HTSIZEFIRST + 1).
                //

                if (TestWF(pwnd, WEFTOOLWINDOW))
                    InflateRect(&rcWindow, -SYSMET(CXSMSIZE), -SYSMET(CYSMSIZE));
                else
                    InflateRect(&rcWindow, -SYSMET(CXSIZE), -SYSMET(CYSIZE));

                if (pt.y < rcWindow.top)
                    ht = (HTTOP - HTSIZEFIRST + 1);
                else if (pt.y >= rcWindow.bottom)
                    ht = (HTBOTTOM - HTSIZEFIRST + 1);
                else
                    ht = 0;

                if (pt.x < rcWindow.left)
                    ht += (HTLEFT - HTSIZEFIRST + 1);
                else if (pt.x >= rcWindow.right)
                    ht += (HTRIGHT - HTSIZEFIRST + 1);

                return (ht + HTSIZEFIRST - 1);
            }
        }

        // Are we above the client area?
        if (pt.y < rcClientAdj.top)
        {
            // Are we in the caption?
            if (TestWF(pwnd, WFBORDERMASK) == LOBYTE(WFCAPTION))
            {
CaptionHit:
                if (pt.y >= rcWindow.top)
                {
                    if (TestWF(pwnd, WEFTOOLWINDOW))
                    {
                        rcWindow.top += SYSMET(CYSMCAPTION);
                        dxButton = SYSMET(CXSMSIZE);
                    }
                    else
                    {
                        rcWindow.top += SYSMET(CYCAPTION);
                        dxButton = SYSMET(CXSIZE);
                    }

                    if ((pt.y >= rcWindow.top) && TestWF(pwnd, WFMPRESENT))
                        return(HTMENU);

                    if ((pt.x >= rcWindow.left)  &&
                        (pt.x <  rcWindow.right) &&
                        (pt.y <  rcWindow.top))
                    {
                        // Are we in the window menu?
                        if (TestWF(pwnd, WFSYSMENU))
                        {
                            rcWindow.left += dxButton;
                            if (pt.x < rcWindow.left)
                            {
                                if (!_HasCaptionIcon(pwnd))
                                // iconless windows have no sysmenu hit rect
                                    return(HTCAPTION);

                                return(HTSYSMENU);
                            }
                        }
                        else if (TestWF(pwnd, WFWIN40COMPAT))
                            return(HTCAPTION);

                        // only a close button if window has a system menu

                        // Are we in the close button?
                        rcWindow.right -= dxButton;
                        if (pt.x >= rcWindow.right)
                            return HTCLOSE;

                        if ((pt.x < rcWindow.right) && !TestWF(pwnd, WEFTOOLWINDOW))
                        {
                            // Are we in the maximize/restore button?
                            if (TestWF(pwnd, (WFMAXBOX | WFMINBOX)))
                            {
                                // Note that sizing buttons are same width for both
                                // big captions and small captions.
                                rcWindow.right -= dxButton;
                                if (pt.x >= rcWindow.right)
                                    return HTZOOM;

                                // Are we in the minimize button?
                                rcWindow.right -= dxButton;
                                if (pt.x >= rcWindow.right)
                                    return HTREDUCE;
                            }
                            else if (TestWF(pwnd, WEFCONTEXTHELP))
                            {
                                rcWindow.right -= dxButton;
                                if (pt.x >= rcWindow.right)
                                    return HTHELP;
                            }
                        }
                    }
                }

                // We're in the caption proper
                return HTCAPTION;
            }

            //
            // Are we in the menu?
            //
            if (TestWF(pwnd, WFMPRESENT))
                return HTMENU;
        }
    }
    else
    {
        //
        // NOTE:
        // We can only be here if we are on the client edge, horz scroll,
        // sizebox, or vert scroll.  Hence, if we are not on the first 3,
        // we must be on the last one.
        //

        //
        // Are we on the client edge?
        //
        if (TestWF(pwnd, WEFCLIENTEDGE))
        {
            InflateRect(&rcClientAdj, -SYSMET(CXEDGE), -SYSMET(CYEDGE));
            if (!PtInRect(&rcClientAdj, pt))
                return(HTBORDER);
        }

        //
        // Are we on the scrollbars?
        //
        if (TestWF(pwnd, WFHPRESENT) && (pt.y >= rcClient.bottom))
        {
            UserAssert(pt.y < rcClientAdj.bottom);
            if (TestWF(pwnd, WFVPRESENT) && (pt.x >= rcClient.right))
                return(SizeBoxHwnd(pwnd) ? HTBOTTOMRIGHT : HTGROWBOX);
            else
                return(HTHSCROLL);
        }
        else
        {
            UserAssert(TestWF(pwnd, WFVPRESENT));
            UserAssert(pt.x >= rcClient.right);
            UserAssert(pt.x < rcClientAdj.right);
            return(HTVSCROLL);
        }
    }

    //
    // We give up.
    //
    // Win31 returned HTNOWHERE in this case; For compatibility, we will
    // keep it that way.
    //
    return(HTNOWHERE);

}