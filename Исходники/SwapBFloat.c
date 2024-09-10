int main( int argc, char **argv)
{
/*  sample command lines
-i bdv.bshort -o junk.bshort -V -# 16
*/
	OSErr   error = noErr;
	static  char id[] = "$Revision: 1.2 $$Date: 2002/09/10 22:06:02 $";
	char    headerName[ NAME_SIZE ];
	char    *extension;
	char    ofName[ NAME_SIZE ];
	int     OutOrder;

	error = ProcessCommandLine( argc, argv );
	ILError( error, "error in command line" );

	extension = strrchr( u.InFileName, '.' );
	if( !strlen(extension) ) {
		printf( "Input file name error\n" );
		return 0;
	}
	if( !equalString( extension, ".bfloat" )) {
		printf( "This utility works only on bfloat images!\n" );
		return 0;
	}

//	strcpy( headerName, u.InFileName, NAME_SIZE );
	strcpy( headerName, u.InFileName ); //zrinka 09/10/02
	
	extension = strrchr( headerName, '.' );
	if( !strlen(extension) ) {
		printf( "Input file name error\n" );
		return 0;
	}
	sprintf( extension, ".hdr" );
	u.inFile = errfopen( headerName, "r" );
	
	fscanf( u.inFile, "%d%d%d%d", &u.id.ys, &u.id.xs, &u.id.zs, &u.id.ByteOrder );
//	error = ck_fclose( u.inFile, "input header" );
	error = ck_fclose( u.inFile ); //zrinka 09/10/02
	
	u.inFile  =  errfopen( u.InFileName,  "rb" );

	strcpy( ofName, u.OutFileName );
	strcat( ofName, ".bfloat" );
	u.outFile =  errfopen( ofName, "wb" );

	error = DoSwap( u.inFile, u.outFile );
	ILError( error, argv[0] );

	error = ck_fclose( u.inFile );
	ILError( error, "infile" );

	error = ck_fclose( u.outFile );
	ILError( error, "infile" );

	strcpy( ofName, u.OutFileName );
	strcat( ofName, ".hdr" );
	u.outFile = errfopen( ofName, "w" );
	if( u.id.ByteOrder == 1 ) {	// pc-dec bytOrder
		OutOrder = 0;
	} else {
		OutOrder = 1;
	}

	fprintf( u.outFile, "%d %d %d %d", u.id.ys, u.id.xs, u.id.zs, OutOrder );
	error = ck_fclose( u.outFile );
	ILError( error, "main" );
}