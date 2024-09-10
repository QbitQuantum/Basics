/* called from graphics library */
void
eresized(int callgetwin)
{
	needresize = callgetwin + 1;

	/* new window? */
	/* was using Refmesg */
	if (needresize > 1 && getwindow(display, Refnone) < 0)
		sysfatal("can't reattach to window: %r");

	/* destroyed window? */
	if (Dx(screen->r) == 0 || Dy(screen->r) == 0)
		exits("window gone");

	reshape();
}