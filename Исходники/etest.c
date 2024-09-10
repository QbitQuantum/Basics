int
main( int argc, char **argv )
{
	char	*s;

	int			fd, rc;
	BerElement	*ber;
	Sockbuf		*sb;

	/* enable debugging */
	int ival = -1;
	ber_set_option( NULL, LBER_OPT_DEBUG_LEVEL, &ival );

	if ( argc < 2 ) {
		usage( argv[0] );
		return( EXIT_FAILURE );
	}

#ifdef HAVE_CONSOLE_H
	ccommand( &argv );
	cshow( stdout );

	if (( fd = open( "lber-test", O_WRONLY|O_CREAT|O_TRUNC|O_BINARY ))
		< 0 ) {
	    perror( "open" );
	    return( EXIT_FAILURE );
	}

#else
	fd = fileno(stdout);
#endif

	sb = ber_sockbuf_alloc();
	ber_sockbuf_add_io( sb, &ber_sockbuf_io_fd, LBER_SBIOD_LEVEL_PROVIDER,
		(void *)&fd );

	if( sb == NULL ) {
		perror( "ber_sockbuf_alloc_fd" );
		return( EXIT_FAILURE );
	}

	if ( (ber = ber_alloc_t( LBER_USE_DER )) == NULL ) {
		perror( "ber_alloc" );
		return( EXIT_FAILURE );
	}

	fprintf(stderr, "encode: start\n" );
	if( ber_printf( ber, "{" /*}*/ ) ) {
		perror( "ber_printf {" /*}*/ );
		return( EXIT_FAILURE );
	}

	for ( s = argv[1]; *s; s++ ) {
		char *buf;
		char fmt[2];

		fmt[0] = *s;
		fmt[1] = '\0';

		fprintf(stderr, "encode: %s\n", fmt );
		switch ( *s ) {
		case 'i':	/* int */
		case 'b':	/* boolean */
		case 'e':	/* enumeration */
			buf = getbuf();
			rc = ber_printf( ber, fmt, atoi(buf) );
			break;

		case 'n':	/* null */
		case '{':	/* begin sequence */
		case '}':	/* end sequence */
		case '[':	/* begin set */
		case ']':	/* end set */
			rc = ber_printf( ber, fmt );
			break;

		case 'o':	/* octet string (non-null terminated) */
		case 'B':	/* bit string */
			buf = getbuf();
			rc = ber_printf( ber, fmt, buf, strlen(buf) );
			break;

		case 's':	/* string */
		case 't':	/* tag for the next element */
			buf = getbuf();
			rc = ber_printf( ber, fmt, buf );
			break;

		default:
			fprintf( stderr, "encode: unknown fmt %c\n", *fmt );
			rc = -1;
			break;
		}

		if( rc == -1 ) {
			perror( "ber_printf" );
			return( EXIT_FAILURE );
		}
	}

	fprintf(stderr, "encode: end\n" );
	if( ber_printf( ber, /*{*/ "N}" ) == -1 ) {
		perror( /*{*/ "ber_printf }" );
		return( EXIT_FAILURE );
	}

	if ( ber_flush( sb, ber, 1 ) == -1 ) {
		perror( "ber_flush" );
		return( EXIT_FAILURE );
	}

	ber_sockbuf_free( sb );
	return( EXIT_SUCCESS );
}