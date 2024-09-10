/*
 * Map key -> value resolution
 * NOTE: these are old-fashion maps; new maps will be parsed on separate
 * config lines, and referred by name.
 */
int
rewrite_xmap_apply(
		struct rewrite_info *info,
		struct rewrite_op *op,
		struct rewrite_map *map,
		struct berval *key,
		struct berval *val
)
{
	int rc = REWRITE_SUCCESS;
	
	assert( info != NULL );
	assert( op != NULL );
	assert( map != NULL );
	assert( key != NULL );
	assert( val != NULL );
	
	val->bv_val = NULL;
	val->bv_len = 0;
	
	switch ( map->lm_type ) {
#ifdef HAVE_GETPWNAM
	case REWRITE_MAP_XPWDMAP: {
		struct passwd *pwd;

#ifdef USE_REWRITE_LDAP_PVT_THREADS
		ldap_pvt_thread_mutex_lock( &xpasswd_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */
		
		pwd = getpwnam( key->bv_val );
		if ( pwd == NULL ) {

#ifdef USE_REWRITE_LDAP_PVT_THREADS
			ldap_pvt_thread_mutex_unlock( &xpasswd_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */

			rc = LDAP_NO_SUCH_OBJECT;
			break;
		}

#ifdef HAVE_STRUCT_PASSWD_PW_GECOS
		if ( pwd->pw_gecos != NULL && pwd->pw_gecos[0] != '\0' ) {
			int l = strlen( pwd->pw_gecos );
			
			val->bv_val = strdup( pwd->pw_gecos );
			val->bv_len = l;
		} else
#endif /* HAVE_STRUCT_PASSWD_PW_GECOS */
		{
			val->bv_val = strdup( key->bv_val );
			val->bv_len = key->bv_len;
		}

#ifdef USE_REWRITE_LDAP_PVT_THREADS
		ldap_pvt_thread_mutex_unlock( &xpasswd_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */

		if ( val->bv_val == NULL ) {
			rc = REWRITE_ERR;
		}
		break;
	}
#endif /* HAVE_GETPWNAM*/
	
	case REWRITE_MAP_XFILEMAP: {
		char buf[1024];
		
		if ( map->lm_args == NULL ) {
			rc = REWRITE_ERR;
			break;
		}
		
#ifdef USE_REWRITE_LDAP_PVT_THREADS
		ldap_pvt_thread_mutex_lock( &map->lm_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */

		rewind( ( FILE * )map->lm_args );
		
		while ( fgets( buf, sizeof( buf ), ( FILE * )map->lm_args ) ) {
			char *p;
			int blen;
			
			blen = strlen( buf );
			if ( buf[ blen - 1 ] == '\n' ) {
				buf[ blen - 1 ] = '\0';
			}
			
			p = strtok( buf, " " );
			if ( p == NULL ) {
#ifdef USE_REWRITE_LDAP_PVT_THREADS
				ldap_pvt_thread_mutex_unlock( &map->lm_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */
				rc = REWRITE_ERR;
				goto rc_return;
			}
			if ( strcasecmp( p, key->bv_val ) == 0 
					&& ( p = strtok( NULL, "" ) ) ) {
				val->bv_val = strdup( p );
				if ( val->bv_val == NULL ) {
					return REWRITE_ERR;
				}

				val->bv_len = strlen( p );
				
#ifdef USE_REWRITE_LDAP_PVT_THREADS
				ldap_pvt_thread_mutex_unlock( &map->lm_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */
				
				goto rc_return;
			}
		}

#ifdef USE_REWRITE_LDAP_PVT_THREADS
		ldap_pvt_thread_mutex_unlock( &map->lm_mutex );
#endif /* USE_REWRITE_LDAP_PVT_THREADS */

		rc = REWRITE_ERR;
		
		break;
	}

	case REWRITE_MAP_XLDAPMAP: {
		LDAP *ld;
		char filter[1024];
		LDAPMessage *res = NULL, *entry;
		LDAPURLDesc *lud = ( LDAPURLDesc * )map->lm_args;
		int attrsonly = 0;
		char **values;

		assert( lud != NULL );

		/*
		 * No mutex because there is no write on the map data
		 */
		
		ld = ldap_init( lud->lud_host, lud->lud_port );
		if ( ld == NULL ) {
			rc = REWRITE_ERR;
			goto rc_return;
		}

		snprintf( filter, sizeof( filter ), lud->lud_filter,
				key->bv_val );

		if ( strcasecmp( lud->lud_attrs[ 0 ], "dn" ) == 0 ) {
			attrsonly = 1;
		}
		rc = ldap_search_s( ld, lud->lud_dn, lud->lud_scope,
				filter, lud->lud_attrs, attrsonly, &res );
		if ( rc != LDAP_SUCCESS ) {
			ldap_unbind( ld );
			rc = REWRITE_ERR;
			goto rc_return;
		}

		if ( ldap_count_entries( ld, res ) != 1 ) {
			ldap_unbind( ld );
			rc = REWRITE_ERR;
			goto rc_return;
		}

		entry = ldap_first_entry( ld, res );
		if ( entry == NULL ) {
			ldap_msgfree( res );
			ldap_unbind( ld );
			rc = REWRITE_ERR;
			goto rc_return;
		}
		if ( attrsonly == 1 ) {
			val->bv_val = ldap_get_dn( ld, entry );

		} else {
			values = ldap_get_values( ld, entry,
					lud->lud_attrs[0] );
			if ( values != NULL ) {
				val->bv_val = strdup( values[ 0 ] );
				ldap_value_free( values );
			}
		}

		ldap_msgfree( res );
		ldap_unbind( ld );
		
		if ( val->bv_val == NULL ) {
			rc = REWRITE_ERR;
			goto rc_return;
		}
		val->bv_len = strlen( val->bv_val );

		rc = REWRITE_SUCCESS;
	} break;
	}

rc_return:;
	return rc;
}