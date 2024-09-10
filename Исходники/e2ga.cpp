	mv mv_compress(const float *c, float epsilon/*= 0.0*/, int gu /*= ...*/) {
		float cc[4];
		int cgu;
		compress(c, cc, cgu, epsilon, gu);
		return mv(cgu, cc);
	}