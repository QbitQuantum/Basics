static int
rmb(void)
{
	static Menu menu = {nil, menugen};
	int n;
	Win *w;
	File *f;

	if(actw != nil && actw->tab->rmb != nil && actw->tab->rmb(actw, mc) >= 0)
		return 0;
	n = menuhit(3, mc, &menu, nil);
	if(n < 0)
		return 0;
	switch(n){
	case ZEROX:
		w = winsel(mc, 3);
		if(w != nil)
			winzerox(w, mc);
		return 0;
	case CLOSE:
		w = winsel(mc, 3);
		if(w != nil)
			winclose(w);
		return 0;
	case RESIZE:
		winresize(winsel(mc, 3), mc);
		return 0;
	case WRITE:
		w = winsel(mc, 3);
		if(w != nil)
			winwrite(w, nil);
		return 0;
	case QUIT:
		return quit();
	}
	if(n < WIN)
		sysfatal("rmb: no action for n=%d", n);
	if(n == 0){
		setfocus(cmdw);
		return 0;
	}
	n -= WIN;
	for(f = flist.next; f != &flist; f = f->next)
		if(--n == 0){
			if(f->wins.wnext == &f->wins){
				newwinsel(f->type, mc, f);
				return 0;
			}
			for(w = f->wins.wnext; w != &f->wins && w != actw; w = w->wnext)
				;
			if(w->wnext == &f->wins)
				w = w->wnext;
			setfocus(w->wnext);
			return 0;
		}
	return 0;
}