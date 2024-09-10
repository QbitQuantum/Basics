void CMMABitmapWindow::SetDestinationBitmapL(CFbsBitmap* aBitmap)
{
    CFbsBitmap* bitmap = new(ELeave)CFbsBitmap();
    CleanupStack::PushL(bitmap);
    User::LeaveIfError(bitmap->Duplicate(aBitmap->Handle()));

    // create context for bitmap
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(aBitmap);
    CleanupStack::PushL(bitmapDevice);


    CGraphicsContext* bitmapContext = NULL;
    User::LeaveIfError(bitmapDevice->CreateContext(bitmapContext));

    CleanupStack::Pop(bitmapDevice);   // bitmapDevice
    CleanupStack::Pop(bitmap);   // bitmap

    delete iBitmap;
    iBitmap = bitmap;
    delete iBitmapDevice;
    iBitmapDevice = bitmapDevice;
    delete iBitmapContext;
    iBitmapContext = bitmapContext;

    if (iDrawRect.IsEmpty())
    {
        iDrawRect.SetSize(iBitmap->SizeInPixels());
    }
}