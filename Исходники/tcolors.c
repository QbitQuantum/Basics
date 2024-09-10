void
mousethread(void *v)
{
	Point p;
	Mouse m;
	int i, n, prev;
	char buf[100];
	ulong rgb;

	prev = -1;
	while(readmouse(mousectl) >= 0){
		m = mousectl->m;
		switch(m.buttons){
		case 1:
			while(m.buttons){
				if(screen->depth > 8)
					n = 256;
				else
					n = 1<<screen->depth;
				for(i=0; i!=n; i++)
					if(i!=prev && ptinrect(m.xy, crect[i])){
						if(ramp)
							rgb = grey(i);
						else
							rgb = cmap2rgb(i);
						sprint(buf, fmt,
							i,
							(rgb>>16)&0xFF,
							(rgb>>8)&0xFF,
							rgb&0xFF,
							(rgb<<8) | 0xFF);
						p = addpt(screen->r.min, Pt(2,2));
						draw(screen, Rpt(p, addpt(p, stringsize(font, buf))), display->white, nil, p);
						string(screen, p, display->black, ZP, font, buf);
						prev=i;
						break;
					}
				readmouse(mousectl);
				m = mousectl->m;
			}
			break;

		case 4:
			switch(menuhit(3, mousectl, &menu, nil)){
			case 0:
				threadexitsall(0);
			}
		}
	}
}