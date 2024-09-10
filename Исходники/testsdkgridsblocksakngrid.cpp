// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleScrollEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetRect( iContainer->Rect() );
    
    CEikScrollBar *scrollbar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollbar );
    
    grid->HandleScrollEventL( scrollbar, EEikScrollLeft );
    grid->HandleScrollEventL( scrollbar, EEikScrollUp );
    grid->HandleScrollEventL( scrollbar, EEikScrollRight );
    grid->HandleScrollEventL( scrollbar, EEikScrollDown );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageLeft );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageUp );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageRight );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageDown );
    grid->HandleScrollEventL( scrollbar, EEikScrollHome );
    grid->HandleScrollEventL( scrollbar, EEikScrollTop );
    grid->HandleScrollEventL( scrollbar, EEikScrollEnd );
    grid->HandleScrollEventL( scrollbar, EEikScrollBottom );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbDragHoriz );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbDragVert );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbReleaseHoriz );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbReleaseVert );
    
    CleanupStack::PopAndDestroy( scrollbar );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }