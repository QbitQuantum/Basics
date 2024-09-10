double MatCTECat( EXPR *name, EXPR *nothing )
    {
    char *string ;

    string = ExprValueString( name ) ;
    if( !string )
	{
	IOerror( MatBomb, "MatCTECat", "cannot evaluate name" ) ;
	return nan("") ;
	}
    return ExprValue( DbaseGetExpr( string, "CTE" ) ) ;
    }