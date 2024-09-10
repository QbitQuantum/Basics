static void clearDepthSSE(float* begin,size_t length,float value){
	enum { SimdLaneWidth = 4 };

	assertRelease(uintptr_t(begin)%16 == 0);
	auto rem = length % SimdLaneWidth;
	length = (length/SimdLaneWidth)*SimdLaneWidth;
	
	__m128 k = _mm_set_ps1(value);
	for(size_t i = 0;i<length;i+=SimdLaneWidth)
		_mm_store_ps(begin+i,k);
	if(rem == 0) return;
	for(size_t i = 0;i<rem;i++){
		begin[length+i] = value;
	}
}