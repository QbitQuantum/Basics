void
gaussianblur(PLBmpBase * theSource, PLBmp * theDestination, const KernelVec & theKernel, double theRadius,
             unsigned theRealWidth, unsigned theRealHeight, double theSigma) {
    int myIntRadius = int(ceil(double(theRadius)));

    unsigned mySrcHeight = theSource->GetHeight();
    unsigned mySrcWidth = theSource->GetWidth();
    unsigned myDestWidth =  mySrcWidth;
    unsigned myDestHeight = mySrcHeight;
    PLBmp * myTempBmp = new PLAnyBmp();
    myTempBmp->Create(myDestWidth, mySrcHeight, theSource->GetPixelFormat());

    theDestination->Create(myDestWidth, myDestHeight, theSource->GetPixelFormat());

    // Convolve in x-direction
    int myOffset = myIntRadius - 1;
    {
        // pass 1: Glur in x direction
        for (unsigned y=0; y < mySrcHeight; ++y) {
            for(unsigned x=0; x<myDestWidth; ++x) {
                PIXELTYPE myColor;
                clearPixel(myColor);
                for(int w=0; w<myIntRadius; ++w) {
                    int xs = x + w - myOffset;
                    PIXELTYPE myKernelPixel;
                    if (xs>=0 && static_cast<unsigned>(xs)<theRealWidth) {
                        getPix<PIXELTYPE>(theSource, xs,y, myKernelPixel);
                    } else {
                        if (xs < 0) {
                            getPix<PIXELTYPE>(theSource, 0,y, myKernelPixel);
                        } else {
                            getPix<PIXELTYPE>(theSource, theRealWidth-1,y, myKernelPixel);
                        }
                    }
                    multAndStore(myColor, &myKernelPixel, theKernel[w]);
                    xs = x + w;
                    if (xs>=0 && static_cast<unsigned>(xs)<theRealWidth) {
                        getPix<PIXELTYPE>(theSource, xs,y, myKernelPixel);
                    } else {
                        if (xs < 0) {
                            getPix<PIXELTYPE>(theSource, 0,y, myKernelPixel);
                        } else {
                            getPix<PIXELTYPE>(theSource, theRealWidth-1,y, myKernelPixel);
                        }
                    }
                    multAndStore(myColor, &myKernelPixel, theKernel[w+myIntRadius]);
                }
                myTempBmp->SetPixel(x,y,myColor);
            }
        }
    }

    for(unsigned x=0; x<myDestWidth; ++x) {
        for (unsigned y=0; y < myDestHeight; ++y) {
            PIXELTYPE myColor;
            clearPixel(myColor);
            for(int w=0; w<myIntRadius; ++w) {
                int ys = y + w - myOffset;
                PIXELTYPE myKernelPixel;

                if (ys>=0 && static_cast<unsigned>(ys)<theRealHeight) {
                    getPix<PIXELTYPE>(myTempBmp, x,ys, myKernelPixel);
                } else {
                    if (ys < 0) {
                        getPix<PIXELTYPE>(myTempBmp, x,0, myKernelPixel);
                    } else {
                        getPix<PIXELTYPE>(myTempBmp, x,theRealHeight-1, myKernelPixel);
                    }
                }
                multAndStore(myColor, &myKernelPixel, theKernel[w]);
                ys = y + w;
                if (ys>=0 && static_cast<unsigned>(ys)<theRealHeight) {
                    getPix<PIXELTYPE>(myTempBmp, x,ys, myKernelPixel);
                } else {
                    if (ys < 0) {
                        getPix<PIXELTYPE>(myTempBmp, x,0, myKernelPixel);
                    } else {
                        getPix<PIXELTYPE>(myTempBmp, x,theRealHeight-1, myKernelPixel);
                    }
                }
                multAndStore(myColor, &myKernelPixel, theKernel[w+myIntRadius]);
            }
            theDestination->SetPixel(x,y,myColor);
        }
    }
    delete myTempBmp;
}