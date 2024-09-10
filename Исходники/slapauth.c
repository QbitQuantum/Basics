int
slapauth( int argc, char **argv )
{
	int			rc = EXIT_SUCCESS;
	const char		*progname = "slapauth";
	Connection		conn = {0};
	OperationBuffer	opbuf;
	Operation		*op;
	void			*thrctx;

	slap_tool_init( progname, SLAPAUTH, argc, argv );

	argv = &argv[ optind ];
	argc -= optind;

	thrctx = ldap_pvt_thread_pool_context();
	connection_fake_init( &conn, &opbuf, thrctx );
	op = &opbuf.ob_op;

	conn.c_sasl_bind_mech = mech;

	if ( !BER_BVISNULL( &authzID ) ) {
		struct berval	authzdn;
		
		rc = slap_sasl_getdn( &conn, op, &authzID, NULL, &authzdn,
				SLAP_GETDN_AUTHZID );
		if ( rc != LDAP_SUCCESS ) {
			fprintf( stderr, "authzID: <%s> check failed %d (%s)\n",
					authzID.bv_val, rc,
					ldap_err2string( rc ) );
			rc = 1;
			BER_BVZERO( &authzID );
			goto destroy;
		} 

		authzID = authzdn;
	}


	if ( !BER_BVISNULL( &authcID ) ) {
		if ( !BER_BVISNULL( &authzID ) || argc == 0 ) {
			rc = do_check( &conn, op, &authcID );
			goto destroy;
		}

		for ( ; argc--; argv++ ) {
			struct berval	authzdn;
		
			ber_str2bv( argv[ 0 ], 0, 0, &authzID );

			rc = slap_sasl_getdn( &conn, op, &authzID, NULL, &authzdn,
					SLAP_GETDN_AUTHZID );
			if ( rc != LDAP_SUCCESS ) {
				fprintf( stderr, "authzID: <%s> check failed %d (%s)\n",
						authzID.bv_val, rc,
						ldap_err2string( rc ) );
				rc = -1;
				BER_BVZERO( &authzID );
				if ( !continuemode ) {
					goto destroy;
				}
			}

			authzID = authzdn;

			rc = do_check( &conn, op, &authcID );

			op->o_tmpfree( authzID.bv_val, op->o_tmpmemctx );
			BER_BVZERO( &authzID );

			if ( rc && !continuemode ) {
				goto destroy;
			}
		}

		goto destroy;
	}

	for ( ; argc--; argv++ ) {
		struct berval	id;

		ber_str2bv( argv[ 0 ], 0, 0, &id );

		rc = do_check( &conn, op, &id );

		if ( rc && !continuemode ) {
			goto destroy;
		}
	}

destroy:;
	if ( !BER_BVISNULL( &authzID ) ) {
		op->o_tmpfree( authzID.bv_val, op->o_tmpmemctx );
	}
	if ( slap_tool_destroy())
		rc = EXIT_FAILURE;

	return rc;
}