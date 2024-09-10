template <> void Matrix<double>::set(double value)
{
#ifdef _DEBUG
	if(height==0 || width==0)
		throw std::invalid_argument("Impossible to set value for ghost matrix");
#endif
	double* x = pData;
	int n = width*height;
    int i;
    __m128d XMM0 = _mm_set1_pd(value);
    for (i = 0;i < (n);i += 8) { 
        _mm_store_pd((x)+i  , XMM0); 
        _mm_store_pd((x)+i+2, XMM0); 
        _mm_store_pd((x)+i+4, XMM0); 
        _mm_store_pd((x)+i+6, XMM0); 
    } 
}