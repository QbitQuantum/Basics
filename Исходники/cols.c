Text*
colwhich(Column *c, Point p)
{
	int i;
	Window *w;

	if(!ptinrect(p, c->r))
		return nil;
	if(ptinrect(p, c->tag.all))
		return &c->tag;
	for(i=0; i<c->nw; i++){
		w = c->w[i];
		if(ptinrect(p, w->r)){
			if(ptinrect(p, w->tag.all))
				return &w->tag;
			return &w->body;
		}
		/* scrollr drops below w->r on low windows */
		if(ptinrect(p, w->body.scrollr))
			return &w->body;
	}
	return nil;
}