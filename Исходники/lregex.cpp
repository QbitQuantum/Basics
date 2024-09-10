void LiLFeSRegEx::addFlags( FSP arg ) {
  while ( arg.GetType() != nil ) {
    if ( arg.GetType() == cons ) {
      FSP p = arg.Follow( hd );
      arg = arg.Follow( tl );
      if ( p.IsString() ) {
	const char* option = p.ReadString();
	if ( strcmp( option, "ICASE" ) == 0 ) {
	  cflags |= REG_ICASE;
        } else if ( strcmp( option, "i" ) == 0 ) {
          cflags |= REG_ICASE;
	} else if ( strcmp( option, "NEWLINE" ) == 0 ) {
	  cflags |= REG_NEWLINE;
	} else if ( strcmp( option, "NOTBOL" ) == 0 ) {
	  eflags |= REG_NOTBOL;
	} else if ( strcmp( option, "NOTEOL" ) == 0 ) {
	  eflags |= REG_NOTEOL;
	} else if ( strcmp( option, "GLOBAL" ) == 0 ) {
          global = true;
        } else if ( strcmp( option, "g" ) == 0 ) {
          global = true;
        } else {
	  string msg( "Invalid option for regex: " );
	  msg.append( option );
	  throw LiLFeSRegExError( msg );
	}
      } else {
	throw LiLFeSRegExError( "regex: Option must be specified with string" );
      }
    } else {
      throw LiLFeSRegExError( "regex: Option must be specified with string" );
    }
  }
}