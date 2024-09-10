static int glist_key(GGadget *g, GEvent *event) {
    GList *gl = (GList *) g;
    uint16 keysym = event->u.chr.keysym;
    int sofar_pos = gl->sofar_pos;
    int loff, xoff, sel=-1;
    int refresh = false;

    if ( event->type == et_charup )
return( false );
    if ( !g->takes_input || (g->state!=gs_enabled && g->state!=gs_active && g->state!=gs_focused ))
return(false );

    if ( gl->ispopup && event->u.chr.keysym == GK_Return ) {
	GListDoubleClick(gl,false,-1);
return( true );
    } else if ( gl->ispopup && event->u.chr.keysym == GK_Escape ) {
	GListClose(gl);
return( true );
    }

    if ( event->u.chr.keysym == GK_Return || event->u.chr.keysym == GK_Tab ||
	    event->u.chr.keysym == GK_BackTab || event->u.chr.keysym == GK_Escape )
return( false );

    GDrawCancelTimer(gl->enduser); gl->enduser = NULL; gl->sofar_pos = 0;

    loff = 0x80000000; xoff = 0x80000000; sel = -1;
    if ( keysym == GK_Home || keysym == GK_KP_Home || keysym == GK_Begin || keysym == GK_KP_Begin ) {
	loff = -gl->loff;
	xoff = -gl->xoff;
	sel = 0;
    } else if ( keysym == GK_End || keysym == GK_KP_End ) {
	loff = GListTopInWindow(gl,gl->ltot-1)-gl->loff;
	xoff = -gl->xoff;
	sel = gl->ltot-1;
    } else if ( keysym == GK_Up || keysym == GK_KP_Up ) {
	if (( sel = GListGetFirstSelPos(&gl->g)-1 )<0 ) {
	    /*if ( gl->loff!=0 ) loff = -1; else loff = 0;*/
	    sel = 0;
	}
    } else if ( keysym == GK_Down || keysym == GK_KP_Down ) {
	if (( sel = GListGetFirstSelPos(&gl->g))!= -1 )
	    ++sel;
	else
	    /*if ( gl->loff + GListLinesInWindow(gl,gl->loff)<gl->ltot ) loff = 1; else loff = 0;*/
	    sel = 0;
    } else if ( keysym == GK_Left || keysym == GK_KP_Left ) {
	xoff = -GDrawPointsToPixels(gl->g.base,6);
    } else if ( keysym == GK_Right || keysym == GK_KP_Right ) {
	xoff = GDrawPointsToPixels(gl->g.base,6);
    } else if ( keysym == GK_Page_Up || keysym == GK_KP_Page_Up ) {
	loff = GListTopInWindow(gl,gl->loff);
	if ( loff == gl->loff )		/* Normally we leave one line in window from before, except if only one line fits */
	    loff = GListTopInWindow(gl,gl->loff-1);
	loff -= gl->loff;
	if (( sel = GListGetFirstSelPos(&gl->g))!= -1 ) {
	    if (( sel += loff )<0 ) sel = 0;
	}
    } else if ( keysym == GK_Page_Down || keysym == GK_KP_Page_Down ) {
	loff = GListLinesInWindow(gl,gl->loff)-1;
	if ( loff<=0 ) loff = 1;
	if ( loff + gl->loff >= gl->ltot )
	    loff = GListTopInWindow(gl,gl->ltot-1)-gl->loff;
	if (( sel = GListGetFirstSelPos(&gl->g))!= -1 ) {
	    if (( sel += loff )>=gl->ltot ) sel = gl->ltot-1;
	}
    } else if ( keysym == GK_BackSpace && gl->orderer ) {
	/* ordered lists may be reversed by typing backspace */
	gl->backwards = !gl->backwards;
	GListOrderIt(gl);
	sel = GListGetFirstSelPos(&gl->g);
	if ( sel!=-1 ) {
	    int top = GListTopInWindow(gl,gl->ltot-1);
	    gl->loff = sel-1;
	    if ( gl->loff > top )
		gl->loff = top;
	    if ( sel-1<0 )
		gl->loff = 0;
	}
	GScrollBarSetPos(&gl->vsb->g,gl->loff);
	_ggadget_redraw(&gl->g);
return( true );
    } else if ( event->u.chr.chars[0]!='\0' && gl->orderer ) {
	int len = u_strlen(event->u.chr.chars);
	if ( sofar_pos+len >= gl->sofar_max ) {
	    if ( gl->sofar_max == 0 )
		gl->sofar = galloc((gl->sofar_max = len+10) * sizeof(unichar_t));
	    else
		gl->sofar = grealloc(gl->sofar,(gl->sofar_max = sofar_pos+len+10)*sizeof(unichar_t));
	}
	u_strcpy(gl->sofar+sofar_pos,event->u.chr.chars);
	gl->sofar_pos = sofar_pos + len;
	sel = GListFindPosition(gl,gl->sofar);
	gl->enduser = GDrawRequestTimer(gl->g.base,GListTypeTime,0,NULL);
    }

    if ( loff==0x80000000 && sel>=0 ) {
	if ( sel>=gl->ltot ) sel = gl->ltot-1;
	if ( sel<gl->loff ) loff = sel-gl->loff;
	else if ( sel>=gl->loff+GListLinesInWindow(gl,gl->loff) )
	    loff = sel-(gl->loff+GListLinesInWindow(gl,gl->loff)-1);
    } else
	sel = -1;
    if ( sel!=-1 ) {
	int wassel = gl->ti[sel]->selected;
	refresh = GListAnyOtherSels(gl,sel) || !wassel;
	GListSelectOne(&gl->g,sel);
	if ( refresh )
	    GListSelected(gl,false,sel);
    }
    if ( loff!=0x80000000 || xoff!=0x80000000 ) {
	if ( loff==0x80000000 ) loff = 0;
	if ( xoff==0x80000000 ) xoff = 0;
	GListScrollBy(gl,loff,xoff);
    }
    if ( refresh )
	_ggadget_redraw(g);
    if ( loff!=0x80000000 || xoff!=0x80000000 || sel!=-1 )
return( true );

return( false );
}