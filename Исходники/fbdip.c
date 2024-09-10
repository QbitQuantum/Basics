void fbdip(int n3, int n4, float ****in, float **dip, int nit, float eta)
/*< omnidirectional dip estimation >*/
{
	int it, i1, j1, j2;
	double  norm, s1, c1;

	for(i1=0; i1<n1*n2; i1++)
		p[0][i1] = p0;

	for (it=0; it<nit; it++)
	{
		for(i1=0; i1<n1*n2; i1++)
		{
			s1 = cimagf(p[0][i1]);
			c1 = crealf(p[0][i1]);
			u1[0][i1] = 0.0;
			u2[0][i1] = 0.0;
			u3[0][i1] = 0.0;
			for(j2=0; j2<n4; j2++)
			for(j1=0; j1<n3; j1++)
			{
				if((j1+j2)%2==0) continue;
				u1[0][i1] += 2.0*in[j2][j1][0][i1]*POW(s1, j1)*POW(c1,j2);
				u2[0][i1] += 2.0*in[j2][j1][0][i1]*j1*POW(s1, j1-1)*POW(c1,j2);
				u3[0][i1] += 2.0*in[j2][j1][0][i1]*POW(s1, j1)*j2*POW(c1,j2-1);
			}
		}

		if(verb)
		{
			for(i1=0, norm=0.0; i1<n1*n2; i1++)
				norm += (u1[0][i1]*u1[0][i1]);
			sf_warning("res1 %d %g", it+1, sqrtf(norm/n1/n2));
		}

		if(use_divn)
		{
			for(i1=0, c1=0.0, s1=0.0; i1<n1*n2; i1++)
			{
				c1 += (u2[0][i1]*u2[0][i1]);
				s1 += (u3[0][i1]*u3[0][i1]);
			}
			c1=sqrtf(c1/(n1*n2));
			s1=sqrtf(s1/(n1*n2));
			for(i1=0; i1<n1*n2; i1++)
			{
				u1[0][i1] /= c1;
				u2[0][i1] /= c1;
			}
			sf_divn(u1[0], u2[0], u4[0]);
			for(i1=0; i1<n1*n2; i1++)
			{
				u1[0][i1] *= c1/s1;
				u3[0][i1] /= s1;
			}
			sf_divn(u1[0], u3[0], u5[0]);
		}else{
			for(i1=0; i1<n1*n2; i1++)
			{
				u4[0][i1] = divn(u1[0][i1], u2[0][i1]);
				u5[0][i1] = divn(u1[0][i1], u3[0][i1]);
			}
		}
		for(i1=0; i1<n1*n2; i1++)
		{
			p[0][i1] -= eta * sf_cmplx(u5[0][i1], u4[0][i1]);
			p[0][i1] = p[0][i1]*r/(cabsf(p[0][i1])+ 1E-15);
		}

	}
	for(i1=0; i1<n1*n2; i1++)
		dip[0][i1] = atan(tan(cargf(p[0][i1])));
}