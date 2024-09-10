void CNtMagickView::DoDisplayImage()

{

  CDC *pDC = GetDC();

  if (pDC != NULL && m_Image.isValid() ) 

    {

      CRect rectClient;

      GetClientRect(rectClient);



      // Clear the background

      pDC->FillSolidRect(rectClient,pDC->GetBkColor());



      // Set up the Windows bitmap header

      BITMAPINFOHEADER bmi;

      bmi.biSize = sizeof(BITMAPINFOHEADER);    // Size of structure

      bmi.biWidth = m_Image.columns();          // Bitmaps width in pixels

      bmi.biHeight = (-1)*m_Image.rows();       // Bitmaps height n pixels

      bmi.biPlanes = 1;                         // Number of planes in the image

      bmi.biBitCount = 32;                      // The number of bits per pixel

      bmi.biCompression = BI_RGB;               // The type of compression used

      bmi.biSizeImage = 0;                      // The size of the image in bytes

      bmi.biXPelsPerMeter = 0;                  // Horizontal resolution

      bmi.biYPelsPerMeter = 0;                  // Veritical resolution

      bmi.biClrUsed = 0;                        // Number of colors actually used

      bmi.biClrImportant = 0;                   // Colors most important



      // Extract the pixels from Magick++ image object and convert to a DIB section

      Quantum *pPixels = m_Image.getPixels(0,0,m_Image.columns(),m_Image.rows());



      RGBQUAD *prgbaDIB = 0;

      HBITMAP hBitmap = CreateDIBSection

        (

         pDC->m_hDC,            // handle to device context

         (BITMAPINFO *)&bmi,    // pointer to structure containing bitmap size, format, and color data

         DIB_RGB_COLORS,        // color data type indicator: RGB values or palette indices

         (void**)&prgbaDIB,     // pointer to variable to receive a pointer to the bitmap's bit values

         NULL,                  // optional handle to a file mapping object

         0                      // offset to the bitmap bit values within the file mapping object

         );



      if ( !hBitmap )

        return;



      unsigned long nPixels = m_Image.columns() * m_Image.rows();

      RGBQUAD *pDestPixel = prgbaDIB;

      // Transfer pixels, scaling to Quantum

      for( unsigned long nPixelCount = nPixels; nPixelCount ; nPixelCount-- )

        {

          pDestPixel->rgbRed = MagickCore::GetPixelRed(m_Image.constImage(),pPixels)/257;

          pDestPixel->rgbGreen = MagickCore::GetPixelGreen(m_Image.constImage(),pPixels)/257;

          pDestPixel->rgbBlue = MagickCore::GetPixelBlue(m_Image.constImage(),pPixels)/257;

          pDestPixel->rgbReserved = 0;

          ++pDestPixel;

          pPixels+=MagickCore::GetPixelChannels(m_Image.constImage());

        }


      // Now copy the bitmap to device.

        HDC     hMemDC = CreateCompatibleDC( pDC->m_hDC );

        SelectObject( hMemDC, hBitmap );

        BitBlt( pDC->m_hDC, 0, 0, m_Image.columns(), m_Image.rows(), hMemDC, 0, 0, SRCCOPY );

        DeleteObject( hMemDC );

    }

}