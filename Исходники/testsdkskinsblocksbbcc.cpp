// -----------------------------------------------------------------------------
// CTestSDKSkins::TestBBCCSetRectL
// -----------------------------------------------------------------------------
TInt CTestSDKSkins::TestBBCCSetRectL( CStifItemParser& /*aItem*/ )
    {
    TAknsItemID itemID;
    TPoint pointTL( 0, 0 );
    TPoint pointBR( KLength, KLength );
    TRect rect( pointTL, pointBR );
    CAknsBasicBackgroundControlContext* context = 
        CAknsBasicBackgroundControlContext::NewL( itemID, rect, ETrue );
    CleanupStack::PushL( context );
    STIF_ASSERT_NOT_NULL( context );
    
    context->SetRect( rect );
    
    CleanupStack::PopAndDestroy( context );
    
    return KErrNone;
    
    }