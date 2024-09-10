void CGame::draw(SDL_Surface *sfc,SDL_Rect logic_vp,CCarObject *focusing,float *fy,int *cp_delay)
{
	List<CObject> l;
	CObject *o;
	int sx,sy;
	float f=0.0;
	SDL_Rect vp=logic_vp;

	{
		f=float(-focusing->get_y_speed())/MAX_SPEED;
		f=0.66F + (0.85F-0.66F)*f;
		*fy=(2*(*fy)+f)/3;
	}

	sx=focusing->get_x()-vp.w/2;
	sy=int(focusing->get_y()-vp.h*(*fy));
	if (sx+vp.w>dx) sx=dx-vp.w;
	if (sy+vp.h>dy) sy=dy-vp.h;
	if (sx<0) sx=0;
	if (sy<0) sy=0;
	if (vp.w>dx) {
		vp.x=logic_vp.x+vp.w-dx;
		vp.w=dx;
	} /* if */ 
	sx-=vp.x;
	sy-=vp.y;
	SDL_SetClipRect(sfc,&vp);

	if (game_remake_extras && current_level==3) {
		/* 128-96 */ 
		/* Water animation for level 3: */ 
		List<CTile> l;
		CTile *t;

		l.Instance(tiles[3]);
		l.Rewind();
		while(l.Iterate(t)) {
			if (t->r.x==0 && t->r.y==0 && t->r.w==128 && t->r.h==96) {
				SDL_Surface *tmp=SDL_CreateRGBSurface(0,128,96,32,0,0,0,0);
				SDL_Rect r1,r2;
				r1.x=0;
				r1.y=0;
				r1.w=128;
				r1.h=96;
				r2.x=0;
				r2.y=0;
				r2.w=128;
				r2.h=96;
				SDL_BlitSurface(t->orig,&r1,tmp,&r2);
				r1.x=1;
				r1.w=127;
				SDL_BlitSurface(tmp,&r1,t->orig,&r2);
				r1.x=0;
				r1.w=1;
				r2.x=127;
				SDL_BlitSurface(tmp,&r1,t->orig,&r2);
				SDL_FreeSurface(tmp);
			} /* if */ 
		} /* if */ 
	} /* if */ 
	
	{
		int i;
		int min=0,max=0;

		get_quick_min_max(sy+vp.y,sy+vp.y+vp.h,&min,&max);

		for(i=min;i<=max;i++) {
			l.Instance(quick_background[i]);
			l.Rewind();
			while(l.Iterate(o)) o->draw(sx,sy,sfc);
		} /* for */ 

		for(i=min;i<=max;i++) {
			l.Instance(quick_middleground[i]);
			l.Rewind();
			while(l.Iterate(o)) o->draw(sx,sy,sfc);
		} /* for */ 


		/* TYRE MARKS: */ 
		if (game_remake_extras) {
			List<CTyreMark> l;
			CTyreMark *r;

			l.Instance(tyre_marks);
			l.Rewind();
			while(l.Iterate(r)) {
				draw_line(sfc,r->x-sx,r->y-sy,r->x2-sx,r->y2-sy,0);
				draw_line(sfc,r->x+1-sx,r->y-sy,r->x2+1-sx,r->y2-sy,0);
			} /* if */ 
		} /* if */ 

		l.Instance(objects);
		l.Rewind();
		while(l.Iterate(o)) o->draw(sx,sy,sfc);


		for(i=min;i<=max;i++) {
			l.Instance(quick_foreground[i]);
			l.Rewind();
			while(l.Iterate(o)) o->draw(sx,sy,sfc);
		} /* for */ 
	}

	/* Draw overlays: */ 
	if (focusing->get_y()<384) {
		(*cp_delay)++;
		((CPlayerCarObject *)focusing)->reach_goal();
	} /* if */ 

	if ((*cp_delay)>=0) {
		int i;
		int x1,x2;
		CTile *tile=0;

		if (current_level==6) tile=extra_tiles[11];
						 else tile=extra_tiles[10];

		if (vp.w>=tile->get_dx()) {
			int amp;
			int offs;

			amp=*cp_delay;
			if (amp<0) amp=0;
			if (amp>128) amp=128;
			amp=int((128-amp)*(128-amp)/128);
			if (amp<0) amp=0;

			offs=int(cos(float((*cp_delay)*(*cp_delay))/500.0)*amp);
			if (offs<0) offs=-offs;

			tile->draw(vp.x+(vp.w/2)-(tile->get_dx()/2),vp.y+64-offs,sfc);
		} else {
			x1=-tile->get_dx();
			x2=(vp.w-tile->get_dx())/2;
			i=*cp_delay;

			tile->draw(vp.x+x1+((x2-x1)/32)*i,vp.y+32,sfc);
		} /* if */ 

	} /* if */ 



	SDL_SetClipRect(sfc,0);

} /* CGame::draw */ 