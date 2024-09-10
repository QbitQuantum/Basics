void SimpleClean::PartialSubtractImageAVX(double *image, size_t imgWidth, size_t imgHeight, const double *psf, size_t psfWidth, size_t psfHeight, size_t x, size_t y, double factor, size_t startY, size_t endY)
{
	size_t startX, endX;
	int offsetX = (int) x - psfWidth/2, offsetY = (int) y - psfHeight/2;
	
	if(offsetX > 0)
		startX = offsetX;
	else
		startX = 0;
	
	if(offsetY > (int) startY)
		startY = offsetY;
	
	endX = std::min(x + psfWidth/2, imgWidth);
	
	size_t unAlignedCount = (endX - startX) % 4;
	endX -= unAlignedCount;
	
	endY = std::min(y + psfHeight/2, endY);
	
	const __m256d mFactor = _mm256_set1_pd(-factor);
	for(size_t ypos = startY; ypos < endY; ++ypos)
	{
		double *imageIter = image + ypos * imgWidth + startX;
		const double *psfIter = psf + (ypos - offsetY) * psfWidth + startX - offsetX;
		for(size_t xpos = startX; xpos != endX; xpos+=4)
		{
			__m256d
				imgVal = _mm256_loadu_pd(imageIter),
				psfVal = _mm256_loadu_pd(psfIter);
#ifdef __FMA4__
			_mm256_storeu_pd(imageIter, _mm256_fmadd_pd(psfVal, mFactor, imgVal));
#else
			_mm256_storeu_pd(imageIter, _mm256_add_pd(imgVal, _mm256_mul_pd(psfVal, mFactor)));
#endif
			imageIter+=4;
			psfIter+=4;
		}
		for(size_t xpos = endX; xpos!=endX + unAlignedCount; ++xpos)
		{
			*imageIter -= *psfIter * factor;
			++imageIter;
			++psfIter;
		}
	}
}