A4(PRIVATE, void, dobuttons, INTEGER, id, INTEGER, offsetx,
   INTEGER, offsety, BOOLEAN, demo_button_p)
{
    struct bdef *bp;
    struct sdef *sp;
    struct pdef *pp;
    int i;
    EventRecord evt;
    int done;
    int tcnt, twid;
    Point p;
#define BILLBUTTONS /*  */
#if defined (BILLBUTTONS)
    INTEGER h, v;
#endif /* BILLBUTTONS */
    char *textp;

    if ((bp = (struct bdef *) findid(id))) {
        for (i = 0; i < Cx(bp->nbut); i++) {

            /* Offset buttons; this hack is to center the splash screen
             * on non-512x342 root windows...yuck!
             */

            C_OffsetRect (&bp->buts[i].butloc, offsetx, offsety);
            if ((sp = (struct sdef *)findid(CW(bp->buts[i].butstrid)))) {
                if (demo_button_p && sp->text[0] == 'O' && sp->text[1] == 'K')
                    textp = "Demo";
                else
                    textp = sp->text;
                tcnt = strlen(textp);
                twid = TextWidth((Ptr) textp, 0, tcnt);
                MoveTo((CW(bp->buts[i].butloc.left)  +
                        CW(bp->buts[i].butloc.right) - twid) / 2,
                       (CW(bp->buts[i].butloc.top)   +
                        CW(bp->buts[i].butloc.bottom)) / 2 + 4);
                DrawText((Ptr) textp, 0, tcnt);
            }
#if defined (BILLBUTTONS)
            h = CW(bp->buts[i].butloc.right) - CW(bp->buts[i].butloc.left);
            v = (CW(bp->buts[i].butloc.bottom) - CW(bp->buts[i].butloc.top))/2;
            if (h > v)
                h = v;
            if (!(ROMlib_options & ROMLIB_RECT_SCREEN_BIT))
                FrameRoundRect(&bp->buts[i].butloc, h, v);
            else
                FrameRect(&bp->buts[i].butloc);
#else /* BILLBUTTONS */
            if (!(ROMlib_options & ROMLIB_RECT_SCREEN_BIT))
                FrameRoundRect(&bp->buts[i].butloc, 10, 10);
            else
                FrameRect(&bp->buts[i].butloc);
#endif /* BILLBUTTONS */
        }

        for (done = 0; !done;) {
            C_GetNextEvent(mDownMask|keyDownMask, &evt);
            if (evt.what == CWC(mouseDown) || evt.what == CWC(keyDown)) {
                p.h = CW(evt.where.h);
                p.v = CW(evt.where.v);
                for (i = 0; !done && i < CW(bp->nbut); i++) {
                    if (PtInRect(p, &bp->buts[i].butloc) ||
                            ((evt.what == CWC(keyDown)) &&
                             (((CL(evt.message) & charCodeMask) == '\r') ||
                              ((CL(evt.message) & charCodeMask) == NUMPAD_ENTER)))
                       ) {
                        if ((pp = (struct pdef *)
                                  findid(CW(bp->buts[i].butprocid))))
                            /* NOTE:  we will have to do a better
                                  job here sometime */
                            (*(void (*)(void))MR(pp->proc))();
                        done = 1;
                    }
                }
                if (!done)
                    SysBeep(1);
            }
        }
        if (evt.what == CWC(mouseDown))
            while (!C_GetNextEvent(mUpMask, &evt))
                ;

        /* Move all buttons back. */
        for (i = 0; i < Cx(bp->nbut); i++)
            C_OffsetRect (&bp->buts[i].butloc, -offsetx, -offsety);
    }
}