class CFbsBitmap* WFBitmapUtil::CopyBitmapL(class CFbsBitmap* aBitmap)
{
   if (!aBitmap) {
      return NULL;
   }
   class CFbsBitmap* copiedBitmap = new (ELeave) CFbsBitmap();
   copiedBitmap->Create(aBitmap->SizeInPixels(), aBitmap->DisplayMode());

   CFbsBitmapDevice* fbsdev = CFbsBitmapDevice::NewL(copiedBitmap);
   CleanupStack::PushL(fbsdev);
   CFbsBitGc* fbsgc = CFbsBitGc::NewL();
   CleanupStack::PushL(fbsgc);
   fbsgc->Activate(fbsdev);
   fbsgc->BitBlt(TPoint(0,0),aBitmap);
   CleanupStack::PopAndDestroy(2);
   return copiedBitmap;
}