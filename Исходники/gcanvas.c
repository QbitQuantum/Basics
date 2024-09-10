int GCsetwidgetattr(Gwidget_t * widget, int attrn, Gwattr_t * attrp)
{
    PIXsize_t ps;
    int ai, r, g, b, color;
    GdkColor *cp;

    for (ai = 0; ai < attrn; ai++) {
	switch (attrp[ai].id) {
	case G_ATTRSIZE:
	    GETSIZE(attrp[ai].u.s, ps, MINCWSIZE);
	    gtk_drawing_area_size(GTK_DRAWING_AREA(widget->w), ps.x, ps.y);
	    break;
	case G_ATTRBORDERWIDTH:
	    break;
	case G_ATTRCURSOR:
	    if (Strcmp(attrp[ai].u.t, "watch") == 0) {
		gdk_window_set_cursor(widget->w->window,
				      gdk_cursor_new(GDK_WATCH));
	    } else {
		gdk_window_set_cursor(widget->w->window,
				      gdk_cursor_new(GDK_LEFT_PTR));
	    }
	    Gsync();
	    break;
	case G_ATTRCOLOR:
	    color = attrp[ai].u.c.index;
	    if (color < 0 || color > G_MAXCOLORS) {
		Gerr(POS, G_ERRBADCOLORINDEX, color);
		return -1;
	    }
	    r = attrp[ai].u.c.r * 257;
	    g = attrp[ai].u.c.g * 257;
	    b = attrp[ai].u.c.b * 257;
	    cp = &WCU->colors[color].color;
	    if (WCU->colors[color].inuse)
		if (cp->red != r || cp->green != g || cp->blue != b)
		    if (color > 1 || WCU->allocedcolor[color])
			gdk_colormap_free_colors(WCU->cmap, cp, 1);

	    cp->red = r, cp->green = g, cp->blue = b;
	    if (gdk_colormap_alloc_color(WCU->cmap, cp, TRUE, TRUE)) {
		WCU->colors[color].inuse = TRUE;
		if (color <= 1)
		    WCU->allocedcolor[color] = TRUE;
	    }
	    cp->red = r, cp->green = g, cp->blue = b;
	    if (color == WCU->gattr.color)
		WCU->gattr.color = -1;
	    break;
	case G_ATTRVIEWPORT:
	    WCU->vsize.x = (int) (attrp[ai].u.s.x + 0.5);
	    WCU->vsize.y = (int) (attrp[ai].u.s.y + 0.5);
	    break;
	case G_ATTRWINDOW:
	    WCU->wrect = attrp[ai].u.r;
	    adjustclip(widget);
	    break;
	case G_ATTRWINDOWID:
	    Gerr(POS, G_ERRCANNOTSETATTR2, "windowid");
	    return -1;
	case G_ATTREVENTCB:
	    WCU->func = (Gcanvascb) attrp[ai].u.func;
	    break;
	case G_ATTRUSERDATA:
	    widget->udata = attrp[ai].u.u;
	    break;
	default:
	    Gerr(POS, G_ERRBADATTRID, attrp[ai].id);
	    return -1;
	}
    }
    return 0;
}