// ---------------------------------------------------------------------------
// CBCTestHeadingPaneCase::TestHeadingPaneL
// ---------------------------------------------------------------------------
//
void CBCTestHeadingPaneCase::TestHeadingPaneL()
    {
    CEikFormattedCellListBox* listBox =
        new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listBox );

    CAknPopupList* popupList = CAknPopupList::NewL( listBox,
        R_AVKON_SOFTKEYS_SELECT_BACK,
        AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    AssertNotNullL( popupList, KAknPopupList );

    listBox->ConstructL( popupList, EAknListBoxMenuList );

    CAknPopupHeadingPane* head = new( ELeave ) CAknPopupHeadingPane();
    CleanupStack::PushL( head );
    AssertNotNullL( head, KAknPopupHeadingPane );
    head->SetContainerWindowL( *iContainer );

    TBufC<KFifteen> bufc( KHeading );
    TPtrC ptrc = bufc.Des();
    // Invoke CAknPopupHeadingPane's ConstructL()
    head->ConstructL( ptrc );
    AssertTrueL( ETrue, KConstructL );

    // Invoke CAknPopupHeadingPane's MinimumSize()
    TSize s = head->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );    

    // Invoke CAknPopupHeadingPane's HandlePointerEventL()
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    head->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );    

    // Invoke CAknPopupHeadingPane's SizeChanged()
    head->SizeChanged();
    AssertTrueL( ETrue, KSizeChanged );

    // Invoke CAknPopupHeadingPane's Prompt()
    head->Prompt();
    AssertTrueL( ETrue, KPrompt );

    // Invoke CAknPopupHeadingPane's PromptText()
    head->PromptText();
    AssertTrueL( ETrue, KPromptText );

    // Invoke CAknPopupHeadingPane's SetTextL()
    TBufC<KTwenty> otherBufc( KOtherHeading );
    TPtrC otherPtrc = otherBufc.Des();
    head->SetTextL( otherPtrc );
    AssertTrueL( ETrue, KSetTextL );

    // Invoke CAknPopupHeadingPane's SetLayout()
    head->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
    AssertTrueL( ETrue, KSetLayout );

    // Invoke CAknPopupHeadingPane's SetHeaderImageL()
    TBuf<KMaxFileName> iconFile;
    iContainer->GetCoeEnv()->ReadResource( iconFile, 
                                           R_BCTESTPOPUPS_ICONFILE );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image ); // image
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;
    AknIconUtils::CreateIconL( bitmap,
                               bitmapM,
                               iconFile,
                               EMbmBctestpopupsTel,
                               EMbmBctestpopupsTelm ); 

    CleanupStack::PushL( bitmap ); // bitmap
    CleanupStack::PushL( bitmapM ); // bitmap mask

    image->SetPictureOwnedExternally( TBool( 0 ) );
    image->SetPicture( bitmap, bitmapM );

    head->SetHeaderImageL( image );
    AssertTrueL( ETrue, KSetHeaderImageL );

    CleanupStack::Pop( bitmapM );  
    CleanupStack::Pop( bitmap );
    CleanupStack::Pop( image );

     // Invoke CAknPopupHeadingPane's SetSkinFrameId()
    TAknsItemID aknsItemID;
    head->SetSkinFrameId( aknsItemID );
    AssertTrueL( ETrue, KSetSkinFrameId );

     // Invoke CAknPopupHeadingPane's SetSkinFrameCenterId()
    head->SetSkinFrameCenterId( aknsItemID );
    AssertTrueL( ETrue, KSetSkinFrameCenterId );    
    
    // Invoke CAknPopupHeadingPane's SetHeaderAnimationL()
    head->SetHeaderAnimationL( R_BCTESTPOPUPS_BITMAP_ANIMATION );
    AssertTrueL( ETrue, KSetHeaderAnimationL );    

    // Invoke CAknPopupHeadingPane's StartAnimationL()
    head->StartAnimationL();
    AssertTrueL( ETrue, KStartAnimationL );

    // Invoke CAknPopupHeadingPane's CancelAnimation()
    head->CancelAnimation();
    AssertTrueL( ETrue, KCancelAnimation );
         
    CleanupStack::PopAndDestroy( head ); 
    head = NULL;

    head = new( ELeave ) CAknPopupHeadingPane();
    CleanupStack::PushL( head );

    // Invoke CAknPopupHeadingPane's ConstructFromResourceL()
    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC(
        reader, R_BCTESTPOPUPS_AVKON_HEADING );
    head->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader    

    CleanupStack::PopAndDestroy( head );    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    delete image;
    }