size_t CRowSolution<T>::findSolution(const T *pSolution, size_t i, size_t iMax, const CSolutionPerm *pSolPerm, size_t &lastCanonIdx, size_t *pNextSolutionIdx) const
{
	const uchar *pCanonFlags = pSolPerm->canonFlags();
	const size_t len = solutionSize() * sizeof(*pSolution);
	while (++i < iMax && MEMCMP(pSolution, firstSolution() + pSolPerm->GetAt(i) * solutionSize(), len)) {
		if (*(pCanonFlags + i) == 1) {
			if (lastCanonIdx == SIZE_MAX)
				*pNextSolutionIdx = i;

			lastCanonIdx = i;
		}
	}

	return i;
}