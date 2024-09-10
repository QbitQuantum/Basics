void RipplingMOO::fillImage(float t)
    {
    int h = getH();
    int w = getW();
    
#pragma omp parallel for if ( _omp )
    for (int i = 1; i <= h; i++)
	{
	for (int j = 1; j <= w; j++)
	    {
	    setPixel(i, j, t);
	    }
	}
    }