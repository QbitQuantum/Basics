// -----------------------------------------------------------------------------
// CSkinningModule::TestCaseBasicBackgroundControlContextOpsL
// Basic background context operations.
// -----------------------------------------------------------------------------
//
TInt CSkinningModule::TestCaseBasicBackgroundControlContextOpsL( TTestResult& aResult )
    {
    TInt err = KErrNone;

    TRect initialRect( TSize( 100, 100 ) );
    TRect nextRect( TSize( 50, 50 ) );
    TAknsItemID id = KAknsIIDQsnCpClockAnalogueFace1;
    TAknsItemID id2 = KAknsIIDQsnCpClockAnalogueFace2;

    CAknsBasicBackgroundControlContext* myCtx =
        CAknsBasicBackgroundControlContext::NewL( id, initialRect, EFalse );
    CleanupStack::PushL( myCtx );

    myCtx->SetBitmap( id2 );
    myCtx->SetRect( nextRect );
    myCtx->SetParentPos( TPoint( 0,0 ) );
    myCtx->SetParentContext( NULL );

    if ( !myCtx->IsCompatibleWithType( EAknsControlContextTypeBasic ) ||
         !myCtx->IsCompatibleWithType( EAknsControlContextTypeUnknown ) ||
         myCtx->IsCompatibleWithType( EAknsControlContextTypeLayered ) ||
         myCtx->IsCompatibleWithType( EAknsControlContextTypeListBox ) ||
         myCtx->IsCompatibleWithType( EAknsControlContextTypeFrame ))
        {
        err = KErrGeneral;
        }

    CleanupStack::PopAndDestroy( myCtx );

    // Sets test case result and description(Maximum size is KStifMaxResultDes)
    _LIT( KDescription, "BasicBackgroundControlContextOps finished" );
    aResult.SetResult( err, KDescription );
    return err;
    }