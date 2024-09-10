		inline float16 Transpose(const float16 & a)
		{
			float16 temp, res;

			temp.x.m128 = _mm_unpacklo_ps(a.x.m128, a.z.m128);
			temp.y.m128 = _mm_unpacklo_ps(a.y.m128, a.w.m128);
			temp.z.m128 = _mm_unpackhi_ps(a.x.m128, a.z.m128);
			temp.w.m128 = _mm_unpackhi_ps(a.y.m128, a.w.m128);

			res.x.m128 = _mm_unpacklo_ps(temp.x.m128, temp.y.m128);
			res.y.m128 = _mm_unpackhi_ps(temp.x.m128, temp.y.m128);
			res.z.m128 = _mm_unpacklo_ps(temp.z.m128, temp.w.m128);
			res.w.m128 = _mm_unpackhi_ps(temp.z.m128, temp.w.m128);

			return res;
		}