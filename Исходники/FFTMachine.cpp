//************************************
// Method:    getComplexImage
// FullName:  CFFTMachine::getComplexImage
// Access:    protected 
// Returns:   LPCOMPLEX
// Qualifier:
// Parameter: CImgSource * in_pSrcImg
//************************************
procStatus CFFTMachine::getComplexImage( CImgSource* in_pSrc, LPCOMPLEX* out_ppComplex )
{
	procStatus eRetCode = eNormal;

	Bitmap* pBmp = in_pSrc->GetSourceRef();
	ASSERT(pBmp != NULL);
	ASSERT(out_ppComplex);
	

	INT nWidth = pBmp->GetWidth();
	INT nHeight= pBmp->GetHeight();
	
	SourceType eType = in_pSrc->GetType();
	Status sts = Ok;
	BYTE nVal = 0;

	for (INT y=0;y<nHeight;y++)	//for all rows
	{
		for (INT x=0;x<nWidth; x++) //for all col
		{
			nVal = 0;
			Color clr(0,0,0);
			sts = pBmp->GetPixel(x,y, &clr);
			if(sts == Ok)
			{
				nVal = CUtility::GetMonoPixelValue(clr, eType);
				out_ppComplex[y][x].real = nVal; 
			}
			else
			{
				break;
			}
		}
		if(sts != Ok) break;
	}
	
	if (sts != Ok)
	{
		eRetCode = eSystemErr;
	}
	return eRetCode;
}