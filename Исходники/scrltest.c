void done(Panel *p, int buttons){
	USED(p, buttons);
	bitblt(&screen, screen.r.min, &screen, screen.r, Zero);
	exits(0);
}