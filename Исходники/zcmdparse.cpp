void zCmdParseCommandLine( int argc, char **argv, ZHashTable &hash ) {
	int nonOptionArgCount=0;
	for( int i=0; i<argc; i++ ) {
		if( argv[i][0] == '-' ) {
			// Does the option have a value assignment?
			char *valPtr = 0;
			for( int j=0; argv[i][j]; j++ ) {
				if( argv[i][j] == '=' ) {
					valPtr = &argv[i][j+1];
					argv[i][j] = 0;
					break;
				}
			}

			hash.putS( argv[i], valPtr ? valPtr : (char *)"*novalue*" );

			int len = strlen( argv[i] );
			char *indexKey = new char[len + 16];
			strcpy( indexKey, argv[i] );
			strcat( indexKey, "-index" );

			hash.putI( indexKey, i );
		}
		else {
			char key[32];
			sprintf( key, "nonOptionArg%d", nonOptionArgCount++ ); 
			hash.putS( key, argv[i] );
		}
	}
}