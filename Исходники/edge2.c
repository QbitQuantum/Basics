static int
initialize (struct filter *f, struct initdata *i)
{
    inhermisc (f, i);
    /*in/out coloring modes looks better in iter modes. This also saves some
       memory in truecolor. */
    if (f->data != NULL)
        destroypalette ((struct palette *) f->data);
    f->data = createpalette (0, 65536, i->image->bytesperpixel <= 1 ? SMALLITER : LARGEITER, 0, 65536, NULL, NULL, NULL, NULL, NULL);
    if (!inherimage (f, i, TOUCHIMAGE | NEWIMAGE, 0, 0, (struct palette *) f->data, 0, 0))
        return 0;
    return (f->previous->action->initialize (f->previous, i));
}