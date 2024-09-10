bool
Aggregate::onLiteralFalse(
    Solver& solver,
    Literal currentLiteral,
    PropagatorData p )
{
    int position = p.position();
    assert_msg( abs( position ) > 0 && abs( position ) < static_cast< int >( literals.size() ), abs( position ) << " >= " << literals.size() );
    assert_msg( currentLiteral == ( position < 0 ? literals[ -position ].getOppositeLiteral() : literals[ position ] ), currentLiteral << " != " << ( position < 0 ? literals[ -position ].getOppositeLiteral() : literals[ position ] ) );
    trace_msg( aggregates, 10, "Aggregate: " << *this << ". Literal: " << currentLiteral.getOppositeLiteral() << " is true. Position: " << position );
    int ac = ( position < 0 ? POS : NEG );
    Literal aggrLiteral = ( ac == POS ? literals[ 1 ].getOppositeLiteral() : literals[ 1 ] );
    
    if( solver.isTrue( aggrLiteral ) || active + ac == 0 )
    {        
        trace_msg( aggregates, 2, "Return. AggrLiteral: " << aggrLiteral << " - Active: " << active << " - Ac: " << ac );
        return false;
    }
    
    unsigned int index = ( position > 0 ? position : -position ); 
    int64_t& counter = ( position > 0 ? counterW2 : counterW1 );

    trace_msg( aggregates, 2, "Updating counter. Old value: " << counter << " - New value: " << counter - weights[ index ] );
    
    if( counter < ( int64_t ) weights[ index ] )
    {
        assert_msg( solver.getDecisionLevel( currentLiteral ) == 0, "Literal " << currentLiteral << " in " << *this << " has a decision level " << solver.getDecisionLevel( currentLiteral ) );
        trace_msg( aggregates, 3, "A conflict happened." );        
        solver.assignLiteral( currentLiteral, this );
        return false;
    }
    assert( counter >= ( int64_t ) weights[ index ] );
    counter -= weights[ index ];
    watched[ index ] = false;
    
    if( solver.getDecisionLevel( currentLiteral ) != 0 )
        trail.push_back( position );

    trace_msg( aggregates, 2, "Umax: " << umax << " - size: " << size() );
    while( umax < literals.size() && ( int64_t ) weights[ umax ] > counter )
    {
        if( watched[ umax ] )
        {
            if( literalOfUnroll == Literal::null )
                literalOfUnroll = currentLiteral;
            active = ac;
            Literal lit = ( ac == POS ? literals[ umax ].getOppositeLiteral() : literals[ umax ] );
            if( !solver.isTrue( lit ) )
            {                
                //Maybe we don't need to add the position of this literal
                trail.push_back( umax * ac );
            
                trace_msg( aggregates, 9, "Inferring " << lit << " as true" );
//                createClauseFromTrail( lit );
                solver.assignLiteral( lit, this );
                if( solver.conflictDetected() )
                    return true;
            }
            else
            {
                trace_msg( aggregates, 9, "Skipping true literal " << lit );
            }
        }
        
        ++umax;
        trace_msg( aggregates, 3, "Updated umax. New Value: " << umax );        
    }
    
    return true;
}