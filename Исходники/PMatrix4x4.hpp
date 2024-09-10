			inline PVector4df operator*(const PVector4df &v) {
		
#ifdef __SSE_AVAIL__

				__m128 v1 = _mm_load_ps(v._Vec);
				__m128 m0 = _mm_load_ps(Row1);
				__m128 m1 = _mm_load_ps(Row2);
				__m128 m2 = _mm_load_ps(Row3);
				__m128 m3 = _mm_load_ps(Row4);
				 m0 = _mm_mul_ps(m0, v1);   //(e11 * v.X) , (e21 * v.Y), (e31 * v.Z), (e41 * v.W)
				 m1 = _mm_mul_ps(m1, v1);	//(e12 * v.X) , (e22 * v.Y), (e32 * v.Z), (e42 * v.W)
				 m2 = _mm_mul_ps(m2, v1);	//(e13 * v.X) , (e23 * v.Y), (e33 * v.Z), (e43 * v.W)
				 m3 = _mm_mul_ps(m3, v1);	//(e14 * v.X) , (e24 * v.Y), (e34 * v.Z), (e44 * v.W)

				m0 = _mm_hadd_ps(m0, m1);
				m0 = _mm_hadd_ps(m0, m0);
				m2 = _mm_hadd_ps(m2, m3);
				m2 = _mm_hadd_ps(m2, m2);
				m0 = _mm_movehl_ps(m2, m0);

				PVector4df val;
				_mm_store_ps(val._Vec, m0);
				return val;
#else

				return PVector4df(v.X * e11 + v.Y * e21 + v.Z * e31 + v.W * e41,
					v.X * e12 + v.Y * e22 + v.Z * e32 + v.W * e42,
					v.X * e13 + v.Y * e23 + v.Z * e33 + v.W * e43,
					v.X * e14 + v.Y * e24 + v.Z * e34 + v.W * e44);
#endif
			}