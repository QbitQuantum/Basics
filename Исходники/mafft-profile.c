int main( int argc, char *argv[] )
{
	char **argv2;
	static int  *nlen;	
	static char **name, **seq;
	static char **seq1, **seq2;
	static char **mseq1, **mseq2;
	static char **aseq;
	static char **bseq;
	static double **pscore;
	static double *eff;
	int i, j, len1, len2;
	static int ***topol;
	static double **len;
	FILE *gp1, *gp2;
	char c;
	int nlenmax1, nlenmax2, nseq1, nseq2;
	int alloclen;

	argv2 = arguments( argc, argv );

	fprintf( stderr, "####### in galn\n" );

	initFiles();

	fprintf( stderr, "file1 = %s\n", argv2[0] );
	fprintf( stderr, "file2 = %s\n", argv2[1] );

	gp1 = fopen( argv2[0], "r" ); if( !gp1 ) ErrorExit( "cannot open file1" );
	gp2 = fopen( argv2[1], "r" ); if( !gp2 ) ErrorExit( "cannot open file2" );

#if 0
	PreRead( gp1, &nseq1, &nlenmax1 );
	PreRead( gp2, &nseq2, &nlenmax2 );
#else
    getnumlen( gp1 );
	nseq1 = njob; nlenmax1 = nlenmax;
    getnumlen( gp2 );
	nseq2 = njob; nlenmax2 = nlenmax;
#endif

	njob = nseq1 + nseq2;
	nlenmax = MAX( nlenmax1, nlenmax2 );

	rewind( gp1 );
	rewind( gp2 );


	name = AllocateCharMtx( njob, B );
	nlen = AllocateIntVec( njob );
	seq1 = AllocateCharMtx( nseq1, nlenmax*3 );
	seq2 = AllocateCharMtx( nseq2, nlenmax*3 );
	seq  = AllocateCharMtx( njob, 1 );
	aseq = AllocateCharMtx( njob, nlenmax*3 );
	bseq = AllocateCharMtx( njob, nlenmax*3 );
	mseq1 = AllocateCharMtx( njob, 1 );
	mseq2 = AllocateCharMtx( njob, 1 );
	alloclen = nlenmax * 3;

	topol = AllocateIntCub( njob, 2, njob );
	len = AllocateDoubleMtx( njob, 2 );
	pscore = AllocateDoubleMtx( njob, njob );
	eff = AllocateDoubleVec( njob );

#if 0
    njob=nseq2; FRead( gp2, name+nseq1, nlen+nseq1, seq2 );
	njob=nseq1; FRead( gp1, name, nlen, seq1 );
#else
    njob=nseq2; readDataforgaln( gp2, name+nseq1, nlen+nseq1, seq2 );
	njob=nseq1; readDataforgaln( gp1, name, nlen, seq1 );
#endif
	njob = nseq1 + nseq2;


#if 0  // CHUUI
	commongappick( nseq1, seq1 );
	commongappick( nseq2, seq2 );
#endif

	for( i=0; i<nseq1; i++ ) seq[i] = seq1[i];
	for( i=nseq1; i<njob; i++ ) seq[i] = seq2[i-nseq1];
/*
	Write( stdout, njob, name, nlen, seq );
*/

    constants( njob, seq );

    WriteOptions( trap_g );

    c = seqcheck( seq );
    if( c )
    {
        fprintf( stderr, "Illeagal character %c\n", c );
        exit( 1 );
    }
    for( i=1; i<nseq1; i++ ) 
    {
        if( nlen[i] != nlen[0] ) 
            ErrorExit( "group1 is not aligned." );
    }
    for( i=nseq1+1;  i<njob; i++ ) 
    {
        if( nlen[i] != nlen[nseq1] ) 
            ErrorExit( "group2 is not aligned." );
    }
    if( tbutree == 0 )
	{
		for( i=0; i<nseq1; i++ ) 
		{
			for( j=i+1; j<nseq1; j++ )
			{
				pscore[i][j] = (double)substitution_hosei( seq[i], seq[j] );
//				fprintf( stderr, "%d-%d, %5.1f \n", i, j, pscore[i][j] );
			}
			for( j=nseq1; j<njob; j++ )
			{
				pscore[i][j] = 3.0;
//				fprintf( stderr, "%d-%d, %5.1f \n", i, j, pscore[i][j] );
			}
		}
		for( i=nseq1; i<njob-1; i++ ) 
		{
			for( j=i+1; j<njob; j++ )
			{
				pscore[i][j] = (double)substitution_hosei( seq[i], seq[j] );
//				fprintf( stderr, "%d-%d, %5.1f \n", i, j, pscore[i][j] );
			}
		}
//		fprintf( stderr, "\n" );


    }
   	else
	{
		fprintf( stderr, "Not supported\n" );
		exit( 1 );
#if 0
		prep = fopen( "hat2", "r" );
		if( prep == NULL ) ErrorExit( "Make hat2." );
		readhat2( prep, njob, name, pscore );
		fclose( prep );
#endif
	}
	fprintf( stderr, "Constructing dendrogram ... " );
	if( treemethod == 'x' )
		veryfastsupg( njob, pscore, topol, len );
	else
		ErrorExit( "Incorrect tree\n" );
	fprintf( stderr, "done.\n" );

	if( tbrweight )
	{
		weight = 3;
		counteff_simple( njob, topol, len, eff );
//		for( i=0; i<njob; i++ ) fprintf( stderr, "eff[%d] = %f\n", i, eff[i] );
	}
	else
	{
		for( i=0; i<njob; i++ ) eff[i] = 1.0;
	}

	len1 = strlen( seq[0] );
	len2 = strlen( seq[nseq1] );
	if( len1 > 30000 || len2 > 30000 )
	{       
		fprintf( stderr, "\nlen1=%d, len2=%d, Switching to the memsave mode.\n", len1, len2 );
		alg = 'M';
	}       
        



	GroupAlign( nseq1, nseq2, name, nlen, seq, aseq, mseq1, mseq2, topol, len, eff, alloclen );

#if 0
	writePre( njob, name, nlen, aseq, 1 );
#else
	writeDataforgaln( stdout, njob, name, nlen, aseq );
#endif

	SHOWVERSION;
	return( 0 );
}