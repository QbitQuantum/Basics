static struct filter *
getinstance (const struct filteraction *a)
{
    struct filter *f = createfilter (a);
    struct stereogramdata *i = (struct stereogramdata *) calloc (1, sizeof (*i));
    i->minc = 0;
    i->savedpalette = NULL;
    i->palette = createpalette (0, 65536, IMAGETYPE, 0, 65536, NULL, NULL, NULL, NULL, NULL);
    f->data = i;
    f->name = "Random dot stereogram";
    return (f);
}