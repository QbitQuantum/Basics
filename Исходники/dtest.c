main( int argc, char **argv )
{
	long		i, i2, num;
	unsigned long	len;
	int		tag;
	char		*str, *s1, *s2;
	BerElement	ber;
	Sockbuf		sb;
	extern char	*optarg;

#ifdef MACOS
	ccommand( &argv );
	cshow( stdout );
#endif /* MACOS */

	bzero( &sb, sizeof(sb) );
	sb.sb_sd = 0;
	sb.sb_ber.ber_buf = NULL;
	if ( (tag = ber_get_next( &sb, &len, &ber )) == -1 ) {
		perror( "ber_get_next" );
		exit( 1 );
	}
	printf( "message has tag 0x%x and length %ld\n", tag, len );

	if ( ber_scanf( &ber, "i", &i ) == -1 ) {
		fprintf( stderr, "ber_scanf returns -1\n" );
		exit( 1 );
	}
	printf( "got int %d\n", i );

	return( 0 );
}