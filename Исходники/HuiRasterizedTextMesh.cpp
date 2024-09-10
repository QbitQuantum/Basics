TBool CHuiRasterizedTextMesh::RasterizePictographLineL(const TDesC& aTextLine, CFont* aFont, SRasterizedLine & aLineOut)
    {
    if(iUsingPreRasterizedMesh)
        {
        return EFalse;
        }

    // Retrieve the used text style.
    THuiTextStyle* textStyle = CHuiStatic::Env().TextStyleManager().TextStyle(iTextStyleId);
    
    // Calculate line extents and assign it to texture size.
    TSize textureSize = textStyle->LineExtentsL(aTextLine);
	    
    if(textureSize.iWidth == 0 || !iPictographInterface || !iPictographInterface->Interface()->ContainsPictographs(aTextLine))
        {
        // This is an empty string or it does not contain pictographs. We will not rasterize it.
        // Just add a gap.
        aLineOut.iTexture = NULL;
        aLineOut.iGap = textureSize.iHeight;
        return !IsMaxLineCountReached(); 
        }

    // store the actual size to be assigned as the textures logical size
    TSize actualsize(textureSize);

    if (aLineOut.iTexture == NULL)
        {
    // Create a texture for storing the pictographs into.
        aLineOut.iTexture = CHuiTexture::NewL();
        HUI_DEBUG1(_L("CHuiRasterizedTextMesh::RasterizePictographLineL() - Registering self (0x%x) as a texture content observer."), this);        
        // Register one content observer for the first texture that
        // is able to restore all lines in a single run
        if (iLines.Count()==1)
            {
            aLineOut.iTexture->iContentObservers.AppendL(*this);
            }
        aLineOut.iGap = 0;
        }

    // set a name for the texture
    // @todo is this needed, what names to use
    aLineOut.iTexture->SetImageFileNameL(_L("Pictographs"));

    TSize maxTextureSize = aLineOut.iTexture->MaxTextureSize();
    textureSize.iWidth = Min(textureSize.iWidth, maxTextureSize.iWidth);
    textureSize.iHeight = Min(textureSize.iHeight, maxTextureSize.iHeight);

    if((textureSize.iWidth == 0) || (textureSize.iHeight == 0))
        {
        // Cannot draw into this tiny texture, so leave.
        HUI_DEBUG2(_L("CHuiRasterizedTextMesh::RasterizePictographLineL() - texture size was too small to draw into (%i, %i)."), textureSize.iWidth, textureSize.iHeight);
        User::Leave(KErrAbort);
        }

    User::LeaveIfError( iPictographBitmap->Resize(textureSize) );

    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(iPictographBitmap);
    CleanupStack::PushL(device);

    CFbsBitGc* gc = 0;
    User::LeaveIfError( device->CreateContext(gc) );
    CleanupStack::PushL(gc);

    // Prepare the bitmap for drawing...set drawmode because of EColor16MA mode...
    gc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha); 

    TRgb color = KRgbWhite;
    color.SetAlpha(0x00);
    gc->SetBrushColor(color);
    gc->Clear();
    gc->UseFont(aFont);  
    
	// Draw pictorgraphs
    iPictographInterface->Interface()->DrawPictographsInText(
            *gc,
            *aFont,
            aTextLine, TPoint(0, aFont->FontMaxAscent()));

    CleanupStack::PopAndDestroy(gc);
    CleanupStack::PopAndDestroy(device);

    aLineOut.iTexture->UploadL(*iPictographBitmap, NULL, EHuiTextureUploadFlagRetainResolution);
    aLineOut.iTexture->SetSize(actualsize);
    return !IsMaxLineCountReached();
    }