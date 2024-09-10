ECode COverlayFrame::GenerateOverlayWithRenderingMode(
    /* [in] */ IMediaItem* mediaItemsList,
    /* [in] */ IOverlayFrame* overlay,
    /* [in] */ Int32 height,
    /* [in] */ Int32 width)
{
    AutoPtr<IMediaItem> t = mediaItemsList;

    /* get the rendering mode */
    Int32 renderMode;
    t->GetRenderingMode(&renderMode);

    AutoPtr<IBitmap> overlayBitmap;
    overlay->GetBitmap((IBitmap**)&overlayBitmap);

    /*
     * Check if the resize of Overlay is needed with rendering mode applied
     * because of change in export dimensions
     */
    Int32 resizedRGBFileHeight;
    ((COverlayFrame*)overlay)->GetResizedRGBSizeHeight(&resizedRGBFileHeight);
    Int32 resizedRGBFileWidth;
    ((COverlayFrame*)overlay)->GetResizedRGBSizeWidth(&resizedRGBFileWidth);

    /* Get original bitmap width if it is not resized */
    if(resizedRGBFileWidth == 0) {
        overlayBitmap->GetWidth(&resizedRGBFileWidth);
    }
    /* Get original bitmap height if it is not resized */
    if(resizedRGBFileHeight == 0) {
        overlayBitmap->GetHeight(&resizedRGBFileHeight);
    }

    String name;
    ((COverlayFrame*)overlay)->GetFilename(&name);
    AutoPtr<IFile> file;
    CFile::New(name, (IFile**)&file);
    Boolean b;
    file->Exists(&b);

    if (resizedRGBFileWidth != width || resizedRGBFileHeight != height || (!b)) {
        /*
         *  Create the canvas bitmap
         */
        AutoPtr<IBitmapFactory> bitmapFactory;
        CBitmapFactory::AcquireSingleton((IBitmapFactory**)&bitmapFactory);
        AutoPtr<IBitmap> destBitmap;
        bitmapFactory->CreateBitmap(width, height, Elastos::Droid::Graphics::BitmapConfig_ARGB_8888, (IBitmap**)&destBitmap);

        AutoPtr<ICanvas> overlayCanvas;
        CCanvas::New(destBitmap, (ICanvas**)&overlayCanvas);
        AutoPtr<IRect> destRect;
        AutoPtr<IRect> srcRect;

        Int32 canvasWidth, canvasHeight;
        overlayCanvas->GetWidth(&canvasWidth);
        overlayCanvas->GetHeight(&canvasHeight);
        Int32 bitmapWidth, bitmapHeight;
        overlayBitmap->GetWidth(&bitmapWidth);
        overlayBitmap->GetHeight(&bitmapHeight);
        switch (renderMode) {
            case IMediaItem::RENDERING_MODE_STRETCH: {
                CRect::New(0, 0, canvasWidth, canvasHeight, (IRect**)&destRect);
                CRect::New(0, 0, bitmapWidth, bitmapHeight, (IRect**)&srcRect);
                break;
            }

            case IMediaItem::RENDERING_MODE_BLACK_BORDER: {
                Int32 left, right, top, bottom;
                Float aROverlayImage, aRCanvas;
                aROverlayImage = (Float)bitmapWidth /
                                 (Float)bitmapHeight;

                aRCanvas = (Float)canvasWidth /
                                 (Float)canvasHeight;

                if (aROverlayImage > aRCanvas) {
                    Int32 newHeight = ((canvasWidth * bitmapHeight)
                                     / bitmapWidth);
                    left = 0;
                    top  = (canvasHeight - newHeight) / 2;
                    right = canvasWidth;
                    bottom = top + newHeight;
                }
                else {
                    Int32 newWidth = ((canvasHeight * bitmapWidth)
                                        / bitmapHeight);
                    left = (canvasWidth - newWidth) / 2;
                    top  = 0;
                    right = left + newWidth;
                    bottom = canvasHeight;
                }

                CRect::New(left, top, right, bottom, (IRect**)&destRect);
                CRect::New(0, 0, bitmapWidth, bitmapHeight, (IRect**)&srcRect);
                break;
            }

            case IMediaItem::RENDERING_MODE_CROPPING: {
                // Calculate the source rect
                Int32 left, right, top, bottom;
                Float aROverlayImage, aRCanvas;
                aROverlayImage = (Float)(bitmapWidth) /
                                 (Float)(bitmapHeight);
                aRCanvas = (Float)(canvasWidth) /
                                (Float)(canvasHeight);
                if (aROverlayImage < aRCanvas) {
                    Int32 newHeight = ((bitmapWidth * canvasHeight)
                               / canvasWidth);

                    left = 0;
                    top  = (bitmapHeight - newHeight) / 2;
                    right = bitmapWidth;
                    bottom = top + newHeight;
                }
                else {
                    Int32 newWidth = ((bitmapHeight * canvasWidth)
                                / canvasHeight);
                    left = (bitmapWidth - newWidth) / 2;
                    top  = 0;
                    right = left + newWidth;
                    bottom = bitmapHeight;
                }

                CRect::New(left, top, right, bottom, (IRect**)&srcRect);
                CRect::New(0, 0, canvasWidth, canvasHeight, (IRect**)&destRect);
                break;
            }

            default: {
                // throw new IllegalStateException("Rendering mode: " + renderMode);
                return E_ILLEGAL_STATE_EXCEPTION;
            }
        }

        overlayCanvas->DrawBitmap(overlayBitmap, srcRect, destRect, sResizePaint);
        overlayCanvas->SetBitmap(NULL);

        /*
         * Write to the dest file
         */
        String outFileName;
        ((COverlayFrame*)overlay)->GetFilename(&outFileName);

        /*
         * Save the image to same rgb file
         */
        if (outFileName != NULL) {
            AutoPtr<IFile> file;
            CFile::New(outFileName, (IFile**)&file);
            Boolean b;
            file->Delete(&b);
        }

        AutoPtr<IFileOutputStream> fl;
        CFileOutputStream::New(outFileName, (IFileOutputStream**)&fl);
        AutoPtr<IDataOutputStream> dos;
        CDataOutputStream::New(fl, (IDataOutputStream**)&dos);

        /*
         * Populate the rgb file with bitmap data
         */
        AutoPtr<ArrayOf<Int32> > framingBuffer = ArrayOf<Int32>::Alloc(width);
        AutoPtr<IByteBuffer> byteBuffer;
        AutoPtr<IByteBufferHelper> helper;
        CByteBufferHelper::AcquireSingleton((IByteBufferHelper**)&helper);
        helper->Allocate(framingBuffer->GetLength() * 4, (IByteBuffer**)&byteBuffer);
        AutoPtr<IInt32Buffer> intBuffer;

        AutoPtr<ArrayOf<Byte> > array;
        byteBuffer->GetArray((ArrayOf<Byte>**)&array);
        Int32 tmp = 0;
        while(tmp < height) {
            destBitmap->GetPixels(*framingBuffer, 0, width, 0, tmp, width, 1);
            byteBuffer->AsInt32Buffer((IInt32Buffer**)&intBuffer);
            intBuffer->PutInt32s(*framingBuffer, 0, width);
            dos->WriteBytes(*array);
            tmp += 1;
        }
        IFlushable::Probe(fl)->Flush();
        fl->Close();

        /*
         * Set the resized RGB width and height
         */
        ((COverlayFrame*)overlay)->SetResizedRGBSize(width, height);
    }
    return NOERROR;
}