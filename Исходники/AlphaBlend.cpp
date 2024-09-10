void alphaBlendSSE_8u(Mat& src1, Mat& src2, Mat& alpha, Mat& dest)
{
	if(dest.empty())dest.create(src1.size(),CV_8U);

	const int imsize = (src1.size().area()/16);
	uchar* s1 = src1.data;
	uchar* s2 = src2.data;
	uchar* a = alpha.data;
	uchar* d = dest.data;

	const __m128i zero = _mm_setzero_si128();
	const __m128i amax = _mm_set1_epi8(char(255));
	int i=0;
	if(s1==d)
	{
		for(;i<imsize;++i)
		{
			__m128i ms1h = _mm_load_si128((__m128i*)(s1));
			__m128i ms2h = _mm_load_si128((__m128i*)(s2));
			__m128i mah = _mm_load_si128((__m128i*)(a));
			__m128i imah = _mm_sub_epi8(amax,mah);

			__m128i ms1l = _mm_unpacklo_epi8(ms1h, zero);
			ms1h = _mm_unpackhi_epi8(ms1h, zero);

			__m128i ms2l = _mm_unpacklo_epi8(ms2h, zero);
			ms2h = _mm_unpackhi_epi8(ms2h, zero);

			__m128i mal = _mm_unpacklo_epi8(mah, zero);
			mah = _mm_unpackhi_epi8(mah, zero);

			__m128i imal = _mm_unpacklo_epi8(imah, zero);
			imah = _mm_unpackhi_epi8(imah, zero);

			ms1l = _mm_mullo_epi16(ms1l,mal);
			ms2l = _mm_mullo_epi16(ms2l,imal);
			ms1l = _mm_add_epi16(ms1l,ms2l);
			//ms1l = _mm_srli_epi16(ms1l,8);
			ms1l = _mm_srai_epi16(ms1l,8);

			ms1h = _mm_mullo_epi16(ms1h,mah);
			ms2h = _mm_mullo_epi16(ms2h,imah);
			ms1h = _mm_add_epi16(ms1h,ms2h);
			//ms1h = _mm_srli_epi16(ms1h,8);
			ms1h = _mm_srai_epi16(ms1h,8);

			_mm_stream_si128((__m128i*)s1,_mm_packs_epi16(ms1l,ms1h));

			s1+=16;
			s2+=16;
			a+=16;
		}
	}
	else
	{
		for(;i<imsize;++i)
		{
			__m128i ms1h = _mm_load_si128((__m128i*)(s1));
			__m128i ms2h = _mm_load_si128((__m128i*)(s2));
			__m128i mah = _mm_load_si128((__m128i*)(a));
			__m128i imah = _mm_sub_epi8(amax,mah);

			__m128i ms1l = _mm_unpacklo_epi8(ms1h, zero);
			ms1h = _mm_unpackhi_epi8(ms1h, zero);

			__m128i ms2l = _mm_unpacklo_epi8(ms2h, zero);
			ms2h = _mm_unpackhi_epi8(ms2h, zero);

			__m128i mal = _mm_unpacklo_epi8(mah, zero);
			mah = _mm_unpackhi_epi8(mah, zero);

			__m128i imal = _mm_unpacklo_epi8(imah, zero);
			imah = _mm_unpackhi_epi8(imah, zero);

			ms1l = _mm_mullo_epi16(ms1l,mal);
			ms2l = _mm_mullo_epi16(ms2l,imal);
			ms1l = _mm_add_epi16(ms1l,ms2l);
			//ms1l = _mm_srli_epi16(ms1l,8);
			ms1l = _mm_srai_epi16(ms1l,8);

			ms1h = _mm_mullo_epi16(ms1h,mah);
			ms2h = _mm_mullo_epi16(ms2h,imah);
			ms1h = _mm_add_epi16(ms1h,ms2h);
			//ms1h = _mm_srli_epi16(ms1h,8);
			ms1h = _mm_srai_epi16(ms1h,8);

			_mm_store_si128((__m128i*)d,_mm_packs_epi16(ms1l,ms1h));

			s1+=16;
			s2+=16;
			a+=16;
			d+=16;
		}
	}

	{
		uchar* s1 = src1.data;
		uchar* s2 = src2.data;
		uchar* a = alpha.data;
		uchar* d = dest.data;
		for(int n=i*16;n<src1.size().area();n++)
		{
			d[n] = (a[n]*s1[n] + (255-a[n])*s2[n])>>8;
		}
	}
}