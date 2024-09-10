int main( int argc, char **argv )
{
	int i, j;
	FILE *fp, *infp;
	char **seq;
	int *grpseq;
	char *tmpseq;
	int  **pointt;
	static char name[M][B];
	static int nlen[M];
	double **mtx;
	double **mtx2;
	double score, score0;
	static short *table1;
	char b[B];

	arguments( argc, argv );

	if( inputfile )
	{
		infp = fopen( inputfile, "r" );
		if( !infp )
		{
			fprintf( stderr, "Cannot open %s\n", inputfile );
			exit( 1 );
		}
	}
	else
		infp = stdin;

#if 0
	PreRead( stdin, &njob, &nlenmax );
#else
	getnumlen( infp );
#endif
	rewind( infp );
	if( njob < 2 )
	{
		fprintf( stderr, "At least 2 sequences should be input!\n"
						 "Only %d sequence found.\n", njob );
		exit( 1 );
	}

	tmpseq = AllocateCharVec( nlenmax+1 );
	seq = AllocateCharMtx( njob, nlenmax+1 );
	grpseq = AllocateIntVec( nlenmax+1 );
	pointt = AllocateIntMtx( njob, nlenmax+1 );
	mtx = AllocateDoubleMtx( njob, njob );
	mtx2 = AllocateDoubleMtx( njob, njob );
	pamN = NOTSPECIFIED;

#if 0
	FRead( infp, name, nlen, seq );
#else
	readData( infp, name, nlen, seq );
#endif

	fclose( infp );

	constants( njob, seq );

	if( dorp == 'd' ) tsize = (int)pow( 4, 6 );
	else              tsize = (int)pow( 6, 6 );

	maxl = 0;
	for( i=0; i<njob; i++ ) 
	{
		gappick0( tmpseq, seq[i] );
		nlen[i] = strlen( tmpseq );
		if( nlen[i] < 6 )
		{
			fprintf( stderr, "Seq %d, too short, %d characters\n", i+1, nlen[i] );
			exit( 1 );
		}
		if( nlen[i] > maxl ) maxl = nlen[i];
		if( dorp == 'd' ) /* nuc */
		{
			seq_grp_nuc( grpseq, tmpseq );
			makepointtable_nuc( pointt[i], grpseq );
		}
		else                 /* amino */
		{
			seq_grp( grpseq, tmpseq );
			makepointtable( pointt[i], grpseq );
		}
	}
	for( i=0; i<njob; i++ )
	{
		table1 = (short *)calloc( tsize, sizeof( short ) );
		if( !table1 ) ErrorExit( "Cannot allocate table1\n" );
		if( i % 10 == 0 )
		{
			fprintf( stderr, "%4d / %4d\r", i+1, njob );
		}
		makecompositiontable_p( table1, pointt[i] );

		for( j=i; j<njob; j++ ) 
		{
			score = (double)commonsextet_p( table1, pointt[j] );
			mtx[i][j] = score;
		} 
		free( table1 );
	}
	for( i=0; i<njob; i++ )
	{
		score0 = mtx[i][i];
		for( j=0; j<njob; j++ ) 
			mtx2[i][j] = ( score0 - mtx[MIN(i,j)][MAX(i,j)] ) / score0 * 3.0;
	}
	for( i=0; i<njob-1; i++ ) for( j=i+1; j<njob; j++ ) 
	{
#if TEST
                double jscore;
                jscore = mtx[i][j] / ( MIN( strlen( seq[i] ), strlen( seq[j] ) ) - 2 );
                fprintf( stdout, "jscore = %f\n", jscore );

		fprintf( stdout, "mtx2[%d][%d] = %f, mtx2[%d][%d] = %f\n", i, j, mtx2[i][j], j, i, mtx2[j][i] );
#endif
		mtx2[i][j] = MIN( mtx2[i][j], mtx2[j][i] );
#if TEST
		fprintf( stdout, "sonokekka mtx2[%d][%d] %f\n", i, j, mtx2[i][j] );
#endif
	}

	if( disopt )
	{
		for( i=0; i<njob; i++ ) 
		{
			sprintf( b, "=lgth = %04d", nlen[i] );
			strins( b, name[i] );
		}
	}
		
	fp = fopen( "hat2", "w" );
	if( !fp ) ErrorExit( "Cannot open hat2." );
	WriteHat2( fp, njob, name, mtx2 );
	fclose( fp );

	fprintf( stderr, "\n" );
	SHOWVERSION;
	exit( 0 );
}