static void
resize(Vnc *v, int first)
{
    int fd;
    Point d;

    d = addpt(v->dim, Pt(2*Borderwidth, 2*Borderwidth));
    lockdisplay(display);

    if(getwindow(display, Refnone) < 0)
        sysfatal("internal error: can't get the window image");

    /*
     * limit the window to at most the vnc server's size
     */
    if(first || d.x < Dx(screen->r) || d.y < Dy(screen->r)) {
        fd = open("/dev/wctl", OWRITE);
        if(fd >= 0) {
            fprint(fd, "resize -dx %d -dy %d", d.x, d.y);
            close(fd);
        }
    }
    unlockdisplay(display);
}