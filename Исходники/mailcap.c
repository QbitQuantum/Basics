static struct mailcap *
loadMailcap(char *filename)
{
    FILE *f;
    int i, n;
    Str tmp;
    struct mailcap *mcap;

    f = fopen(expandPath(filename), "r");
    if (f == NULL)
	return NULL;
    i = 0;
    while (tmp = Strfgets(f), tmp->length > 0) {
	if (tmp->ptr[0] != '#')
	    i++;
    }
    fseek(f, 0, 0);
    n = i;
    mcap = New_N(struct mailcap, n + 1);
    i = 0;
    while (tmp = Strfgets(f), tmp->length > 0) {
	if (tmp->ptr[0] == '#')
	    continue;
      redo:
	while (IS_SPACE(Strlastchar(tmp)))
	    Strshrink(tmp, 1);
	if (Strlastchar(tmp) == '\\') {
	    /* continuation */
	    Strshrink(tmp, 1);
	    Strcat(tmp, Strfgets(f));
	    goto redo;
	}
	if (extractMailcapEntry(tmp->ptr, &mcap[i]))
	    i++;
    }
    memset(&mcap[i], 0, sizeof(struct mailcap));
    fclose(f);
    return mcap;
}