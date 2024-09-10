void RayTracingImageCudaMOO::fillImageGL()
    {
    int w = getW();
    int h = getH();

#pragma omp parallel for num_threads(numThreads)
    for (int i = 1; i <= h; i++)
	{
	for (int j = 1; j <= w; j++)
	    {
	    setPixel(i, j, t);
	    }
	}
    }