int fwide(FILE *f, int mode)
{
    if (!f->mode) f->mode = NORMALIZE(mode);
    return f->mode;
}