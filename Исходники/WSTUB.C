char *dos4g_path()
{
    static char fullpath[80];
    int i;
    
    for( i = 0;
         i < sizeof( paths_to_check ) / sizeof( paths_to_check[0] ); i++ ) {
	_searchenv( "dos4gw.exe", paths_to_check[i], fullpath );
	if( fullpath[0] ) return( &fullpath );
    }	
    return( "\dos4gw.exe" );
}