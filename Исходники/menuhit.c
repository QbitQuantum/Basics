int
menuhit(int but, Mousectl *mc, Menu *menu, Screen *scr)
{
	int i, nitem, nitemdrawn, maxwid, lasti, off, noff, wid, screenitem;
	int scrolling;
	Rectangle r, menur, sc, textr, scrollr;
	Image *b, *save, *backup;
	Point pt;
	char *item;

	if(back == nil)
		menucolors();
	sc = screen->clipr;
	replclipr(screen, 0, screen->r);
	maxwid = 0;
	for(nitem = 0;
	    item = menu->item? menu->item[nitem] : (*menu->gen)(nitem);
	    nitem++){
		i = stringwidth(font, item);
		if(i > maxwid)
			maxwid = i;
	}
	if(menu->lasthit<0 || menu->lasthit>=nitem)
		menu->lasthit = 0;
	screenitem = (Dy(screen->r)-10)/(font->height+Vspacing);
	if(nitem>Maxunscroll || nitem>screenitem){
		scrolling = 1;
		nitemdrawn = Nscroll;
		if(nitemdrawn > screenitem)
			nitemdrawn = screenitem;
		wid = maxwid + Gap + Scrollwid;
		off = menu->lasthit - nitemdrawn/2;
		if(off < 0)
			off = 0;
		if(off > nitem-nitemdrawn)
			off = nitem-nitemdrawn;
		lasti = menu->lasthit-off;
	}else{
		scrolling = 0;
		nitemdrawn = nitem;
		wid = maxwid;
		off = 0;
		lasti = menu->lasthit;
	}
	r = insetrect(Rect(0, 0, wid, nitemdrawn*(font->height+Vspacing)), -Margin);
	r = rectsubpt(r, Pt(wid/2, lasti*(font->height+Vspacing)+font->height/2));
	r = rectaddpt(r, mc->m.xy);
	pt = ZP;
	if(r.max.x>screen->r.max.x)
		pt.x = screen->r.max.x-r.max.x;
	if(r.max.y>screen->r.max.y)
		pt.y = screen->r.max.y-r.max.y;
	if(r.min.x<screen->r.min.x)
		pt.x = screen->r.min.x-r.min.x;
	if(r.min.y<screen->r.min.y)
		pt.y = screen->r.min.y-r.min.y;
	menur = rectaddpt(r, pt);
	textr.max.x = menur.max.x-Margin;
	textr.min.x = textr.max.x-maxwid;
	textr.min.y = menur.min.y+Margin;
	textr.max.y = textr.min.y + nitemdrawn*(font->height+Vspacing);
	if(scrolling){
		scrollr = insetrect(menur, Border);
		scrollr.max.x = scrollr.min.x+Scrollwid;
	}else
		scrollr = Rect(0, 0, 0, 0);

	if(scr){
		b = allocwindow(scr, menur, Refbackup, DWhite);
		if(b == nil)
			b = screen;
		backup = nil;
	}else{
		b = screen;
		backup = allocimage(display, menur, screen->chan, 0, -1);
		if(backup)
			draw(backup, menur, screen, nil, menur.min);
	}
	draw(b, menur, back, nil, ZP);
	border(b, menur, Blackborder, bord, ZP);
	save = allocimage(display, menurect(textr, 0), screen->chan, 0, -1);
	r = menurect(textr, lasti);
	moveto(mc, divpt(addpt(r.min, r.max), 2));
	menupaint(b, menu, textr, off, nitemdrawn);
	if(scrolling)
		menuscrollpaint(b, scrollr, off, nitem, nitemdrawn);
	while(mc->m.buttons & (1<<(but-1))){
		lasti = menuscan(b, menu, but, mc, textr, off, lasti, save);
		if(lasti >= 0)
			break;
		while(!ptinrect(mc->m.xy, textr) && (mc->m.buttons & (1<<(but-1)))){
			if(scrolling && ptinrect(mc->m.xy, scrollr)){
				noff = ((mc->m.xy.y-scrollr.min.y)*nitem)/Dy(scrollr);
				noff -= nitemdrawn/2;
				if(noff < 0)
					noff = 0;
				if(noff > nitem-nitemdrawn)
					noff = nitem-nitemdrawn;
				if(noff != off){
					off = noff;
					menupaint(b, menu, textr, off, nitemdrawn);
					menuscrollpaint(b, scrollr, off, nitem, nitemdrawn);
				}
			}
			readmouse(mc);
		}
	}
	if(b != screen)
		freeimage(b);
	if(backup){
		draw(screen, menur, backup, nil, menur.min);
		freeimage(backup);
	}
	freeimage(save);
	replclipr(screen, 0, sc);
	flushimage(display, 1);
	if(lasti >= 0){
		menu->lasthit = lasti+off;
		return menu->lasthit;
	}
	return -1;
}