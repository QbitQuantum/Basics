int main ( int argc, char** argv ) {


	int ret;
	int i;

	uint32_t mode= MODE_DEFAULT;
	const char* command= NULL;
	const char* p;

	const char* infilename;
	char outfilename[OTF_PATH_MAX];
	char* outdir= NULL;

	int keep= 0;
	int zlevel= ZLEVEL;


	if ( 1 >= argc ) {

			SHOW_HELPTEXT;
			return 0;
	}
	

	/* collect parameters */
	for ( i= 1; i < argc; i++ ) {

		if ( 0 == strcmp( "-h", argv[i] ) || 0 == strcmp( "--help", argv[i] ) ) {

			SHOW_HELPTEXT;
			exit( 0 );

		} else 

		if ( 0 == strcmp( "-k", argv[i] ) ) {

			keep= 1;

		} else 

		if ( 0 == strcmp( "-o", argv[i] ) && i < argc -1 ) {

			outdir= argv[++i];
			keep= 1;

		} else 

		if ( 0 == strcmp( "-c", argv[i] ) ) {

			if ( MODE_DEFAULT == mode ) {

				mode= MODE_COMPRESS;

			} else {

				fprintf( stderr, "mode already set, cannot re-set, ignoring '-c'\n" );
			}

		} else 

		if ( 0 == strcmp( "-d", argv[i] ) ) {

			if ( MODE_DEFAULT == mode ) {

				mode= MODE_DECOMPRESS;

			} else {

				fprintf( stderr, "mode already set, cannot re-set, ignoring '-d'\n" );
			}

		} else 

		if ( ( '-' == argv[i][0] ) && ( '0' <= argv[i][1] ) && ( '9' >= argv[i][1] ) )  {

			zlevel= (int) ( argv[i][1] - '0' );

		} else 
		
		if ( 0 == strcmp( "-V", argv[i] ) ) {
		
			printf( "%u.%u.%u \"%s\"\n", OTF_VERSION_MAJOR, OTF_VERSION_MINOR,
				OTF_VERSION_SUB, OTF_VERSION_STRING);
			exit( 0 );
		}
	}

	/* look at argv[0], mode defaults to compress/decomress according to command name */
	if ( MODE_DEFAULT == mode ) {
	
		p= strrchr( argv[0], '/' );
		command = NULL != p ? p+1 : argv[0];

		if ( 0 == strcmp( "otfdecompress", command ) || 0 == strcmp( "otfdecompress.exe", command ) ) {

			mode= MODE_DECOMPRESS;

		}

	}


	/* files to (de)compress */
	for ( i= 1; i < argc; i++ ) {

		if ( '-' == argv[i][0] ) {

			/* switches already handled */

			if ( outdir != NULL && 0 == strcmp( argv[i], "-o" ) ) {

				/* skip value of option '-o' */
				i++;

			}

		} else {
		
			/* assume argument is a file name */

			infilename= argv[i];

			/* compose output file name */

			if ( NULL == outdir ) {

				snprintf( outfilename, sizeof( outfilename ) -1, "%s",
					  infilename );

			} else {

				p= strrchr( infilename, '/' );
				if ( NULL != p ) p++;
				else p= infilename;
				
				snprintf( outfilename, sizeof( outfilename ) -1, "%s/%s",
					  outdir, p );

			}

			switch ( mode ) {

			case MODE_DECOMPRESS:

				/* decompress file */

				/* check for ".z" at the end and refuse uncompression if not found */
				if ( ( 2 >= strlen( infilename ) ) ||
				     ( 0 != strcmp( infilename +strlen( infilename ) -2, ".z" ) ) ) {
				
					fprintf( stderr, "ERROR: no trailing '.z' in filename '%s', rejecting\n", 
						 infilename );

					continue;
				}

				/* cut trailing '.z' from output file name */
				outfilename[strlen( outfilename )-2] = '\0';

				fprintf( stdout, "decompress \"%s\" -> \"%s\"\n", 
					infilename, outfilename );

				ret= decompressFile( infilename, outfilename, BUFFERSIZE );

				if ( 0 == ret ) {

					if ( keep ) {

						/* keep compressed file */

					} else {

						/* remove compressed file */
						ret= unlink( infilename );

						if ( 0 != ret ) {

							fprintf( stderr, "error removing '%s'\n", infilename );
						}
					}

				} else {

					fprintf( stderr, "decompress error for file '%s'\n", infilename );
				} 

				break;

			case MODE_COMPRESS:
			case MODE_DEFAULT:
			default:

				/* compress file */

				/* check for ".z" at the end and refuse compression if found */
				if ( ( 2 < strlen( infilename ) ) &&
				     ( 0 == strcmp( infilename +strlen( infilename ) -2, ".z" ) ) ) {
				
					fprintf( stderr, "ERROR: found '.z' suffix in filename, "
						"file '%s' seems already compressed, skip\n", 
						infilename );

					continue;
				}

				/* add trailing '.z' to output file name */
				if ( strlen( outfilename ) +2 < sizeof( outfilename ) )
					strcat( outfilename, ".z" );

				fprintf( stdout, "compress \"%s\" -> \"%s\"\n", 
					infilename, outfilename );

				ret= compressFile( infilename, outfilename, zlevel, BUFFERSIZE );

				if ( 0 == ret ) {

					if ( keep ) {

						if ( outdir ) {

							/* keep uncompressed file */

						} else {

							/* rename original file */

							snprintf( outfilename, sizeof( outfilename ) -1, "%s.original",
								  infilename );

							ret= rename( infilename, outfilename );
						
							if ( 0 != ret ) {

								fprintf( stderr, "error renaming '%s' to '%s'\n", 
									 infilename, outfilename );

							}

						}

					} else {

						/* remove uncompressed */

						ret= unlink( infilename );

						if ( 0 != ret ) {

							fprintf( stderr, "error removing '%s'\n", infilename );
						}
					}

				} else {

					fprintf( stderr, "compress error for file '%s'\n", infilename );
				}

				break;
			}
		}
	}

	return 0;
}