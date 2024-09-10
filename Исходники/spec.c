int addSource(Spec spec, /*@unused@*/ Package pkg,
		const char *field, rpmTag tag)
{
    struct Source *p;
#if defined(RPM_VENDOR_OPENPKG) /* regular-ordered-sources */
    struct Source *p_last;
#endif
    int flag = 0;
    const char *name = NULL;
    const char *mdir = NULL;
    const char *fieldp = NULL;
    char buf[BUFSIZ];
    uint32_t num = 0;

    buf[0] = '\0';
    switch (tag) {
    case RPMTAG_SOURCE:
	flag = RPMFILE_SOURCE;
	name = "source";
	fieldp = spec->line + strlen(name);
	break;
    case RPMTAG_PATCH:
	flag = RPMFILE_PATCH;
	name = "patch";
	fieldp = spec->line + strlen(name);
	break;
    case RPMTAG_ICON:
	flag = RPMFILE_ICON;
	name = "icon";
	fieldp = NULL;
	break;
    default:
assert(0);
	/*@notreached@*/ break;
    }
#if !defined(RPM_VENDOR_OPENPKG) /* splitted-source-directory */
    mdir = getSourceDir(flag);
assert(mdir != NULL);
#endif

    /* Get the number */
    if (fieldp != NULL) {
	char * end = NULL;

	num = strtoul(fieldp, &end, 10);
	SKIPSPACE(end);
	if (*end != ':') {
	    rpmlog(RPMLOG_ERR, _("line %d: No ':' terminator: %s\n"),
			 spec->lineNum, spec->line);
	    return RPMRC_FAIL;
	}
    }

    /* Check whether tags of the same number haven't already been defined */
    for (p = spec->sources; p != NULL; p = p->next) {
	if ( p->num != num ) continue;
	if ((tag == RPMTAG_SOURCE && p->flags == RPMFILE_SOURCE) ||
	    (tag == RPMTAG_PATCH  && p->flags == RPMFILE_PATCH)) {
		rpmlog(RPMLOG_ERR, _("%s %d defined multiple times\n"), name, num);
		return RPMRC_FAIL;
	    }
    }

    /* Create the entry and link it in */
    p = xmalloc(sizeof(*p));
    p->num = num;
    p->fullSource = xstrdup(field);
    p->flags = flag;
    p->source = strrchr(p->fullSource, '/');
    if (p->source)
	p->source++;
    else
	p->source = p->fullSource;

#if defined(RPM_VENDOR_OPENPKG) /* regular-ordered-sources */
    p->next = NULL;
    p_last = spec->sources;
    while (p_last != NULL && p_last->next != NULL)
        p_last = p_last->next;
    if (p_last != NULL)
        p_last->next = p;
    else
        spec->sources = p;
#else
    p->next = spec->sources;
    spec->sources = p;
#endif

    spec->numSources++;

    /* XXX FIXME: need to add ICON* macros. */
#if defined(RPM_VENDOR_OPENPKG) /* splitted-source-directory */
    mdir = getSourceDir(flag, p->source);
#endif
    if (tag != RPMTAG_ICON) {
	const char *body = rpmGenPath(NULL, mdir, p->source);

	sprintf(buf, "%s%d",
		(flag & RPMFILE_PATCH) ? "PATCH" : "SOURCE", num);
	addMacro(spec->macros, buf, NULL, body, RMIL_SPEC);
	sprintf(buf, "%sURL%d",
		(flag & RPMFILE_PATCH) ? "PATCH" : "SOURCE", num);
	addMacro(spec->macros, buf, NULL, p->fullSource, RMIL_SPEC);
#ifdef WITH_LUA
	if (!spec->recursing) {
	    rpmlua lua = NULL; /* global state */
	    const char * what = (flag & RPMFILE_PATCH) ? "patches" : "sources";
	    rpmluav var = rpmluavNew();

	    rpmluaPushTable(lua, what);
	    rpmluavSetListMode(var, 1);
	    rpmluavSetValue(var, RPMLUAV_STRING, body);
	    rpmluaSetVar(lua, var);
/*@-moduncon@*/
	    var = (rpmluav) rpmluavFree(var);
/*@=moduncon@*/
	    rpmluaPop(lua);
	}
#endif
	body = _free(body);
    }
    
    return RPMRC_OK;
}