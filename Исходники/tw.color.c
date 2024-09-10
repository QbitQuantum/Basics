/* parseLS_COLORS():
 *	Parse the LS_COLORS environment variable
 */
void
parseLS_COLORS(const Char *value)
{
    size_t  i, len;
    const Char	 *v;		/* pointer in value */
    char   *c;			/* pointer in colors */
    Extension *volatile e;	/* pointer in extensions */
    jmp_buf_t osetexit;
    size_t omark;

    (void) &e;

    /* init */
    xfree(extensions);
    for (i = 0; i < nvariables; i++)
	variables[i].color = variables[i].defaultcolor;
    colors = NULL;
    extensions = NULL;
    nextensions = 0;

    if (value == NULL)
	return;

    len = Strlen(value);
    /* allocate memory */
    i = 1;
    for (v = value; *v; v++)
	if ((*v & CHAR) == ':')
	    i++;
    extensions = xmalloc(len + i * sizeof(Extension));
    colors = i * sizeof(Extension) + (char *)extensions;
    nextensions = 0;

    /* init pointers */
    v = value;
    c = colors;
    e = &extensions[0];

    /* Prevent from crashing if unknown parameters are given. */

    omark = cleanup_push_mark();
    getexit(osetexit);

    if (setexit() == 0) {

    /* parse */
    while (*v) {
	switch (*v & CHAR) {
	case ':':
	    v++;
	    continue;

	case '*':		/* :*ext=color: */
	    v++;
	    if (getstring(&c, &v, &e->extension, '=') &&
		0 < e->extension.len) {
		v++;
		getstring(&c, &v, &e->color, ':');
		e++;
		continue;
	    }
	    break;

	default:		/* :vl=color: */
	    if (v[0] && v[1] && (v[2] & CHAR) == '=') {
		for (i = 0; i < nvariables; i++)
		    if ((Char)variables[i].variable[0] == (v[0] & CHAR) &&
			(Char)variables[i].variable[1] == (v[1] & CHAR))
			break;
		if (i < nvariables) {
		    v += 3;
		    getstring(&c, &v, &variables[i].color, ':');
		    continue;
		}
		else
		    stderror(ERR_BADCOLORVAR, v[0], v[1]);
	    }
	    break;
	}
	while (*v && (*v & CHAR) != ':')
	    v++;
    }
    }

    cleanup_pop_mark(omark);
    resexit(osetexit);

    nextensions = e - extensions;
}