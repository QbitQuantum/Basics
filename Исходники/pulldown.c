int pl_hitpulldown(Panel *g, Mouse *m){
	int oldstate, passon;
	Rectangle r;
	Panel *p, *hitme;
	Pulldown *pp;
	pp=g->data;
	oldstate=g->state;
	p=pp->pull;
	hitme=0;
	switch(g->state){
	case UP:
		if(!ptinrect(m->xy, g->r))
			g->state=UP;
		else if(m->buttons&7){
			r=g->b->r;
			p->flags&=~PLACE;
			switch(pp->side){
			case PACKN:
				r.min.x=g->r.min.x;
				r.max.y=g->r.min.y;
				p->flags|=PLACESW;
				break;
			case PACKS:
				r.min.x=g->r.min.x;
				r.min.y=g->r.max.y;
				p->flags|=PLACENW;
				break;
			case PACKE:
				r.min.x=g->r.max.x;
				r.min.y=g->r.min.y;
				p->flags|=PLACENW;
				break;
			case PACKW:
				r.max.x=g->r.min.x;
				r.min.y=g->r.min.y;
				p->flags|=PLACENE;
				break;
			case PACKCEN:
				r.min=g->r.min;
				p->flags|=PLACENW;
				break;
			}
			plpack(p, r);
			pp->save=allocimage(display, p->r, g->b->chan, 0, DNofill);
			if(pp->save!=0) draw(pp->save, p->r, g->b, 0, p->r.min);
			pl_invis(p, 0);
			pldraw(p, g->b);
			g->state=DOWN;
		}
		break;
	case DOWN:
		if(!ptinrect(m->xy, g->r)){
			switch(pp->side){
			default: SET(passon); break;		/* doesn't happen */
			case PACKN: passon=m->xy.y<g->r.min.y; break;
			case PACKS: passon=m->xy.y>=g->r.max.y; break;
			case PACKE: passon=m->xy.x>=g->r.max.x; break;
			case PACKW: passon=m->xy.x<g->r.min.x; break;
			case PACKCEN: passon=1; break;
			}
			if(passon){
				hitme=p;
				if((m->buttons&7)==0) g->state=UP;
			}
			else	g->state=UP;
		}
		else if((m->buttons&7)==0) g->state=UP;
		else hitme=p;
		if(g->state!=DOWN && pp->save){
			draw(g->b, p->r, pp->save, 0, p->r.min);
			freeimage(pp->save);
			pp->save=0;
			pl_invis(p, 1);
			hitme=p;
		}
	}
	if(g->state!=oldstate) pldraw(g, g->b);
	if(hitme) plmouse(hitme, m);
	return g->state==DOWN;
}