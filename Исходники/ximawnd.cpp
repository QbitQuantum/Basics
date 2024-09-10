void CxImage::CreateFromHICON(HICON hico)
{
	Destroy();
	if (hico) { 
		ICONINFO iinfo;
		GetIconInfo(hico,&iinfo);
		CreateFromHBITMAP(iinfo.hbmColor);
#if CXIMAGE_SUPPORT_ALPHA
		CxImage mask;
		mask.CreateFromHBITMAP(iinfo.hbmMask);
		mask.GrayScale();
		mask.Negative();
		AlphaSet(mask);
#endif
    }
}