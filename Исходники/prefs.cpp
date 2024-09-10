void Prefs::open(){

	char *p;//=getenv( "blitzpath" );
	size_t len;
	errno_t err=_dupenv_s( &p,&len,"blitzpath" );
	if( err ){
		AfxMessageBox( "blitzpath environment variable not found!",MB_TOPMOST|MB_SETFOREGROUND|MB_ICONINFORMATION );
		ExitProcess(0);
	}

	homeDir=p;
	free( p );

	AddFontResource( (homeDir+"/cfg/blitz.fon").c_str() );

	setDefault();

	bool prg_windowed;

	ifstream in( (homeDir+"/cfg/blitzide.prefs").c_str() );
	if( !in.good() ) return;

	while( !in.eof() ){
		string t;in>>t;
		if( !t.size() ) continue;
		while( in.peek()=='\t' ) in.ignore();
		if( t=="prg_debug" ) in>>prg_debug;
		else if( t=="prg_lastbuild" ) getline( in,prg_lastbuild );
		else if( t=="prg_windowed" ) in>>prg_windowed;
		else if( t=="win_maximized" ) in>>win_maximized;