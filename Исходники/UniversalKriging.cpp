	double CUniversalKriging::Evaluate(const CGridPoint& pt, int iXval)const
	{
		//if variogram is not initialised correckly, we retuern no data;
		if (!m_pVariogram->IsInit())
			return m_param.m_noData;

		// Find the nearest samples: 
		CGridPointVector va;

		Init_va(pt, iXval, va);

		int mdt = GetMDT();
		// Test number of samples found: 
		// Test if there are enough samples to estimate all drift terms: 
		if ((int)va.size() < m_p.m_nbPoint || (int)va.size() <= mdt)
			return m_param.m_noData;

		if ( /*iXval<0 &&*/ va[0].GetDistance(pt) > m_param.m_maxDistance)
			return m_param.m_noData;

		// There are enough samples - proceed with estimation. 
		// Go ahead and set up the OK portion of the kriging matrix: 

		NEWMAT::ColumnVector r;
		NEWMAT::Matrix a;

		Init_a(pt, va, a);
		Init_r(pt, va, r);

		// If estimating the trend then reset all the right hand side terms=0.0:
		if (m_p.m_bTrend)
			r = 0;

		//copy r to compute variance
		NEWMAT::ColumnVector rr(r);


		// Solve the kriging system: 
		int neq = mdt + int(va.size());

		//reduce the matrix until the 2/3 of the number of neightbor
		bool bOK = false;
		while (!bOK && neq >= mdt + m_p.m_nbPoint * 2 / 3)//by RSA 25/10/2010
		{
			Try
			{
				a = a.i();
				bOK = true;
			}
				Catch(NEWMAT::Exception)
			{
				OutputDebugStringW(L"a=a.i() failled; Reduce number of point");

				Init_a(pt, va, a);
				Init_r(pt, va, r);

				neq--;
				int firstRow = 1 + mdt + int(va.size()) - neq;
				a = a.SubMatrix(firstRow, a.Nrows(), firstRow, a.Ncols());
				r = r.SubMatrix(firstRow, r.Nrows(), 1, 1);
			}

			if (m_pAgent && m_pAgent->TestConnection(m_hxGridSessionID) == S_FALSE)
				throw(CHxGridException());

		}

		//if we don't solve system, return missing
		if (!bOK)
			return m_param.m_noData;


		NEWMAT::ColumnVector s = a*r;


		CDiscretisation m_discr;
		m_discr.Initialization(pt, *m_pVariogram, m_p, m_param.m_bFillNugget);

		// Compute the solution: 
		double uuk = 0.0;
		double ukv = m_discr.cbb;
		for (int j = 0; j < neq; j++)
		{
			ukv -= s[j] * rr[j];
			if (j < (int)va.size())
				uuk += s[j] * (m_prePostTransfo.Transform(va[j].m_event) - m_p.m_SKmean);
		}

		uuk += m_p.m_SKmean;
		uuk = m_prePostTransfo.InvertTransform(uuk, m_param.m_noData);
		//
		if ( /*iXval<0 &&*/ m_param.m_bRegionalLimit  && uuk > m_param.m_noData)
		{
			CStatistic stat;
			for (size_t i = 0; i < va.size(); i++)
				stat += va[i].m_event;

			bool bOutside = uuk<stat[LOWEST] - m_param.m_regionalLimitSD*stat[STD_DEV] || uuk>stat[HIGHEST] + m_param.m_regionalLimitSD*stat[STD_DEV];
			if (bOutside)
			{
				if (m_param.m_bRegionalLimitToBound)
					uuk = min(stat[HIGHEST] + m_param.m_regionalLimitSD*stat[STD_DEV], max(stat[LOWEST] - m_param.m_regionalLimitSD*stat[STD_DEV], uuk));
				else
					uuk = m_param.m_noData;
			}
		}

		if ( /*iXval<0 &&*/ m_param.m_bGlobalLimit && uuk > m_param.m_noData)
		{
			bool bOutside = uuk<m_stat[LOWEST] - m_param.m_globalLimitSD*m_stat[STD_DEV] || uuk>m_stat[HIGHEST] + m_param.m_globalLimitSD*m_stat[STD_DEV];
			if (bOutside)
			{
				if (m_param.m_bGlobalLimitToBound)
					uuk = min(m_stat[HIGHEST] + m_param.m_globalLimitSD*m_stat[STD_DEV], max(m_stat[LOWEST] - m_param.m_globalLimitSD*m_stat[STD_DEV], uuk));
				else
					uuk = m_param.m_noData;
			}
		}

		if ( /*iXval<0 &&*/ m_param.m_bGlobalMinMaxLimit && uuk > m_param.m_noData)
		{
			bool bOutside = uuk<m_param.m_globalMinLimit || uuk>m_param.m_globalMaxLimit;
			if (bOutside)
			{
				if (m_param.m_bGlobalMinMaxLimitToBound)
					uuk = min(m_param.m_globalMaxLimit, max(m_param.m_globalMinLimit, uuk));
				else
					uuk = m_param.m_noData;
			}
		}


		return uuk;
	}