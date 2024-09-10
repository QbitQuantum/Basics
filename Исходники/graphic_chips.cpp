BOOL Chips::createAnimationBuffers(const CChips& chips)
{
  if (chips == chips_)
  {  // The same amount of chips was animated last time,
     // reuse animation buffers
     return TRUE;
  }
  else
  {  // Must recreate animation buffers if
     // image will be bigger than previous animation
     chips_ = chips;
     CSize s = getChipsSize(chips, 0, 0);

     // SANITY CHECK
     if (s.cx > 300)
       s.cx = 300;
     if (s.cy > 300)
       s.cy = 300;

     bool recreate = false;
     BITMAP bm;
     memset(&bm, 0, sizeof(bm));

     if (!chipsImage_.GetSafeHandle())
     {
       bm.bmWidth = s.cx;
       bm.bmHeight = s.cy;
       recreate = true;
     }
     else
     {
       chipsImage_.GetBitmap(&bm);
       if (bm.bmWidth != s.cx || bm.bmHeight != s.cy)
         recreate = true;
       else
         recreate = false;
     }

     CWindowDC dcScreen(NULL);
     if (recreate)
     {
       chipsImage_.DeleteObject();
       chipsMask_.DeleteObject();
       bmpSave_.DeleteObject();

       if (!chipsImage_.CreateCompatibleBitmap(&dcScreen, s.cx, s.cy) ||
           !chipsMask_.CreateCompatibleBitmap(&dcScreen, s.cx, s.cy) ||
           !bmpSave_.CreateCompatibleBitmap(&dcScreen, s.cx, s.cy))
       {
         return FALSE;
       }

       chipsImage_.GetBitmap(&bm);
     }

     CDC dcTmp;
     dcTmp.CreateCompatibleDC(&dcScreen);

     // Create the image
     CBitmap* pOldBmp = dcTmp.SelectObject(&chipsImage_);
     dcTmp.PatBlt(0, 0, bm.bmWidth, bm.bmHeight, BLACKNESS);
     drawChips(&dcTmp, chips, 0, bm.bmHeight - Height_, 0);

// Debugging:
//     dcScreen.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcTmp,
//                     0, 0, SRCCOPY);

     // Create the mask
     dcTmp.SelectObject(&chipsMask_);
     dcTmp.PatBlt(0, 0, bm.bmWidth, bm.bmHeight, WHITENESS);
     drawChips(&dcTmp, chips, 0, bm.bmHeight - Height_, DF_CreateMask);

// Debugging:
//     dcScreen.BitBlt(bm.bmWidth + 2, 0, bm.bmWidth, bm.bmHeight, &dcTmp,
//                     0, 0, SRCCOPY);

     // Clean up
     dcTmp.SelectObject(pOldBmp);
   }

  return TRUE;
}