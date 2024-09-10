/*
 * Read list of areas from VARDIR/AREAS file.
 *
 * Format:
 *     AREA    NEWSGROUP    [-options]
 *
 * Options:
 *     -a Z:N/F.P       use alternate address for this area
 *     -z ZONE          use AKA for zone Z for this area
 *     -o ORIGIN        use alternate origin line for this area
 *     -d DISTRIBUTION  use Distribution: DISTRIBUTION for this newsgroup
 *     -l               only local xpostings allowed
 *     -x               no xpostings allowed
 *     -g               no messages from other gates FTN->Usenet
 *     -8               use ISO 8-bit umlauts
 *     -H               AREA/NEWSGROUP match entire hierarchy, names are
 *                      translated automatically
 *     -R LVL           ^ARFC header level
 *     -m MAXSIZE       set MaxMsgSize for this area (0 = infinity)
 *     -L LIMITSIZE     set LimitMsgSize for this area (0 = infinity)
 *     -X "Xtra: xyz"	add extra RFC header (multiple -X are allowed)
 *     -8               convert to 8bit iso-8859-1 characters
 *     -Q               convert to quoted-printable iso-8859-1 characters
 *     -C def:in:out    charset mapping setting
 */
Area *areas_parse_line(char *buf)
{
    Area *p;
    char *a, *g, *o;
	
    a = xstrtok(buf,  " \t");	/* FTN area */
    g = xstrtok(NULL, " \t");	/* Newsgroup */
    if(a==NULL || g==NULL)
	return NULL;

    /* Check for include command */
    if(strieq(a, "include"))
    {
	areas_do_file(g);
	return NULL;
    }
    
    /* Create new areas entry */
    p = (Area *)xmalloc(sizeof(Area));
    p->next         = NULL;
    p->area         = strsave(a);
    p->group        = strsave(g);
    p->zone         = cf_defzone();
    node_invalid(&p->addr);
    p->origin       = NULL;
    p->distribution = NULL;
    p->flags        = 0;
    p->rfc_lvl      = -1;
    p->maxsize      = -1;
    p->limitsize    = -1;
    tl_init(&p->x_hdr);
    p->charset      = NULL;

    /* Options */
    for(o=xstrtok(NULL, " \t");
	o;
	o=xstrtok(NULL, " \t")  )
    {
	if(!strcmp(o, "-a"))
	    /* -a Z:N/F.P */
	    if((o = xstrtok(NULL, " \t")))
		asc_to_node(o, &p->addr, FALSE);
	if(!strcmp(o, "-z"))
	    /* -z ZONE */
	    if((o = xstrtok(NULL, " \t")))
		p->zone = atoi(o);
	if(!strcmp(o, "-o"))
	    /* -o ORIGIN */
	    if((o = xstrtok(NULL, " \t")))
		p->origin = strsave(o);
	if(!strcmp(o, "-d"))
	    /* -d DISTRIBUTION */
	    if((o = xstrtok(NULL, " \t")))
		p->distribution = strsave(o);
	if(!strcmp(o, "-l"))
	    p->flags |= AREA_LOCALXPOST;
	if(!strcmp(o, "-x"))
	    p->flags |= AREA_NOXPOST;
	if(!strcmp(o, "-g"))
	    p->flags |= AREA_NOGATE;
	if(!strcmp(o, "-H"))
	    p->flags |= AREA_HIERARCHY;
	if(!strcmp(o, "-!"))
	    p->flags |= AREA_NO;
	if(!strcmp(o, "-R"))
	    /* -R lvl */
	    if((o = xstrtok(NULL, " \t")))
		p->rfc_lvl = atoi(o);
	if(!strcmp(o, "-m"))
	    /* -m MAXMSGSIZE */
	    if((o = xstrtok(NULL, " \t")))
		p->maxsize = atol(o);
	if(!strcmp(o, "-L"))
	    /* -L LIMITMSGSIZE */
	    if((o = xstrtok(NULL, " \t")))
		p->limitsize = atol(o);
	if(!strcmp(o, "-X"))
	    /* -X "Xtra: xyz" */
	    if((o = xstrtok(NULL, " \t")))
		tl_append(&p->x_hdr, o);
	if(!strcmp(o, "-8"))
	    p->flags |= AREA_8BIT;
	if(!strcmp(o, "-Q"))
	    p->flags |= AREA_QP;
	if(!strcmp(o, "-C"))
	    /* -C DEF:IN:OUT */
	    if((o = xstrtok(NULL, " \t")))
		p->charset = strsave(o);
    }
    /* Value not set or error */
    if(p->maxsize   < 0)
	p->maxsize   = areas_def_maxsize;
    if(p->limitsize < 0)
	p->limitsize = areas_def_limitsize;
	
    debug(15, "areas: %s %s Z=%d A=%s R=%d S=%ld",
	  p->area, p->group, p->zone,
	  p->addr.zone!=-1 ? znfp1(&p->addr) : "",
	  p->rfc_lvl, p->maxsize                               );

    return p;
}