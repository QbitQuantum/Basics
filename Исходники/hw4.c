int main ( int argc, char **argv )
{
	Argvs cmd = ParseCommandLine ( argc, argv );
	if ( cmd.mode == OP_KEYGEN ) {
		if ( keygen ( cmd.t ) != 0 ) {
			printerror ( "Unknown keygen error" );
		}
	} else if ( cmd.mode == OP_CRYPT ) {
		if ( crypt ( cmd.file1, cmd.file2 ) != 0 ) {
			printerror ( "Unknown crypt error" );
		}
		free ( cmd.file1 );
		free ( cmd.file2 );
	} else if ( cmd.mode == OP_INVKEY ) {
		if ( invkey ( cmd.file1 ) != 0 ) {
			printerror ( "unknown invkey error" );
		}
		free ( cmd.file1 );
	} else if ( cmd.mode == OP_HISTO ) {
		if ( histo ( cmd.t, cmd.i, cmd.file1 ) != 0 ) {
			printerror ( "unknown histo error" );
		}
		free ( cmd.file1 );
	} else if ( cmd.mode == OP_SOLVE ) {
		if ( solve ( cmd.l, cmd.file1 ) != 0 ) {
			printerror ( "unknown solve error" );
		}
		free ( cmd.file1 );
	}
	return 0;
}