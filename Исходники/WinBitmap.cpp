/* second-phase constrcutor */
bool WinBitmap::construct(const byte* dataBuf, uint32 nbrBytes)
{
   /* get the current DC format */
   m_dc = CreateCompatibleDC(NULL);
   if(m_dc == NULL) {
      return(false);
   }

/** TGA Implementation **/
#if 1
   register int32 row, col;
   register int32 index;
   int32 red, green, blue, alpha;
   int32 bitDepth;
   HDC maskDC = NULL;
   HBITMAP oldMaskBmp = NULL;

   /* get the BMP file information */
   TGAHEADER tgaHeader;
   ::memcpy(&tgaHeader, dataBuf, sizeof(TGAHEADER));

   /* get the location of the color data */
   
   int offset = sizeof(TGAHEADER) + tgaHeader.numCharsID;
   
   const byte* colorData = reinterpret_cast<const byte*>(&dataBuf[offset]);

   bool useColorMap = false;
   if ( tgaHeader.colorMapType == 1 ) {
      // Use color map.
      useColorMap = true;
      // Read the color map data.
      int offsetToColorData = readColorMapData( tgaHeader, colorData );
      // Add the offset to colorData so that the colorData actually
      // points to the color data instead of to the color map.
      colorData += offsetToColorData; 
   }
     
   // colorData should now point at the color data!

   /* set the dimensions */
   m_width = tgaHeader.imageWidth;
   m_height = tgaHeader.imageHeight;

   /* get the bit-depth of the image */
   bitDepth = tgaHeader.bitsPerPixel;

   /* create the bitmap using the given info */
   m_bmp = CreateBitmap(m_width, m_height, 1,
                        GetDeviceCaps(m_dc, BITSPIXEL),
                        NULL);
   if(m_bmp == NULL) {
      /* cannot create bitmap */
      return(false);
   }

   /* select the bitmap into the DC */
   m_oldBmp = (HBITMAP)SelectObject(m_dc, m_bmp);

   /* create the same sized monocrome mask if required */
   if(bitDepth == 32) {
      m_mask = CreateBitmap(m_width, m_height, 1, 1, NULL);
      /* check for errors */
      if(m_mask == NULL) {
         return(false);
      }
      /* create DC, and select the mask into it */
      maskDC = CreateCompatibleDC(NULL);
      /* check for errors */
      if(maskDC == NULL) {
         return(false);
      }
      /* select our monochrome mask into it */
      oldMaskBmp = (HBITMAP)SelectObject(maskDC, m_mask);
   }

   /* Bottom-up TGAs are expected .. read and create */
   index = 0;
   for(row = m_height-1; row >= 0; --row) {
      for(col = 0; col < m_width; ++col) {

         /* 32-bit TGAs need different processing from 24-bit */
         if(bitDepth == 32) {
            if ( useColorMap ) {
               int colorMapIdx = colorData[ index++ ];
               PIXEL p = m_colorMap[ colorMapIdx ];
               blue = p.blue;
               green = p.green;
               red = p.red;
               alpha = 255;
            } else {
               // No color map.
               /* read the color value in components */
               blue  = colorData[index++];
               green = colorData[index++];
               red   = colorData[index++];
               alpha = colorData[index++];
            }
            /* write the color pixel */
            SetPixelV(m_dc, col, row, RGB(red,green,blue));
            /* check the alpha component */
            if(alpha > 127) {
               /* solid pixel */
               SetPixelV(maskDC, col, row, RGB(255,255,255));
            }
            else {
               /* transparent pixel */
               SetPixelV(maskDC, col, row, RGB(0,0,0));
            }
         }
         /* expecting 24-bit RGB Image */
         else {
            if ( useColorMap ) {
               int colorMapIdx = colorData[ index++ ];
               PIXEL p = m_colorMap[ colorMapIdx ];
               blue = p.blue;
               green = p.green;
               red = p.red;
            } else {
               // No color map.
               /* read the color value in components */
               blue  = colorData[index++];
               green = colorData[index++];
               red   = colorData[index++];
            }
            /* write the color pixel */
            SetPixelV(m_dc, col, row, RGB(red,green,blue));
         }

      }
   }

   /* release the mask DC if used */
   if(bitDepth == 32) {
      SelectObject(maskDC, oldMaskBmp);
      DeleteDC(maskDC);
   }

   if(bitDepth == 32) {
      /* set our masked flag */
      m_isMasked = true;
   }
   else {
      m_isMasked = false;
   }

   /* success */
   return(true);
#endif


/** BMP Implementation **/
#if 0
   register int32 row, col;
   register int32 index;
   int32 red, green, blue, alpha;
   HDC maskDC = NULL;
   HBITMAP oldMaskBmp = NULL;

   /* get the BMP file information */
   BITMAPFILEHEADER bmHeader;
   BITMAPINFOHEADER bmInfo;
   ::memcpy(&bmHeader, dataBuf, sizeof(BITMAPFILEHEADER));
   ::memcpy(&bmInfo, &dataBuf[sizeof(BITMAPFILEHEADER)], 
            sizeof(BITMAPINFOHEADER));

   /* get the location of the color data */
   const byte* colorData = reinterpret_cast<const byte*>(&dataBuf[bmHeader.bfOffBits]);

   /* set the dimensions */
   m_width = bmInfo.biWidth;
   m_height = bmInfo.biHeight;

   /* create the bitmap using the given info */
   m_bmp = CreateBitmap(m_width, m_height, 1,
                        GetDeviceCaps(m_dc, BITSPIXEL),
                        NULL);
   if(m_bmp == NULL) {
      /* cannot create bitmap */
      return(false);
   }

   /* select the bitmap into the DC */
   m_oldBmp = (HBITMAP)SelectObject(m_dc, m_bmp);

   /* create the same sized monocrome mask if required */
   if(bmInfo.biBitCount == 32) {
      m_mask = CreateBitmap(m_width, m_height, 1, 1, NULL);
      /* check for errors */
      if(m_mask == NULL) {
         return(false);
      }
      /* create DC, and select the mask into it */
      maskDC = CreateCompatibleDC(NULL);
      /* check for errors */
      if(maskDC == NULL) {
         return(false);
      }
      /* select our monochrome mask into it */
      oldMaskBmp = (HBITMAP)SelectObject(maskDC, m_mask);
   }

   /* Bottom-up BMP's are expected .. read and create */
   index = 0;
   for(row = m_height-1; row >= 0; --row) {
      for(col = 0; col < m_width; ++col) {

         /* 32-bit BMP's need different processing from 24-bit */
         if(bmInfo.biBitCount == 32) {
            /* read the color value in components */
            alpha = colorData[index++];
            blue  = colorData[index++];
            green = colorData[index++];
            red   = colorData[index++];
            /* write the color pixel */
            SetPixelV(m_dc, col, row, RGB(red,green,blue));
            /* check the alpha component */
            if(alpha > 127) {
               /* solid pixel */
               SetPixelV(maskDC, col, row, RGB(255,255,255));
            }
            else {
               /* transparent pixel */
               SetPixelV(maskDC, col, row, RGB(0,0,0));
            }
         }
         /* expecting 24-bit RGB Image */
         else {
            /* read the color value in components */
            blue  = colorData[index++];
            green = colorData[index++];
            red   = colorData[index++];
            /* write the color pixel */
            SetPixelV(m_dc, col, row, RGB(red,green,blue));
         }

      }
   }

   /* release the mask DC if used */
   if(bmInfo.biBitCount == 32) {
      SelectObject(maskDC, oldMaskBmp);
      DeleteDC(maskDC);
   }

   if(bmInfo.biBitCount == 32) {
      /* set our masked flag */
      m_isMasked = true;
   }
   else {
      m_isMasked = false;
   }

   /* success */
   return(true);

#endif

/* TESTING Implemntation */
#if 0
   /* try to create the bitmap -- TESTING */
   m_bmp = CreateBitmap(7, 7, 1,
                        GetDeviceCaps(m_dc, BITSPIXEL),
                        NULL);
   if(m_bmp == NULL) {
      /* delete the DC */
      DeleteDC(m_dc);
      return(false);
   }

   /* select the bitmap into the DC */
   m_oldBmp = (HBITMAP)SelectObject(m_dc, m_bmp);

   /* set the dimensions */
   m_width = 7;
   m_height = 7;

   /* TEST - clear the bitmap */
   HBRUSH clrBrush = CreateSolidBrush( RGB(200,20,20) );
   RECT bmpRect;
   SetRect(&bmpRect, 0, 0, m_width, m_height);
   FillRect(m_dc, &bmpRect, clrBrush);
   DeleteObject(clrBrush);

   /* success */
   return(true);

#endif

}