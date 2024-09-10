void VPictureData_MacPicture::_DisposeMetaFile()const
{
	if (fMetaFile)
	{
#if VERSIONWIN
		DeleteEnhMetaFile(fMetaFile);
#else
		QDPictRelease(fMetaFile);
#endif
		fMetaFile = NULL;
	}
	if (fTrans)
	{
#if VERSIONWIN
#if ENABLE_D2D
		VWinD2DGraphicContext::ReleaseBitmap(fTrans);
#endif
		delete fTrans;
#elif VERSIONMAC
		CFRelease(fTrans);
#endif
		fTrans = NULL;
	}
#if VERSIONWIN
	if (fGdiplusMetaFile)
		delete fGdiplusMetaFile;
	fGdiplusMetaFile = 0;
#endif
}