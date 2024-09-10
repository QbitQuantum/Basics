RECT	TTransRemain::RectNoBlack(IMG &image, TRect2D<int> &rect, IMG debugImage)
{
	unsigned char				*pImage = NULL;
	PVPAT						VPA		= NULL;
	GetImageVPA					(image, 0, (void**)&pImage, &VPA);

	//const size_t rectWidth	= rect.Width();
	//const size_t rectHeight = rect.Height();

	RECT	resultRect = { 0, 0, 0, 0};

	bool lineEmpty = false;
	for(int i = rect.x0() ; i < rect.x1(); ++i)
	{
		for (int j = rect.y0(); j < rect.y1(); ++j)
		{
			if (0 == *(VPA[i].XEntry + pImage + VPA[j].YEntry) )
			{
				break;
			}
			//*(rawVPA[i].XEntry + pRawImage + rawVPA[j].YEntry) = 255;
			
			if (rect.y1() -1 == j)
			{
				lineEmpty = true;
			}
		}
		if (lineEmpty)
		{
			resultRect.left = rect.x0() + i;
			resultRect.top	= rect.y0();
			break;
		}		
	}

	lineEmpty	= false;
	for (int i = rect.x1()-1; i >rect.x0(); --i)
	{
		for (int j = rect.y0(); j < rect.y1(); ++j)
		{			
			
			if ( 0 == *(VPA[i].XEntry + pImage + VPA[j].YEntry))
			{
				break;
			}
			if ( rect.y1()-1 == j)
			{
				lineEmpty = true;
			}
		}
		if (lineEmpty)
		{
			resultRect.right = rect.x0() + i;
			resultRect.bottom = rect.y1();
			break;
		}
	}
	return resultRect;
}