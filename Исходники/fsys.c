unichar_t *u_GFileGetAbsoluteName(unichar_t *name, unichar_t *result, int rsiz) {
    /* result may be the same as name */
    unichar_t buffer[1000];

    if ( ! u_GFileIsAbsolute(name) ) {
	unichar_t *pt, *spt, *rpt, *bpt;

	if ( dirname_[0]=='\0' ) {
	    getcwd(dirname_,sizeof(dirname_));
	}
	uc_strcpy(buffer,dirname_);
	if ( buffer[u_strlen(buffer)-1]!='/' )
	    uc_strcat(buffer,"/");
	u_strcat(buffer,name);
	_u_backslash_to_slash(buffer);

	/* Normalize out any .. */
	spt = rpt = buffer;
	while ( *spt!='\0' ) {
	    if ( *spt=='/' ) ++spt;
	    for ( pt = spt; *pt!='\0' && *pt!='/'; ++pt );
	    if ( pt==spt )	/* Found // in a path spec, reduce to / (we've*/
		u_strcpy(spt,pt); /*  skipped past the :// of the machine name) */
	    else if ( pt==spt+1 && spt[0]=='.' && *pt=='/' )	/* Noop */
		u_strcpy(spt,spt+2);
	    else if ( pt==spt+2 && spt[0]=='.' && spt[1]=='.' ) {
		for ( bpt=spt-2 ; bpt>rpt && *bpt!='/'; --bpt );
		if ( bpt>=rpt && *bpt=='/' ) {
		    u_strcpy(bpt,pt);
		    spt = bpt;
		} else {
		    rpt = pt;
		    spt = pt;
		}
	    } else
		spt = pt;
	}
	name = buffer;
    }
    if (result!=name) {
	u_strncpy(result,name,rsiz);
	result[rsiz-1]='\0';
	_u_backslash_to_slash(result);
    }
return(result);
}