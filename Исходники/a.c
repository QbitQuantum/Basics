ripple()
{
	register Point p1, p2;
	register Point inc;
	register Point p;

	while (kbdchar() != 'q') {
		if (P->state & MOVED) {
			P->state &= ~(MOVED|RESHAPED);
			p = sub (Drect.origin, p);
			p1 = add (p1, p);
			p2 = add (p2, p);
			p = Drect.origin;
		}
		else if (P->state & RESHAPED) {
			P->state &= ~RESHAPED;
			p1.x=p2.x=avg(Drect.origin.x, Drect.corner.x);
			p1.y=p2.y=avg(Drect.origin.y, Drect.corner.y);
			inc.x=1;
			inc.y=1;
			rectf(&display, Drect, F_XOR);
			p = Drect.origin;
		}
		rectf(&display, canon(p1, p2), F_XOR);
		if (p1.x==Drect.origin.x || p1.x==Drect.corner.x) {
			inc.x= -inc.x;
		}
		if (p1.y==Drect.origin.y || p1.y==Drect.corner.y) {
			inc.y= -inc.y;
		}
		p1 = sub (p1, inc);
		p2 = add (p2, inc);
		wait (CPU);
	}
}