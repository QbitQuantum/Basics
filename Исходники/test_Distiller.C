// ----------- test_collate -----------
//
static void test_collate( void )
{
    std::cout << "\t--- testing collate on three "
                 "temporally-overlapping Partials... ---\n\n";

    //  Fabricate three Partials, overlapping temporally, 
    //  leave them unlabeled, and distill (collate) them.
    Partial p1;
    p1.insert( 0, Breakpoint( 100, 0.4, 0, 0 ) );
    p1.insert( 0.3, Breakpoint( 110, 0.4, 0, .1 ) );
    p1.setLabel( 0 );
    
    Partial p2;
    p2.insert( 0.2, Breakpoint( 200, 0.3, 0, 0 ) );
    p2.insert( 0.35, Breakpoint( 210, 0.3, 0.2, .1 ) );
    p2.setLabel( 0 );

    Partial p3;
    p3.insert( 0.33, Breakpoint( 300, 0.3, 0, 0 ) );
    p3.insert( 0.4, Breakpoint( 310, 0.3, 0.2, .1 ) );
    p3.setLabel( 0 );

    PartialList l;
    l.push_back( p3 );
    l.push_back( p1 );
    l.push_back( p2 );

    const double fade = .01; // 10 ms
    Collator d( fade );
    d.collate( l );

    //  Fabricate the Partials that the distillation should 
    //  produce.
    Partial compare1;
    compare1.insert( 0, Breakpoint( 100, 0.4, 0, 0 ) );
    compare1.insert( 0.3, Breakpoint( 110, 0.4, 0, .1 ) );
    double t = 0.3 + fade;
    compare1.insert( t, Breakpoint( p1.frequencyAt(t), 0, 
                                    p1.bandwidthAt(t), p1.phaseAt(t) ) );
    t = 0.33 - fade;
    compare1.insert( t, Breakpoint( p3.frequencyAt(t), 0, 
                                    p3.bandwidthAt(t), p3.phaseAt(t) ) );
    compare1.insert( 0.33, Breakpoint( 300, 0.3, 0, 0 ) );
    compare1.insert( 0.4, Breakpoint( 310, 0.3, 0.2, .1 ) );
    compare1.setLabel(1);

    Partial compare2 = p2;
    compare2.setLabel(2);
    
    //  compare Partials, the first one will be
    //  the one that was constructed from the 
    //  Partial with the earliest end (p1):
    TEST( l.size() == 2 );
    PartialList::iterator it = l.begin();
    TEST( it->label() == compare1.label() );
    TEST( it->numBreakpoints() == compare1.numBreakpoints() );
    
    Partial::iterator distit = it->begin();
    Partial::iterator compareit = compare1.begin();
    while ( compareit != compare1.end() )
    {
        SAME_PARAM_VALUES( distit.time(), compareit.time() );
        SAME_PARAM_VALUES( distit->frequency(), compareit->frequency() );
        SAME_PARAM_VALUES( distit->amplitude(), compareit->amplitude() );
        SAME_PARAM_VALUES( distit->bandwidth(), compareit->bandwidth() );
        SAME_PARAM_VALUES( distit->phase(), compareit->phase() );
        
        ++compareit;
        ++distit;
    }
    
    ++it;
    TEST( it->numBreakpoints() == compare2.numBreakpoints() );
    TEST( it->label() == compare2.label() );
    distit = it->begin();
    compareit = compare2.begin();
    while ( compareit != compare2.end() )
    {
        SAME_PARAM_VALUES( distit.time(), compareit.time() );
        SAME_PARAM_VALUES( distit->frequency(), compareit->frequency() );
        SAME_PARAM_VALUES( distit->amplitude(), compareit->amplitude() );
        SAME_PARAM_VALUES( distit->bandwidth(), compareit->bandwidth() );
        SAME_PARAM_VALUES( distit->phase(), compareit->phase() );
        
        ++compareit;
        ++distit;
    }
}