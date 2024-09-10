Image* ExtractCharachter(int **iaLabels, int iRows, int iCols, int iLabel)
{
	Image *pImage = new Image();

	int iXmax = 0, iYmax = 0, iXmin = iRows, iYmin = iCols;

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			if(iaLabels[i][j] == iLabel)
			{
				if(iXmax < i)
					iXmax = i;
				if(iXmin > i)
					iXmin = i;

				if(iYmax < j)
					iYmax = j;
				if(iYmin > j)
					iYmin = j;
			}
		}
	}

	int icRows = iXmax - iXmin + 1, icCols = iYmax - iYmin + 1;

	InitImage(pImage,string::basic_string(""),icRows+2, icCols+2,1);

	for(int i = 0;i<icRows+2;i++)
	{
		for(int j = 0;j<icCols+2;j++)
		{
			Pixel pxPW(255);

			pImage->SetPixel(i,j,pxPW);
		}
	}
	
	for(int i = iXmin-1;i<=iXmax+1;i++)
	{
		for(int j = iYmin-1;j<=iYmax+1;j++)
		{
			Pixel pxPB(0);
			Pixel pxPW(255);

			if(iaLabels[i][j] == iLabel)
				pImage->SetPixel(i - (iXmin - 1),j - (iYmin - 1), pxPB);	
			else
				pImage->SetPixel(i - (iXmin - 1),j - (iYmin - 1), pxPW);			
		}
	}

	return pImage;
}