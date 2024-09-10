Status CImgCutter::GenerateMask( UCHAR* pMask, int width, int height )
{	

	Status sts = Ok;
	ASSERT(pMask != NULL);
	//FillMemory(pMask, width * height, 0);

	// Change to image coordinate
	Point pPoint[256];
	// Compute the point coordinate according to the view area
	for (int i=0; i < m_oCurve.GetNumOfPoint(); i++)
	{
		pPoint[i].X = m_oCurve.GetPointAt(i).X - m_CutFrame.left;
		pPoint[i].Y = m_oCurve.GetPointAt(i).Y - m_CutFrame.top;

	}


	DOUBLE	dVerticalScale = (DOUBLE)height / (DOUBLE) m_CutFrame.Height();
	DOUBLE	dHorizontalScale = (DOUBLE)width / (DOUBLE) m_CutFrame.Width();

	for (int i=0; i< m_oCurve.GetNumOfPoint(); i++)
	{
		pPoint[i].X = pPoint[i].X*dHorizontalScale; 
		pPoint[i].Y = pPoint[i].Y*dVerticalScale;		
	}

	Bitmap* pMemBitmap = new Bitmap(width, height, PixelFormat24bppRGB);
	Graphics* pMemGraphics = Graphics::FromImage(pMemBitmap);
	SolidBrush solidBrush(Color(255, 255, 255));
	Rect cutRect;
	switch (m_nCutMode)
	{
	case SV_CUT_RECTANGLE:
		//sts = pMemGraphics->FillRectangle(&solidBrush, , 0, width, height);
		
		cutRect.X = min(pPoint[0].X, pPoint[1].X);
		cutRect.Y = min(pPoint[0].Y, pPoint[1].Y);;
		cutRect.Height = abs(pPoint[1].Y - pPoint[0].Y);
		cutRect.Width = abs(pPoint[1].X - pPoint[0].X);
		sts = pMemGraphics->FillRectangle(&solidBrush, cutRect);
		
		break;

	case SV_CUT_CURVES:
		sts = pMemGraphics->FillClosedCurve(&solidBrush, pPoint, m_oCurve.GetNumOfPoint());
		break;

	case SV_CUT_LINESEGMENTS:
		sts = pMemGraphics->FillClosedCurve(&solidBrush, pPoint, m_oCurve.GetNumOfPoint(),FillModeAlternate, 0.0f);
		break;
	default:
		break;
	}
	
	Color pixcolor;
	for (int y = 0; y < height; y ++) 
		for (int x = 0; x < width; x ++)
		{
			pMemBitmap->GetPixel(x,y, &pixcolor);
			pMask[y*width + x] = (UCHAR)pixcolor.GetRed();			
		}
	
/*
#ifdef _DEBUG
		CLSID pngClsid;	
		CUtility::GetEncoderClsid(L"image/bmp", &pngClsid);
		sts = pMemBitmap->Save(L"D:\\Temp\\Test.bmp", &pngClsid, NULL);
#endif // _DEBUG
*/

	delete pMemGraphics;
	delete pMemBitmap;
	return sts;
}