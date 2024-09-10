// ---------------------------------------------------------------------------
//	merge	(STATIC)
// ---------------------------------------------------------------------------
//	Merge the Breakpoints in the specified iterator range into the
//	distilled Partial. The beginning of the range may overlap, and 
//	will replace, some non-zero-amplitude portion of the distilled
//	Partial. Assume that there is no such overlap at the end of the 
//	range (could check), because findContribution only leaves overlap
//  at the beginning of the range.
//
static void merge( Partial::const_iterator beg, 
				   Partial::const_iterator end, 
				   Partial & destPartial, double fadeTime, 
				   double gapTime = 0. )
{	
	//	absorb energy in distilled Partial that overlaps the
	//	range to merge:
	Partial toMerge( beg, end );
	toMerge.absorb( destPartial );  
    fadeInAndOut( toMerge, fadeTime );

		
    //  find the first Breakpoint in destPartial that is after the
    //  range of merged Breakpoints, plus the required gap:
	Partial::iterator removeEnd = destPartial.findAfter( toMerge.endTime() + gapTime );
    
    //  if this Breakpoint has non-zero amplitude, need to leave time
    //  for a fade in:
	while ( removeEnd != destPartial.end() &&
            removeEnd.breakpoint().amplitude() != 0 &&
            removeEnd.time() < toMerge.endTime() + gapTime + fadeTime )
    {
        ++removeEnd;
    }   
    
	//	find the first Breakpoint in the destination Partial that needs
    //  to be removed because it is in the overlap region:
	Partial::iterator removeBegin = destPartial.findAfter( toMerge.startTime() - gapTime );
        
    //  if beforeMerge has non-zero amplitude, need to leave time
    //  for a fade out:
    if ( removeBegin != destPartial.begin() )
	{
        Partial::iterator beforeMerge = --Partial::iterator(removeBegin);
        
        while ( removeBegin != destPartial.begin() &&
                beforeMerge.breakpoint().amplitude() != 0 &&
                beforeMerge.time() > toMerge.startTime() - gapTime - fadeTime )
        {
            --removeBegin;
            if ( beforeMerge != destPartial.begin() )
            {
                --beforeMerge;
            }
        }   
        
	}
	
	//	remove the Breakpoints in the merge range from destPartial:
    double rbt = (removeBegin != destPartial.end())?(removeBegin.time()):(destPartial.endTime());
    double ret = (removeEnd != destPartial.end())?(removeEnd.time()):(destPartial.endTime());
    Assert( rbt <= ret );
	destPartial.erase( removeBegin, removeEnd );

    //  how about doing the fades here instead?
    //  fade in if necessary:
	if ( removeEnd != destPartial.end() &&
         removeEnd.breakpoint().amplitude() != 0 )
	{
        Assert( removeEnd.time() - fadeTime > toMerge.endTime() );

        //	update removeEnd so that we don't remove this 
        //	null we are inserting:
        destPartial.insert( 
            removeEnd.time() - fadeTime, 
            BreakpointUtils::makeNullBefore( removeEnd.breakpoint(), fadeTime ) );
	}

    if ( removeEnd != destPartial.begin() )
    {
        Partial::iterator beforeMerge = --Partial::iterator(removeEnd);
        if ( beforeMerge.breakpoint().amplitude() > 0 )
        {
            Assert( beforeMerge.time() + fadeTime < toMerge.startTime() );
            
            destPartial.insert( 
                beforeMerge.time() + fadeTime, 
                BreakpointUtils::makeNullAfter( beforeMerge.breakpoint(), fadeTime ) );
        }
    }		
    
    //	insert the Breakpoints in the range:
	for ( Partial::const_iterator insert = toMerge.begin(); insert != toMerge.end(); ++insert )
	{
		destPartial.insert( insert.time(), insert.breakpoint() );
	}
}