int
form_init(FILE *fp)
{
    char var[256];
    char val[10000];
    char *cp, *vp;
    int c;
    
    char *ep = getenv("QUERY_STRING");
    char *rm = getenv("REQUEST_METHOD");

    nvar = 0;

    if (ep && *ep && (rm && strcmp(rm, "POST") != 0))
    {
	cp = strtok(ep, "&");
	while (cp)
	{
	    vp = strchr(cp, '=');
	    if (vp)
	    {
		*vp++ = '\0';
		http_strip(vp);
	    }
	    
	    http_strip(cp);
	    form_add(cp, vp);
	    
	    cp = strtok(NULL, "&");
	}
    }
    else if (fp != NULL)
    {
	while (fscanf(fp, "%255[^=]=", var) == 1)
	{
	    val[0] = '\0';
	    
	    http_strip(var);
	    
	    c = getc(fp);
	    if (c == EOF)
	    {
		form_add(var, "");
		break;
	    }
	    
	    ungetc(c, fp);
	    if (c != '&' && fscanf(fp, "%9999[^&\n\r]", val) == 1)
	    {
		http_strip(val);
		form_add(var, val);
	    }
	    else
		form_add(var, "");
	    
	    c = getc(fp);
	    if (c != '&')
		ungetc(c, fp);
	}
    }
    
    return nvar;
}