// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::TestAknButtonSizeChangedL()
    {
    CTestButton* button = CTestButton::NewL();
    CleanupStack::PushL( button );
    button->SetButtonFlags( KAknButtonNoFrame );
    
    const TDesC text( KNullDesC );
    const TDesC helptext( KSimpleText );
    TFileName file( KMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    button->DoConstructLMoreComplexL( file, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, EMbmAvkonQgn_indi_mic,
        EMbmAvkonQgn_indi_mic_mask, text, helptext, KFlagOne );
    button->SetContainerWindowL( *this );
    button->SetRect( Rect() );
    button->DoSizeChanged();
    TSize size = button->MinimumSize();
    TInt err = KFlagZero;
    if( TSize( KFlagZero, KFlagZero ) == size )
        {
        button->SetButtonFlags( KAknButtonTextLeft );
        button->DoSizeChanged();
        size = button->MinimumSize();
        if( TSize( KFlagZero, KFlagZero ) == size )
            {
            err = KFlagOne;
            return err;
            }
        }
    else
        {
        err = KFlagOne;
        return err;
        }
    CleanupStack::PopAndDestroy( button );
    
    CTestButton* buttontwo = CTestButton::NewL();
    CleanupStack::PushL( buttontwo );
    buttontwo->ConstructFromResourceL( R_BUTTON );
    buttontwo->SetContainerWindowL( *this );
    buttontwo->SetRect( Rect() );
    buttontwo->DoSizeChanged();
    size = buttontwo->MinimumSize();
    if( TSize( KFlagZero, KFlagZero ) == size )
        {
        buttontwo->SetButtonFlags( KAknButtonTextLeft );
        buttontwo->DoSizeChanged();
        size = buttontwo->MinimumSize();
        if( TSize( KFlagZero, KFlagZero ) == size )
            {
            err = KFlagOne;
            return err;
            }
        }
    else
        {
        err = KFlagOne;
        return err;
        }
    CleanupStack::PopAndDestroy( buttontwo );
    return err;
    }