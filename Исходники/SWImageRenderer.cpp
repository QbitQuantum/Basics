			inline void MoveNext(int s) {
				if(s == 0) return;
				else if(s < 4){
					auto v = uv, st = uvStep;
					while(s--) {
						v = _mm_add_epi64(v, st);
					}
					uv = v;
				}
				else {
					// no SSE2 support for 64bit multiply, but
					// this isn't a big problem because this case is rare
					uvU += stepU * s;
					uvV += stepV * s;
				}
			}