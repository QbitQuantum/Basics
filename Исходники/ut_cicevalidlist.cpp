void UT_CIceValidList::UT_CICEValidList_HasPairForComponentsL()
    {
    RArray<TUint> components;
    CleanupClosePushL( components );
    
    components.AppendL( 5 );
    EUNIT_ASSERT( 
        EFalse == iValidList->HasPairForComponents( components ) );
    
    UT_CICEValidList_AddValidPairLL();
    EUNIT_ASSERT( 
        EFalse == iValidList->HasPairForComponents( components ) );
    components.AppendL( KComponentIdRtp );
    EUNIT_ASSERT( 
        EFalse == iValidList->HasPairForComponents( components ) );
    components.Remove( 0 );
    EUNIT_ASSERT( 
        ETrue == iValidList->HasPairForComponents( components ) );
    
    components.Reset();
    EUNIT_ASSERT_PANIC( 
        iValidList->HasPairForComponents( components ), "USER", 0 );
    
    CleanupStack::PopAndDestroy( &components );
    }