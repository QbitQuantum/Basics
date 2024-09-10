static int
do_entry2text(
	LDAP			*ld,
	char			*buf,		/* NULL for use-internal */
	char			*base,		/* used for search actions */
	LDAPMessage		*entry,
	struct ldap_disptmpl	*tmpl,
	char			**defattrs,
	char			***defvals,
	writeptype		writeproc,
	void			*writeparm,
	char			*eol,
	int			rdncount,
	unsigned int		opts,
	char			*urlprefix	/* if non-NULL, do HTML */
)
{
    int				i, err, html, show, labelwidth;
    int				freebuf,  freevals;
    char			*dn, **vals;
    struct ldap_tmplitem	*rowp, *colp;

    if (( dn = ldap_get_dn( ld, entry )) == NULL ) {
	return( ld->ld_errno );
    }

    if ( buf == NULL ) {
	if (( buf = malloc( LDAP_DTMPL_BUFSIZ )) == NULL ) {
	    ld->ld_errno = LDAP_NO_MEMORY;
	    free( dn );
	    return( ld->ld_errno );
	}
	freebuf = 1;
    } else {
	freebuf = 0;
    }

    html = ( urlprefix != NULL );

    if ( html ) {
	/*
	 * add HTML intro. and title
	 */
	if (!(( opts & LDAP_DISP_OPT_HTMLBODYONLY ) != 0 )) {
	    sprintf( buf, "<HTML>%s<HEAD>%s<TITLE>%s%s - ", eol, eol, eol,
		    ( tmpl == NULL ) ? "Entry" : tmpl->dt_name );
	    (*writeproc)( writeparm, buf, strlen( buf ));
	    output_dn( buf, dn, 0, rdncount, writeproc, writeparm, "", NULL );
	    sprintf( buf, "%s</TITLE>%s</HEAD>%s<BODY>%s<H3>%s - ", eol, eol,
		    eol, eol, ( tmpl == NULL ) ? "Entry" : tmpl->dt_name );
	    (*writeproc)( writeparm, buf, strlen( buf ));
	    output_dn( buf, dn, 0, rdncount, writeproc, writeparm, "", NULL );
	    sprintf( buf, "</H3>%s", eol );
	    (*writeproc)( writeparm, buf, strlen( buf ));
	}

	if (( opts & LDAP_DISP_OPT_NONLEAF ) != 0 &&
		( vals = ldap_explode_dn( dn, 0 )) != NULL ) {
	    char	*untagged;

	    /*
	     * add "Move Up" link
	     */
	    sprintf( buf, "<A HREF=\"%s", urlprefix );
	    for ( i = 1; vals[ i ] != NULL; ++i ) {
		if ( i > 1 ) {
		     strcat_escaped( buf, ", " );
		}
		strcat_escaped( buf, vals[ i ] );
	    }
	    if ( vals[ 1 ] != NULL ) {
		untagged = strchr( vals[ 1 ], '=' );
	    } else {
		untagged = "=The World";
	    }
	    sprintf( buf + strlen( buf ),
		    "%s\">Move Up To <EM>%s</EM></A>%s<BR>",
		    ( vals[ 1 ] == NULL ) ? "??one" : "",
		    ( untagged != NULL ) ? untagged + 1 : vals[ 1 ], eol, eol );
	    (*writeproc)( writeparm, buf, strlen( buf ));

	    /*
	     * add "Browse" link
	     */
	    untagged = strchr( vals[ 0 ], '=' );
	    sprintf( buf, "<A HREF=\"%s", urlprefix );
	    strcat_escaped( buf, dn );
	    sprintf( buf + strlen( buf ), "??one?(!(objectClass=dsa))\">Browse Below <EM>%s</EM></A>%s%s",
		    ( untagged != NULL ) ? untagged + 1 : vals[ 0 ], eol, eol );
	    (*writeproc)( writeparm, buf, strlen( buf ));

	    ldap_value_free( vals );
	}

	(*writeproc)( writeparm, "<HR>", 4 );	/* horizontal rule */
    } else {
	(*writeproc)( writeparm, "\"", 1 );
	output_dn( buf, dn, 0, rdncount, writeproc, writeparm, "", NULL );
	sprintf( buf, "\"%s", eol );
	(*writeproc)( writeparm, buf, strlen( buf ));
    }

    if ( tmpl != NULL && ( opts & LDAP_DISP_OPT_AUTOLABELWIDTH ) != 0 ) {
	labelwidth = max_label_len( tmpl ) + 3;
    } else {
	labelwidth = DEF_LABEL_WIDTH;;
    }

    err = LDAP_SUCCESS;

    if ( tmpl == NULL ) {
	BerElement	*ber;
	char		*attr;

	ber = NULL;
	for ( attr = ldap_first_attribute( ld, entry, &ber );
		NONFATAL_LDAP_ERR( err ) && attr != NULL;
		attr = ldap_next_attribute( ld, entry, ber )) {
	    if (( vals = ldap_get_values( ld, entry, attr )) == NULL ) {
		freevals = 0;
		if ( defattrs != NULL ) {
		    for ( i = 0; defattrs[ i ] != NULL; ++i ) {
			if ( strcasecmp( attr, defattrs[ i ] ) == 0 ) {
			    break;
			}
		    }
		    if ( defattrs[ i ] != NULL ) {
			vals = defvals[ i ];
		    }
		}
	    } else {
		freevals = 1;
	    }

	    if ( islower( *attr )) {	/* cosmetic -- upcase attr. name */
		*attr = toupper( *attr );
	    }

	    err = do_vals2text( ld, buf, vals, attr, labelwidth,
		    LDAP_SYN_CASEIGNORESTR, writeproc, writeparm, eol, 
		    rdncount, urlprefix );
	    if ( freevals ) {
		ldap_value_free( vals );
	    }
	}
    } else {
	for ( rowp = ldap_first_tmplrow( tmpl );
		NONFATAL_LDAP_ERR( err ) && rowp != NULLTMPLITEM;
		rowp = ldap_next_tmplrow( tmpl, rowp )) {
	    for ( colp = ldap_first_tmplcol( tmpl, rowp ); colp != NULLTMPLITEM;
		    colp = ldap_next_tmplcol( tmpl, rowp, colp )) {
		vals = NULL;
		if ( colp->ti_attrname == NULL || ( vals = ldap_get_values( ld,
			entry, colp->ti_attrname )) == NULL ) {
		    freevals = 0;
		    if ( !LDAP_IS_TMPLITEM_OPTION_SET( colp,
			    LDAP_DITEM_OPT_HIDEIFEMPTY ) && defattrs != NULL
			    && colp->ti_attrname != NULL ) {
			for ( i = 0; defattrs[ i ] != NULL; ++i ) {
			    if ( strcasecmp( colp->ti_attrname, defattrs[ i ] )
				    == 0 ) {
				break;
			    }
			}
			if ( defattrs[ i ] != NULL ) {
			    vals = defvals[ i ];
			}
		    }
		} else {
		    freevals = 1;
		    if ( LDAP_IS_TMPLITEM_OPTION_SET( colp,
			    LDAP_DITEM_OPT_SORTVALUES ) && vals[ 0 ] != NULL
			    && vals[ 1 ] != NULL ) {
			ldap_sort_values( ld, vals, ldap_sort_strcasecmp );
		    }
		}

		/*
		 * don't bother even calling do_vals2text() if no values
		 * or boolean with value false and "hide if false" option set
		 */
		show = ( vals != NULL && vals[ 0 ] != NULL );
		if ( show && LDAP_GET_SYN_TYPE( colp->ti_syntaxid )
			== LDAP_SYN_TYPE_BOOLEAN && LDAP_IS_TMPLITEM_OPTION_SET(
			colp, LDAP_DITEM_OPT_HIDEIFFALSE ) &&
			toupper( vals[ 0 ][ 0 ] ) != 'T' ) {
		    show = 0;
		}

		if ( colp->ti_syntaxid == LDAP_SYN_SEARCHACTION ) {
		    if (( opts & LDAP_DISP_OPT_DOSEARCHACTIONS ) != 0 ) {
			if ( colp->ti_attrname == NULL || ( show &&
				toupper( vals[ 0 ][ 0 ] ) == 'T' )) {
			    err = searchaction( ld, buf, base, entry, dn, colp,
				    labelwidth, rdncount, writeproc,
				    writeparm, eol, urlprefix );
			}
		    }
		    show = 0;
		}

		if ( show ) {
		    err = do_vals2text( ld, buf, vals, colp->ti_label,
			labelwidth, colp->ti_syntaxid, writeproc, writeparm,
			eol, rdncount, urlprefix );
		}

		if ( freevals ) {
		    ldap_value_free( vals );
		}
	    }
	}
    }

    if ( html  && !(( opts & LDAP_DISP_OPT_HTMLBODYONLY ) != 0 )) {
	sprintf( buf, "</BODY>%s</HTML>%s", eol, eol );
	(*writeproc)( writeparm, buf, strlen( buf ));
    }

    free( dn );
    if ( freebuf ) {
	free( buf );
    }

    return( err );
}