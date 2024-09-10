void S60ImageUtil::calculateVisibleRect(Image* aImage)
{
   if (aImage->iHasMask) {
      CFbsBitmap* mask = aImage->GetMask();
      TInt xmin = aImage->iWidth;
      TInt xmax = 0;
      TInt ymin = aImage->iHeight;
      TInt ymax = 0;
#if defined USE_AKN_LIB
      //Iterating the pixels with GetPixel() works for sure on all symbian,
      //but it's pretty slow and we have to look at every one pixel.
      //On a 800 x 800 image we do 640 000 GetPixel() iterations.
      TRgb color;
      TRgb white(255, 255, 255);
      for (TInt y = 0; y < aImage->iHeight; y++) {
         for (TInt x = 0; x < aImage->iWidth; x++) {
            mask->GetPixel(color, TPoint(x, y));
            if (color == white) {
               if (xmin > x) {
                  xmin = x;
               }
               if (xmax < x) {
                  xmax = x;
               }
               if (ymin > y) {
                  ymin = y;
               }
               if (ymax < y) {
                  ymax = y;
               }
            }
         }
      }
#else
      //Iterating the pixels by hand in memory probably works on all symbian,
      //it's much faster since we look at 8 pixels at a time, 
      //It needs some testing and verification.
      //On a 800 x 800 image we do roughly 83 000 iterations.
      TDisplayMode dMode = mask->DisplayMode();
      if (dMode == EGray2) {
# ifndef NAV2_CLIENT_SERIES60_V1
         mask->LockHeap();
# endif
         TUint32* imgPtr = mask->DataAddress();
         TSize imgSize = mask->SizeInPixels();
         TInt imgByteWidth = imgSize.iWidth >> 3;
         TInt imgBitsLeft = imgSize.iWidth % 8;
         TInt lineLength = CFbsBitmap::ScanLineLength(imgSize.iWidth, dMode);
         TUint8* pCurrByteLine = (TUint8*) imgPtr;
         TUint8 currByte;
         TInt currXPixelOffset;
         TInt currXPixel;
         for (TInt y = 0; y < imgSize.iHeight; y++) {
            for (TInt x = 0; x < imgByteWidth; x++) {
               currByte = pCurrByteLine[x];
               //If currByte is != 0, it contains at least one white pixel.
               if (currByte) {
                  if (ymin > y) {
                     ymin = y;
                  }
                  if (ymax < y) {
                     ymax = y;
                  }
                  currXPixelOffset = x << 3;
                  //Check if this byte of pixels might contain xmin or xmax.
                  if ((currXPixelOffset < xmin) || 
                      ((currXPixelOffset + 7) > xmax)) {
                     for (TInt b = 0; b < 8; b++) {
                        //Some of the 8 pixels in the byte are visible.
                        //Find which ones that mather for the x-axis.
                        if  (currByte & (1 << b)) {
                           currXPixel = currXPixelOffset + b;
                           if (xmin > currXPixel) {
                              xmin = currXPixel;
                           }
                           if (xmax < currXPixel) {
                              xmax = currXPixel;
                           }
                        }
                     }
                  }
               }
            }
            //Here we take care of bit padded bytes when the
            //image width is not evenly dividable by a byte.
            if (imgBitsLeft != 0) {
               currByte = pCurrByteLine[imgByteWidth];
               currXPixelOffset = imgByteWidth << 3;
               for (TInt b = 0; b < imgBitsLeft; b++) {
                  if  (currByte & (1 << b)) {
                     currXPixel = currXPixelOffset + b;
                     if (xmax < currXPixel) {
                        xmax = currXPixel;
                     }
                  }
               }
            }
            //Move to next line in image.
            pCurrByteLine = pCurrByteLine + lineLength;
         }
      }