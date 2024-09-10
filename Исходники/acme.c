void
mousethread(void *v)
{
	Text *t, *argt;
	int but;
	uint q0, q1;
	Window *w;
	Plumbmsg *pm;
	Mouse m;
	char *act;
	enum { MResize, MMouse, MPlumb, MWarnings, NMALT };
	static Alt alts[NMALT+1];

	USED(v);
	threadsetname("mousethread");
	alts[MResize].c = mousectl->resizec;
	alts[MResize].v = nil;
	alts[MResize].op = CHANRCV;
	alts[MMouse].c = mousectl->c;
	alts[MMouse].v = &mousectl->m;
	alts[MMouse].op = CHANRCV;
	alts[MPlumb].c = cplumb;
	alts[MPlumb].v = &pm;
	alts[MPlumb].op = CHANRCV;
	alts[MWarnings].c = cwarn;
	alts[MWarnings].v = nil;
	alts[MWarnings].op = CHANRCV;
	if(cplumb == nil)
		alts[MPlumb].op = CHANNOP;
	alts[NMALT].op = CHANEND;

	for(;;){
		qlock(&row.lk);
		flushwarnings();
		qunlock(&row.lk);
		flushimage(display, 1);
		switch(alt(alts)){
		case MResize:
			if(getwindow(display, Refnone) < 0)
				error("attach to window");
			draw(screen, screen->r, display->white, nil, ZP);
			iconinit();
			scrlresize();
			rowresize(&row, screen->clipr);
			break;
		case MPlumb:
			if(strcmp(pm->type, "text") == 0){
				act = plumblookup(pm->attr, "action");
				if(act==nil || strcmp(act, "showfile")==0)
					plumblook(pm);
				else if(strcmp(act, "showdata")==0)
					plumbshow(pm);
			}
			plumbfree(pm);
			break;
		case MWarnings:
			break;
		case MMouse:
			/*
			 * Make a copy so decisions are consistent; mousectl changes
			 * underfoot.  Can't just receive into m because this introduces
			 * another race; see /sys/src/libdraw/mouse.c.
			 */
			m = mousectl->m;
			qlock(&row.lk);
			t = rowwhich(&row, m.xy);
			if(t!=mousetext && mousetext!=nil && mousetext->w!=nil){
				winlock(mousetext->w, 'M');
				mousetext->eq0 = ~0;
				wincommit(mousetext->w, mousetext);
				winunlock(mousetext->w);
			}
			mousetext = t;
			if(t == nil)
				goto Continue;
			w = t->w;
			if(t==nil || m.buttons==0)
				goto Continue;
			but = 0;
			if(m.buttons == 1)
				but = 1;
			else if(m.buttons == 2)
				but = 2;
			else if(m.buttons == 4)
				but = 3;
			barttext = t;
			if(t->what==Body && ptinrect(m.xy, t->scrollr)){
				if(but){
					if(swapscrollbuttons){
						if(but == 1)
							but = 3;
						else if(but == 3)
							but = 1;
					}
					winlock(w, 'M');
					t->eq0 = ~0;
					textscroll(t, but);
					winunlock(w);
				}
				goto Continue;
			}
			/* scroll buttons, wheels, etc. */
			if(w != nil && (m.buttons & (8|16))){
				if(m.buttons & 8)
					but = Kscrolloneup;
				else
					but = Kscrollonedown;
				winlock(w, 'M');
				t->eq0 = ~0;
				texttype(t, but);
				winunlock(w);
				goto Continue;
			}
			if(ptinrect(m.xy, t->scrollr)){
				if(but){
					if(t->what == Columntag)
						rowdragcol(&row, t->col, but);
					else if(t->what == Tag){
						coldragwin(t->col, t->w, but);
						if(t->w)
							barttext = &t->w->body;
					}
					if(t->col)
						activecol = t->col;
				}
				goto Continue;
			}
			if(m.buttons){
				if(w)
					winlock(w, 'M');
				t->eq0 = ~0;
				if(w)
					wincommit(w, t);
				else
					textcommit(t, TRUE);
				if(m.buttons & 1){
					textselect(t);
					if(w)
						winsettag(w);
					argtext = t;
					seltext = t;
					if(t->col)
						activecol = t->col;	/* button 1 only */
					if(t->w!=nil && t==&t->w->body)
						activewin = t->w;
				}else if(m.buttons & 2){
					if(textselect2(t, &q0, &q1, &argt))
						execute(t, q0, q1, FALSE, argt);
				}else if(m.buttons & 4){
					if(textselect3(t, &q0, &q1))
						look3(t, q0, q1, FALSE);
				}
				if(w)
					winunlock(w);
				goto Continue;
			}
    Continue:
			qunlock(&row.lk);
			break;
		}
	}
}