int GScreatewidget (Gwidget_t *parent, Gwidget_t *widget,
        int attrn, Gwattr_t *attrp) {
    PIXsize_t ps;
#if XlibSpecificationRelease < 5
    Widget w;
#endif
    int ai;
    XColor c;
    int color;

    if (!parent) {
        Gerr (POS, G_ERRNOPARENTWIDGET);
        return -1;
    }
    ps.x = ps.y = MINSWSIZE;
    RESETARGS;
    for (ai = 0; ai < attrn; ai++) {
        switch (attrp[ai].id) {
        case G_ATTRSIZE:
            GETSIZE (attrp[ai].u.s, ps, MINSWSIZE);
            break;
        case G_ATTRBORDERWIDTH:
            ADD2ARGS (XtNborderWidth, attrp[ai].u.i);
            break;
        case G_ATTRCHILDCENTER:
            Gerr (POS, G_ERRCANNOTSETATTR1, "childcenter");
            return -1;
        case G_ATTRMODE:
            if (Strcmp ("forcebars", attrp[ai].u.t) == 0)
                ADD2ARGS (XtNforceBars, True);
            else {
                Gerr (POS, G_ERRBADATTRVALUE, attrp[ai].u.t);
                return -1;
            }
            break;
        case G_ATTRCOLOR:
            color = attrp[ai].u.c.index;
            if (color != 0 && color != 1) {
                Gerr (POS, G_ERRBADCOLORINDEX, color);
                return -1;
            }
            c.red = attrp[ai].u.c.r * 257;
            c.green = attrp[ai].u.c.g * 257;
            c.blue = attrp[ai].u.c.b * 257;
            if (XAllocColor (
                Gdisplay, DefaultColormap (Gdisplay, Gscreenn), &c
            )) {
                if (color == 0)
                    ADD2ARGS (XtNbackground, c.pixel);
                else
                    ADD2ARGS (XtNforeground, c.pixel);
	    }
            break;
        case G_ATTRWINDOWID:
            Gerr (POS, G_ERRCANNOTSETATTR1, "windowid");
            return -1;
        case G_ATTRUSERDATA:
            widget->udata = attrp[ai].u.u;
            break;
        default:
            Gerr (POS, G_ERRBADATTRID, attrp[ai].id);
            return -1;
        }
    }
    ADD2ARGS (XtNallowHoriz, True);
    ADD2ARGS (XtNallowVert, True);
    ADD2ARGS (XtNwidth, ps.x);
    ADD2ARGS (XtNheight, ps.y);
    if (!(widget->w = XtCreateWidget ("scroll", viewportWidgetClass,
            parent->w, argp, argn))) {
        Gerr (POS, G_ERRCANNOTCREATEWIDGET);
        return -1;
    }
#if XlibSpecificationRelease < 5
    RESETARGS;
    ADD2ARGS (XtNwidth, ps.x);
    ADD2ARGS (XtNheight, ps.y);
    if (!(w = XtCreateWidget ("owsucks", formWidgetClass,
            widget->w, argp, argn))) {
        Gerr (POS, G_ERRCANNOTCREATEWIDGET);
        return -1;
    }
    Glazymanage (w);
    Glazymanage (widget->w);
    XtDestroyWidget (w);
#else
    Glazymanage (widget->w);
#endif
    return 0;
}