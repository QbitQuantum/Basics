void
main(int argc, char *argv[])
{
	Mouse m;
	int i, j;
	unsigned short ran, score, attempt, prev, br[2];
	Image *c[2];
	char *fmt;

	level = 16;
	fmt = "win in %d attempts!";

	ARGBEGIN{
	default:
		goto Usage;
	case 'h':
		level=36;
		break;
	}ARGEND

	if(argc){
    Usage:
		fprint(2, "usage: %s [-h]\n", argv0);
		exits("usage");
	}
	if(initdraw(0,0,"memo") < 0)
		sysfatal("initdraw failed: %r");
	srand(time(0));
	memoinit();
	einit(Emouse);

    Start:
	afaces();
	winflag=0;
	prev=level+1;
	score=attempt=0;
	for(i=0;i!=level;i++)
		block[i].flag = Eninit;

	for(i=0;i!=level/2;i++){
		for(j=0;j!=2;){
			ran = rand()%level;
			if(block[ran].flag == Eninit){
				block[ran].face = face[i];
				block[ran].flag = Eshow;
				j++;
			}
		}
	}
	eresized(0);
	for(;;m=emouse())
		if(m.buttons)
			break;

	for(i=0;i!=level;i++)
		block[i].flag = Ehide;

	redraw();
	j = 0;
	for(;; m=emouse()){
		switch(m.buttons){
		case 1:
			while(m.buttons){
				for(i=0;i!=level;i++){
					if(i!=prev && ptinrect(m.xy,block[i].r)){
						if(block[i].flag==Ehide  && j<2){
							block[i].flag = Eshow;
							draw(screen, block[i].r, block[i].face, nil, ZP);
							c[j] = block[i].face;
							br[j] = prev = i;
							j++;
						}
						break;
					}
				}
				m=emouse();
			}
			break;
		case 4:
			switch(emenuhit(3, &m, &menu)) {
			case 0:	/* restart */
				goto Start;
				break;
			case 1:
				level=16;
				goto Start;
				break;
			case 2:
				level=36;
				goto Start;
				break;
			case 3:
				exits(0);
				break;
			}
		}
		if(j==2){
			attempt++;
			prev = level+1;
			j = 0;
			if(c[0] == c[1]){
				score++;
				block[br[0]].flag = Edisc;
				block[br[1]].flag = Edisc;
			} else{
				block[br[0]].flag = Ehide;
				block[br[1]].flag = Ehide;
			}
			redraw();
			continue;
		}
		if(score == level/2){
			winflag = 1;
			sprint(buf, fmt, attempt);
			redraw();
			for(;;m=emouse())
				if(m.buttons&1 || m.buttons&4)
					break;
			goto Start;
		}
	}
}