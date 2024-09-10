 void runImageTests(const string& sFName)
 {
     cerr << "    Testing " << sFName << endl;
     BitmapPtr pBmp = loadTestBmp(sFName);
     PixelFormat pf = pBmp->getPixelFormat();
     cerr << "      Source Bmp: " << pf << endl;
     BitmapPtr pDestBmp;
     pDestBmp = GPUBrightnessFilter(pBmp->getSize(), pixelFormatHasAlpha(pf), 1)
             .apply(pBmp);
     float maxAverage, maxStdDev;
     if (GLContext::getCurrent()->isGLES()) {
         // less strict (lower floating point precision?)
         maxAverage = 0.5;
         maxStdDev = 1.5;
     }
     else {
         maxAverage = 0.2;
         maxStdDev = 0.5;
     }
     testEqual(*pDestBmp, *pBmp, string("brightness_")+sFName, maxAverage, maxStdDev);
 }