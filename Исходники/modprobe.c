static struct dep_t *build_dep ( void )
{
	int fd;
	struct utsname un;
	struct dep_t *first = 0;
	struct dep_t *current = 0;
	char buffer[256];
	char *filename = buffer;
	int continuation_line = 0;
	
	if ( uname ( &un ))
		return 0;
		
	// check for buffer overflow in following code
	if ( xstrlen ( un.release ) > ( sizeof( buffer ) - 64 )) {
		return 0;
	}
				
	strcpy ( filename, "/lib/modules/" );
	strcat ( filename, un.release );
	strcat ( filename, "/modules.dep" );

	if (( fd = open ( filename, O_RDONLY )) < 0 )
		return 0;

	while ( reads ( fd, buffer, sizeof( buffer ))) {
		int l = xstrlen ( buffer );
		char *p = 0;
		
		while ( isspace ( buffer [l-1] )) {
			buffer [l-1] = 0;
			l--;
		}
		
		if ( l == 0 ) {
			continuation_line = 0;
			continue;
		}
		
		if ( !continuation_line ) {		
			char *col = strchr ( buffer, ':' );
		
			if ( col ) {
				char *mods;
				char *mod;
				int ext = 0;
				
				*col = 0;
				mods = strrchr ( buffer, '/' );
				
				if ( !mods )
					mods = buffer;
				else
					mods++;
					
				if (( *(col-2) == '.' ) && ( *(col-1) == 'o' ))
					ext = 2;
				
				mod = xstrndup ( mods, col - mods - ext );
					
				if ( !current ) {
					first = current = (struct dep_t *) xmalloc ( sizeof ( struct dep_t ));
				}
				else {
					current-> m_next = (struct dep_t *) xmalloc ( sizeof ( struct dep_t ));
					current = current-> m_next;
				}
				current-> m_module  = mod;
				current-> m_isalias = 0;
				current-> m_depcnt  = 0;
				current-> m_deparr  = 0;
				current-> m_next    = 0;
						
				//printf ( "%s:\n", mod );
						
				p = col + 1;		
			}
			else
				p = 0;
		}
		else
			p = buffer;
			
		if ( p && *p ) {
			char *end = &buffer [l-1];
			char *deps = strrchr ( end, '/' );
			char *dep;
			int ext = 0;
			
			while ( isblank ( *end ) || ( *end == '\\' ))
				end--;
				
			deps = strrchr ( p, '/' );
			
			if ( !deps || ( deps < p )) {
				deps = p;
		
				while ( isblank ( *deps ))
					deps++;
			}
			else
				deps++;
			
			if (( *(end-1) == '.' ) && ( *end == 'o' ))
				ext = 2;

			/* Cope with blank lines */
			if ((end-deps-ext+1) <= 0)
				continue;
			
			dep = xstrndup ( deps, end - deps - ext + 1 );
			
			current-> m_depcnt++;
			current-> m_deparr = (char **) xrealloc ( current-> m_deparr, sizeof ( char *) * current-> m_depcnt );
			current-> m_deparr [current-> m_depcnt - 1] = dep;		
			
			//printf ( "    %d) %s\n", current-> m_depcnt, current-> m_deparr [current-> m_depcnt -1] );
		}
	
		if ( buffer [l-1] == '\\' )
			continuation_line = 1;
		else
			continuation_line = 0;
	}
	close ( fd );

	// alias parsing is not 100% correct (no correct handling of continuation lines within an alias) !

	if (( fd = open ( "/etc/modules.conf", O_RDONLY )) < 0 )
		if (( fd = open ( "/etc/conf.modules", O_RDONLY )) < 0 )
			return first;
	
	continuation_line = 0;
	while ( reads ( fd, buffer, sizeof( buffer ))) {
		int l;
		char *p;
		
		p = strchr ( buffer, '#' );	
		if ( p )
			*p = 0;
			
		l = xstrlen ( buffer );
	
		while ( l && isspace ( buffer [l-1] )) {
			buffer [l-1] = 0;
			l--;
		}
		
		if ( l == 0 ) {
			continuation_line = 0;
			continue;
		}
		
		if ( !continuation_line ) {		
			if (( strncmp ( buffer, "alias", 5 ) == 0 ) && isspace ( buffer [5] )) {
				char *alias, *mod;

				alias = buffer + 6;
				
				while ( isspace ( *alias ))
					alias++;			
				mod = alias;					
				while ( !isspace ( *mod ))
					mod++;
				*mod = 0;
				mod++;
				while ( isspace ( *mod ))
					mod++;
										
//					fprintf ( stderr, "ALIAS: '%s' -> '%s'\n", alias, mod );
				
				if ( !current ) {
					first = current = (struct dep_t *) xmalloc ( sizeof ( struct dep_t ));
				}
				else {
					current-> m_next = (struct dep_t *) xmalloc ( sizeof ( struct dep_t ));
					current = current-> m_next;
				}
				current-> m_module  = xstrdup ( alias );
				current-> m_isalias = 1;
				
				if (( strcmp ( alias, "off" ) == 0 ) || ( strcmp ( alias, "null" ) == 0 )) {
					current-> m_depcnt = 0;
					current-> m_deparr = 0;
				}
				else {
					current-> m_depcnt  = 1;
					current-> m_deparr  = xmalloc ( 1 * sizeof( char * ));
					current-> m_deparr[0] = xstrdup ( mod );
				}
				current-> m_next    = 0;					
			}				
		}
	}
	close ( fd );
	
	return first;
}