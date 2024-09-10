void CPrediction::doTransformPFrame(CImage<float> * pSrc, CImage<float> * pDst, CPredictionInfoTable * pPred)
{
	for(int k=0;k<pSrc->getComponents();k++)
	{
		int scale = 16/pSrc->getScale(k);
		CSize size = (*pSrc)[k].getSize();
		for(int y=0; y < size.Height; y+=8)
		{
			for(int x=0; x < size.Width; x+=8)
			{
				prediction_info_t info = (*pPred)[y/scale][x/scale];
				TransformBlock(&(*pSrc)[k][y][x], &(*pDst)[k][y][x], CPoint(k, y, x), size, info, scale);
			}
		}
	}
}