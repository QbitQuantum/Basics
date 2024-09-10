rpmwf rpmwfNew(const char * fn)
{
    struct stat sb, *st = &sb;
    rpmwf wf;
    int xx;

/*@-globs@*/
    if ((xx = Stat(fn, st)) < 0)
	return NULL;
/*@=globs@*/
    wf = rpmwfGetPool(_rpmwfPool);
    wf->fn = xstrdup(fn);
    wf->nb = (size_t)st->st_size;

    return rpmwfLink(wf, "rpmwfNew");
}