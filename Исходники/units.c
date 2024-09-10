EXPR *ExprFindCommensurate( EXPR *expr )
    {
    unsigned int i, j ;
    EXPR *tmp, *tmp2 ;

    for( i = 0 ; i < U(UnitList)->used ; i++ )
	{
	if( U(UN(i))->used != U(expr)->used )
	    continue ;
	for( j = 1 ; j < U(expr)->used ; j++ )
	    {
	    if( !BooleanValue( (BOOL*) OP3( "?=", U(UN(i))->list[j], U(expr)->list[j] ) ) )
		break ;
	    }
	if( j == U(expr)->used )			/* found one */
	    {
	    tmp = OP3( "/", U(expr)->list[0], U(UN(i))->list[0] ) ;
	    tmp2 = Real( MAGNITUDE( tmp ), i ) ;
	    delete tmp ;
	    delete expr ;
	    return tmp2 ;
	    }
	}

    for( i = 1 ; i < U(expr)->used ; i++ )
	{
	if( IS_ZERO( U(expr)->list[i] ) )
	    continue ;
	if( MAGNITUDE( U(expr)->list[i] ) == 1.0 )
	    tmp = U(UN(i))->Ehead->Copy() ;
	else
	    {
	    tmp = Operator( OPER_POW ) ;
	    D(tmp)->Eleft = U(UN(i))->Ehead->Copy() ;
	    D(tmp)->Eright = U(expr)->list[i]->Copy() ;
	    }
	if( U(expr)->Eeval )
	    {
	    tmp2 = Operator( OPER_MULTIPLY ) ;
	    D(tmp2)->Eleft = U(expr)->Eeval ;
	    D(tmp2)->Eright = tmp ;
	    U(expr)->Eeval = tmp2 ;
	    }
	else
	    U(expr)->Eeval = tmp ;
	}

    tmp = Real( MAGNITUDE( U(expr)->list[0] ), U(UnitList)->used ) ;
    delete U(expr)->list[0] ;
    U(expr)->list[0] = Real(1,0) ;
    ListAppend( UnitList, expr ) ;
    return tmp ;
    }