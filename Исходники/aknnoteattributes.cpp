void CAknNoteAttributes::SetAnimationBackGroundFrameL()
{
    // R_QGN_GRAF_WAIT_BAR_ANIM case is OK without background frame.
    if (iAnimation && iAnimationID != R_QGN_GRAF_WAIT_BAR_ANIM)
    {
        // Not set background frame, if there is only one frame in animation.
        CBitmapAnimClientData *animClientData = iAnimation->BitmapAnimData();
        if (animClientData != NULL && animClientData->FrameArray().Count() <= 1)
        {
            return;
        }

        const TDisplayMode displayMode( CCoeEnv::Static()->ScreenDevice()->DisplayMode() );

        // Create skinned background frame

        CFbsBitmap* bitmap = new(ELeave) CFbsBitmap;
        CleanupStack::PushL(bitmap);

        User::LeaveIfError( bitmap->Create( iAnimation->Rect().Size(), displayMode ) );

        CFbsBitmapDevice* doubleBufferDev = CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL(doubleBufferDev);

        CFbsBitGc* doubleBufferGc = 0;
        User::LeaveIfError( doubleBufferDev->CreateContext( doubleBufferGc ) );
        CleanupStack::PushL(doubleBufferGc);

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = iBgContext;

        AknsDrawUtils::DrawBackground( skin, cc, iNoteControl, *doubleBufferGc,
                                       TPoint(0,0), iAnimation->Rect(), KAknsDrawParamDefault );
#if 0
        // waitbar background border
        if ( iAnimationID == R_QGN_GRAF_WAIT_BAR_ANIM )
        {
            CFbsBitmap* frameL = NULL;
            CFbsBitmap* frameCenter = NULL;
            CFbsBitmap* frameR = NULL;
            CFbsBitmap* lMask = NULL;
            CFbsBitmap* centerMask = NULL;
            CFbsBitmap* rMask = NULL;

            AknIconUtils::CreateIconLC( frameL, lMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_side_l, EMbmAvkonQgn_graf_bar_frame_side_l_mask  );
            AknIconUtils::CreateIconLC( frameCenter, centerMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_center, EMbmAvkonQgn_graf_bar_frame_center_mask);
            AknIconUtils::CreateIconLC( frameR, rMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_side_r, EMbmAvkonQgn_graf_bar_frame_side_r_mask  );

            TAknLayoutRect frameGraphicLayout;

            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g1() );
            User::LeaveIfError( AknIconUtils::SetSize( frameL, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );

            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g2() );
            User::LeaveIfError( AknIconUtils::SetSize( frameCenter, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );

            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g3() );
            User::LeaveIfError( AknIconUtils::SetSize( frameR, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );

            TPoint centerPoint( frameL->SizeInPixels().iWidth, 0 );
            TPoint rightPoint( centerPoint.iX + frameCenter->SizeInPixels().iWidth, 0 );

            doubleBufferGc->BitBltMasked( TPoint( 0, 0), frameL,
                                          TRect( TPoint( 0, 0 ), frameL->SizeInPixels() ),
                                          lMask, EFalse );

            doubleBufferGc->BitBltMasked( centerPoint, frameCenter,
                                          TRect( frameCenter->SizeInPixels() ),
                                          centerMask, EFalse );

            doubleBufferGc->BitBltMasked( rightPoint, frameR,
                                          TRect( frameR->SizeInPixels() ),
                                          rMask, EFalse );

            CleanupStack::PopAndDestroy( 6 );
            if ( iAnimation->BitmapAnimData()->PlayMode() == CBitmapAnimClientData::EPlay )
                iAnimation->BitmapAnimData()->SetPlayMode(CBitmapAnimClientData::ECycle);
        }
#endif

        CleanupStack::PopAndDestroy(2); // doubleBufferGc, doubleBufferDev

        // finally set background frame
        CBitmapFrameData* data = CBitmapFrameData::NewL();
        data->SetBitmapsOwnedExternally( EFalse );
        data->SetBitmap( bitmap );

        // Set frame to animation
        iAnimation->BitmapAnimData()->SetBackgroundFrame( data ); // gets ownership

        CleanupStack::Pop(bitmap); // bitmap
    }
}