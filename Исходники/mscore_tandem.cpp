double mscore_tandem::dot(unsigned long *_v)
{
	float fScore = 0.0;
	unsigned long a = 0;
	unsigned long lCount = 0;
	long lType = 0;
	vector<MIType>::iterator itType = m_vmiType[m_lId].begin();
	// tType and tTypeSize were added in 2006.09.01 to correct a problem
	// created by VC++ 2005. This new version uses a strict bounds checking
	// style for STL iterators, that cause a run time error if an iterator
	// longer than .end() is produced by incrementing the iterator.
	size_t tType = 0;
	const size_t tTypeSize = m_vmiType[m_lId].size();
	unsigned long *pType = NULL;
	if(!m_pplType[m_lId])	{
		m_pplType[m_lId] = new unsigned long[tTypeSize];
		pType = m_pplType[m_lId];
		while(tType < tTypeSize)	{
			pType[tType] = itType->m_lM;
			++itType;
			tType++;
		}
	}
	else	{
		pType = m_pplType[m_lId];
	}
	itType = m_vmiType[m_lId].begin();
	tType = 0;
	size_t tStep = (size_t)(0.5 + (double)tTypeSize/(double)m_lCount);
	if(tStep < 1)	{
		tStep = 1;
	}
	unsigned long lSeq = m_plSeq[a];
	while(lSeq != 0 && tType != tTypeSize)	{
		lType = 0;
		if(*pType < lSeq)	{
			lType = 1;
			// Generally lots more spectrum peaks than sequence peaks.  Trying
			// large steps first helps reduce performance hit for this operation.
			// This is were the iterator bounds checking failed in VC++ 2005.
			// By checking the size first, the iterator is not evaluated and
			// does not produce the failure.
			while (tType+tStep < tTypeSize && *(pType+tStep) < lSeq) {
				tType += tStep;
				pType += tStep;
			}
			do {
				tType++;
				pType++;
			} while(tType < tTypeSize && *(pType) < lSeq);
		}
		else if(*pType > lSeq)	{
			do {
				a++;
				lSeq = m_plSeq[a];
			} while(*pType > lSeq && lSeq != 0);
		}
		if(lSeq == 0 || tType == tTypeSize)	{
			break;
		}
		if(*pType == lSeq)	{
//			if((itType+tType)->m_fI > 0.0 && m_pfSeq[a] > 0.0)	{
				m_pafI[lCount] = (itType+tType)->m_fI;
				m_pafSeq[lCount] = m_pfSeq[a];
				lCount++;
//			}
		}
		if(lType)	{
			a++;
			lSeq = m_plSeq[a];
		}
		else	{
			tType++;
			pType++;
		}
	}
	*_v = lCount;
	if(lCount == 0)	{
		return fScore;
	}
#ifdef MSVC
	if(!m_uiSimd)	{
		for(a = 0; a < lCount; a++)	{
			fScore += m_pafI[a] * m_pafSeq[a];
		}
		return fScore;
	}
	if(lCount < 5)	{
		for(a = 0; a < lCount; a++)	{
			fScore += m_pafI[a] * m_pafSeq[a];
		}
		return fScore;
	}
	// align the arrays to 4 float boundary
	for(a = 0; lCount % 4 != 0; a++)	{
		m_pafI[lCount] = 0.0;
		m_pafSeq[lCount] = 0.0;
		lCount++;
	}
	// create compatible pointers
	__m128* pSum = (__m128*) m_pafSum;
	__m128* pI = (__m128*) m_pafI;
	__m128* pS = (__m128*) m_pafSeq;
	__m128 Sum = _mm_set1_ps(0.0);
	__m128 S1 = _mm_set1_ps(0.0);
	unsigned int n = lCount/4;
	// perform intrinsic calls for SIMD registers

	for(a = 0; a < n; a++)	{
		S1 = _mm_mul_ps(*pI,*pS);
		Sum = _mm_add_ps(Sum,S1);
		pI++;
		pS++;
	}
	m_um128.m = Sum;
	fScore = m_um128.f[0] + m_um128.f[1] + m_um128.f[2] + m_um128.f[3];
#else
	for(a = 0; a < lCount; a++)	{
		fScore += m_pafI[a] * m_pafSeq[a];
	}
#endif
	return (fScore);
}