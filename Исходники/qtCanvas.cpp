void
qtCanvas::Impl::setupImage()
{
    MacSetRect(&mFrame, 0, 0, mWidth, mHeight);
    
    mImageStride = mWidth * 4;
    mImageData = new unsigned char[mImageStride * mHeight];

    OSErr err;
	err = QTNewGWorldFromPtr(&mGWorld,
				k32ARGBPixelFormat, &mFrame,
				nil, nil, (GWorldFlags)0,
				mImageData, mImageStride);
    CheckError(err, "QTNewGWorldFromPtr");
}