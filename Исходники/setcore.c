int main( int argc, char *argv[] )
{
	static int  nlen[M];	
	static char **name, **seq;
	static char **oseq;
	static double **pscore;
	static double *eff;
	static double **node0, **node1;
	static double *gapc;
	static double *avgap;
	double tmpavgap;
	int i, j, m, goffset;
	static int ***topol;
	static double **len;
	FILE *prep;
	char c;
	int corestart, coreend;
	int alloclen;
	int winsize;
	char *pt, *ot;
	double gapmin;

	arguments( argc, argv );

	getnumlen( stdin );
	rewind( stdin );

	if( njob < 2 )
	{
		fprintf( stderr, "At least 2 sequences should be input!\n"
						 "Only %d sequence found.\n", njob ); 
		exit( 1 );
	}

	seq = AllocateCharMtx( njob, nlenmax*9+1 );
	name = AllocateCharMtx( njob, B+1 );
	oseq = AllocateCharMtx( njob, nlenmax*9+1 );
	alloclen = nlenmax*9;

	topol = AllocateIntCub( njob, 2, njob );
	len = AllocateDoubleMtx( njob, 2 );
	pscore = AllocateDoubleMtx( njob, njob );
	eff = AllocateDoubleVec( njob );
	node0 = AllocateDoubleMtx( njob, njob );
	node1 = AllocateDoubleMtx( njob, njob );
	gapc = AllocateDoubleVec( alloclen );
	avgap = AllocateDoubleVec( alloclen );

#if 0
	Read( name, nlen, seq );
#else
	readData_pointer( stdin, name, nlen, seq );
#endif

	constants( njob, seq );

#if 0
	fprintf( stderr, "params = %d, %d, %d\n", penalty, penalty_ex, offset );
#endif

	initSignalSM();

	initFiles();

	WriteOptions( trap_g );

	c = seqcheck( seq );
	if( c )
	{
		fprintf( stderr, "Illeagal character %c\n", c );
		exit( 1 );
	}

	writePre( njob, name, nlen, seq, 0 );

	if( tbutree == 0 )
	{
		for( i=1; i<njob; i++ ) 
		{
			if( nlen[i] != nlen[0] ) 
			{
				fprintf( stderr, "Input pre-aligned seqences or make hat2.\n" );
				exit( 1 );
			}
		}
		for( i=0; i<njob-1; i++ ) for( j=i+1; j<njob; j++ ) 
		{
		/*
			pscore[i][j] = (double)score_calc1( seq[i], seq[j] );
		*/
			pscore[i][j] = (double)substitution_hosei( seq[i], seq[j] );
		}
	}
	else
	{
		fprintf( stderr, "Loading 'hat2' ... " );
		prep = fopen( "hat2", "r" );
		if( prep == NULL ) ErrorExit( "Make hat2." );
		readhat2_pointer( prep, njob, name, pscore );
		fclose( prep );
		fprintf( stderr, "done.\n" );

#if 0
		prep = fopen( "hat2_check", "w" );
		WriteHat2( prep, njob, name, pscore );
		fclose( prep );
#endif

	}

	fprintf( stderr, "Constructing dendrogram ... " );
	if( treemethod == 'x' )
		supg( njob, pscore, topol, len );
	else if( treemethod == 's' )
		spg( njob, pscore, topol, len );
	else if( treemethod == 'p' )
		upg2( njob, pscore, topol, len );
	else 
		ErrorExit( "Incorrect tree\n" );
	fprintf( stderr, "done.\n" );

	countnode( njob, topol, node0 );
	if( tbrweight )
	{
		weight = 3; 
#if 0
		utree = 0; counteff( njob, topol, len, eff ); utree = 1;
#else
		counteff_simple( njob, topol, len, eff );
#endif
	}
	else
	{
		for( i=0; i<njob; i++ ) eff[i] = 1.0;
	}


	for( i=0; i<nlenmax; i++ )
	{
		gapc[i] = 0.0;
		for( j=0; j<njob; j++ )
		{
			if( seq[j][i] == '-' ) gapc[i] += eff[j];
		}
	}

	gapmin = 1.0;
	winsize = fftWinSize;
	goffset = winsize/2;
	tmpavgap = 0.0;
	corestart = coreend = -1;
	for( i=0; i<winsize; i++ )
	{
		tmpavgap += gapc[i];
	}
	for( i=winsize; i<nlenmax; i++ )
	{
		m = i - goffset;
		avgap[m] = tmpavgap / winsize;
//		fprintf( stdout, "%d %f %f\n", m, avgap[m], gapc[i] );
		if( avgap[m] < corethr )
		{
			if( corestart == -1 )
				corestart = i - winsize;
//			fprintf( stdout, "ok, gapmin = %f, corestart = %d, coreend = %d\n", gapmin, corestart, coreend );
			if( avgap[m] < gapmin )
			{ 
				gapmin = avgap[m];
			}
			coreend = i;
		}
		tmpavgap -= gapc[i-winsize];
		tmpavgap += gapc[i];
	}
	if( corestart == -1 || coreend == -1 )
	{
		corestart = 0;
		coreend = nlenmax-1;
	}

	for( i=0; i<njob; i++ )
	{
		pt = oseq[i];
		m = winsize;
		while( m-- ) *pt++ = '-';
		for( j=corestart; j<=coreend; j++ )
			*pt++ = seq[i][j];
		m = winsize;
		while( m-- ) *pt++ = '-';
		*pt = 0;

		ot = oseq[i]+winsize-1;
		pt = seq[i]+corestart-1;
		if( coreext ) m = winsize;
		else m = 0;
		while( m && --pt > seq[i] )
			if( *pt != '-' )
			{
				*ot-- = *pt;
				m--;
			}

		ot = oseq[i]+winsize+coreend-corestart+1;
		pt = seq[i]+coreend;
		if( coreext ) m = winsize;
		else m = 0;
		while( m && *(++pt) )
		{
			if( *pt != '-' ) 
			{
				*ot++ = *pt;
				m--;
			}
		}
		fprintf( stdout, ">%s\n", name[i] );
		fprintf( stdout, "%s\n", oseq[i] );
	}

	exit( 1 );

	SHOWVERSION;
	return( 0 );
}