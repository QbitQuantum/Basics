void CMMADisplay::SourceSizeChanged(const TSize& aSourceSize)
{
    LOG(EJavaMMAPI,EInfo,"CMMADisplay::SourceSizeChanged");

#ifdef RD_JAVA_NGA_ENABLED
    if (iWindow)
    {
        iWindow->SetVideoCropRegion(TRect(iUserRect.iTl, aSourceSize));
    }
#endif

    iSourceSize = aSourceSize;
    LOG1(EJavaMMAPI,EInfo,"MMA::CMMADisplay::SourceSizeChanged %d",
         aSourceSize.iWidth);
    LOG1(EJavaMMAPI,EInfo,"MMA::CMMADisplay::SourceSizeChanged %d",
         aSourceSize.iHeight);
    jmethodID getDisplayWidthID = iJni->GetMethodID(
                                      iJavaDisplayClass,
                                      "getDisplayWidth",
                                      "()I");

    jmethodID getDisplayHeightID = iJni->GetMethodID(
                                       iJavaDisplayClass,
                                       "getDisplayHeight",
                                       "()I");


    TInt x =  iJni->CallIntMethod(iJavaDisplayObject,getDisplayWidthID);
    TInt y = iJni->CallIntMethod(iJavaDisplayObject,getDisplayHeightID);
    LOG2(EJavaMMAPI,EInfo,"CMMADisplay.cpp : SourceSizeChanged () iFullScreenSize is x = %d ,y = %d ",x,y);
    // get the ScreenSize from canvas in java
    TSize canvasSize(x, y);
    iFullScreenSize = canvasSize;
    TBool sourceIsBigger = (aSourceSize.iWidth > iFullScreenSize.iWidth ||
                            aSourceSize.iHeight > iFullScreenSize.iHeight);

    if (sourceIsBigger)
    {
        // Source is larger than display area.
        // Shrink draw are to fit in display.
        iWindow->SetDrawRect(ScaleToFullScreen(iFullScreenSize, iSourceSize));
    }
    else
    {
        // source is smaller than display area
        iWindow->SetDrawRect(TRect(iUserRect.iTl, iSourceSize));
    }

    SetClippingRegion();

    if (iUserRect.IsEmpty())
    {
        // Java side hasn't set size.
        iUserRect = iWindow->DrawRect();

        if (!sourceIsBigger)
        {
            // Addjusting rect to top left corner.
            iUserRect = TRect(iUserRect.Size());
        }
    }
}