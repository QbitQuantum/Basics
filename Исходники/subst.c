/*
 * Compiles a substitution pattern
 */
struct rewrite_subst *
rewrite_subst_compile(
		struct rewrite_info *info,
		const char *str
)
{
	size_t subs_len;
	struct berval *subs = NULL, *tmps;
	struct rewrite_submatch *submatch = NULL;

	struct rewrite_subst *s = NULL;

	char *result, *begin, *p;
	int nsub = 0, l;

	assert( info != NULL );
	assert( str != NULL );

	result = strdup( str );
	if ( result == NULL ) {
		return NULL;
	}

	/*
	 * Take care of substitution string
	 */
	for ( p = begin = result, subs_len = 0; p[ 0 ] != '\0'; p++ ) {

		/*
		 * Keep only single escapes '%'
		 */
		if (  !IS_REWRITE_SUBMATCH_ESCAPE( p[ 0 ] ) ) {
			continue;
		} 

		if (  IS_REWRITE_SUBMATCH_ESCAPE( p[ 1 ] ) ) {
			/* Pull &p[1] over p, including the trailing '\0' */
			AC_MEMCPY((char *)p, &p[ 1 ], strlen( p ) );
			continue;
		}

		tmps = ( struct berval * )realloc( subs,
				sizeof( struct berval )*( nsub + 1 ) );
		if ( tmps == NULL ) {
			goto cleanup;
		}
		subs = tmps;
		
		/*
		 * I think an `if l > 0' at runtime is better outside than
		 * inside a function call ...
		 */
		l = p - begin;
		if ( l > 0 ) {
			subs_len += l;
			subs[ nsub ].bv_len = l;
			subs[ nsub ].bv_val = malloc( l + 1 );
			if ( subs[ nsub ].bv_val == NULL ) {
				goto cleanup;
			}
			AC_MEMCPY( subs[ nsub ].bv_val, begin, l );
			subs[ nsub ].bv_val[ l ] = '\0';
		} else {
			subs[ nsub ].bv_val = NULL;
			subs[ nsub ].bv_len = 0;
		}
		
		/*
		 * Substitution pattern
		 */
		if ( isdigit( (unsigned char) p[ 1 ] ) ) {
			struct rewrite_submatch *tmpsm;
			int d = p[ 1 ] - '0';

			/*
			 * Add a new value substitution scheme
			 */

			tmpsm = ( struct rewrite_submatch * )realloc( submatch,
					sizeof( struct rewrite_submatch )*( nsub + 1 ) );
			if ( tmpsm == NULL ) {
				goto cleanup;
			}
			submatch = tmpsm;
			submatch[ nsub ].ls_submatch = d;

			/*
			 * If there is no argument, use default
			 * (substitute substring as is)
			 */
			if ( p[ 2 ] != '{' ) {
				submatch[ nsub ].ls_type = 
					REWRITE_SUBMATCH_ASIS;
				submatch[ nsub ].ls_map = NULL;
				begin = ++p + 1;

			} else {
				struct rewrite_map *map;

				submatch[ nsub ].ls_type =
					REWRITE_SUBMATCH_XMAP;

				map = rewrite_xmap_parse( info,
						p + 3, (const char **)&begin );
				if ( map == NULL ) {
					goto cleanup;
				}
				submatch[ nsub ].ls_map = map;
				p = begin - 1;
			}

		/*
		 * Map with args ...
		 */
		} else if ( p[ 1 ] == '{' ) {
			struct rewrite_map *map;
			struct rewrite_submatch *tmpsm;

			map = rewrite_map_parse( info, p + 2,
					(const char **)&begin );
			if ( map == NULL ) {
				goto cleanup;
			}
			p = begin - 1;

			/*
			 * Add a new value substitution scheme
			 */
			tmpsm = ( struct rewrite_submatch * )realloc( submatch,
					sizeof( struct rewrite_submatch )*( nsub + 1 ) );
			if ( tmpsm == NULL ) {
				goto cleanup;
			}
			submatch = tmpsm;
			submatch[ nsub ].ls_type =
				REWRITE_SUBMATCH_MAP_W_ARG;
			submatch[ nsub ].ls_map = map;

		/*
		 * Escape '%' ...
		 */
		} else if ( p[ 1 ] == '%' ) {
			AC_MEMCPY( &p[ 1 ], &p[ 2 ], strlen( &p[ 1 ] ) );
			continue;

		} else {
			goto cleanup;
		}

		nsub++;
	}
	
	/*
	 * Last part of string
	 */
	tmps = (struct berval * )realloc( subs, sizeof( struct berval )*( nsub + 1 ) );
	if ( tmps == NULL ) {
		/*
		 * XXX need to free the value subst stuff!
		 */
		free( subs );
		goto cleanup;
	}
	subs = tmps;
	l = p - begin;
	if ( l > 0 ) {
		subs_len += l;
		subs[ nsub ].bv_len = l;
		subs[ nsub ].bv_val = malloc( l + 1 );
		if ( subs[ nsub ].bv_val == NULL ) {
			free( subs );
			goto cleanup;
		}
		AC_MEMCPY( subs[ nsub ].bv_val, begin, l );
		subs[ nsub ].bv_val[ l ] = '\0';
	} else {
		subs[ nsub ].bv_val = NULL;
		subs[ nsub ].bv_len = 0;
	}

	s = calloc( sizeof( struct rewrite_subst ), 1 );
	if ( s == NULL ) {
		goto cleanup;
	}

	s->lt_subs_len = subs_len;
        s->lt_subs = subs;
        s->lt_num_submatch = nsub;
        s->lt_submatch = submatch;

cleanup:;
	free( result );

	return s;
}