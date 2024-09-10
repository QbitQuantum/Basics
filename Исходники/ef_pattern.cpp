void CPatternFunction::vfLoadEF(LPCSTR caFileName)
{
	string_path		caPath;
	if (!FS.exist(caPath,"$game_ai$",caFileName)) {
		Msg			("! Evaluation function : File not found \"%s\"",caPath);
		R_ASSERT	(false);
		return;
	}
	
	IReader			*F = FS.r_open(caPath);
	F->r			(&m_tEFHeader,sizeof(SEFHeader));

	if (EFC_VERSION != m_tEFHeader.dwBuilderVersion) {
		FS.r_close	(F);
		Msg			("! Evaluation function (%s) : Not supported version of the Evaluation Function Contructor",caPath);
		R_ASSERT	(false);
		return;
	}

	F->r			(&m_dwVariableCount,sizeof(m_dwVariableCount));
	m_dwaAtomicFeatureRange = xr_alloc<u32>(m_dwVariableCount);
	ZeroMemory		(m_dwaAtomicFeatureRange,m_dwVariableCount*sizeof(u32));
	u32				*m_dwaAtomicIndexes = xr_alloc<u32>(m_dwVariableCount);
	ZeroMemory		(m_dwaAtomicIndexes,m_dwVariableCount*sizeof(u32));

	for (u32 i=0; i<m_dwVariableCount; ++i) {
		F->r(m_dwaAtomicFeatureRange + i,sizeof(u32));
		if (i)
			m_dwaAtomicIndexes[i] = m_dwaAtomicIndexes[i-1] + m_dwaAtomicFeatureRange[i-1];
	}

	m_dwaVariableTypes = xr_alloc<u32>(m_dwVariableCount);
	F->r			(m_dwaVariableTypes,m_dwVariableCount*sizeof(u32));

	F->r			(&m_dwFunctionType,sizeof(u32));

	F->r			(&m_fMinResultValue,sizeof(float));
	F->r			(&m_fMaxResultValue,sizeof(float));

	F->r			(&m_dwPatternCount,sizeof(m_dwPatternCount));
	m_tpPatterns	= xr_alloc<SPattern>(m_dwPatternCount);
	m_dwaPatternIndexes = xr_alloc<u32>(m_dwPatternCount);
	ZeroMemory		(m_dwaPatternIndexes,m_dwPatternCount*sizeof(u32));
	m_dwParameterCount = 0;
	for (u32 i=0; i<m_dwPatternCount; ++i) {
		if (i)
			m_dwaPatternIndexes[i] = m_dwParameterCount;
		F->r		(&(m_tpPatterns[i].dwCardinality),sizeof(m_tpPatterns[i].dwCardinality));
		m_tpPatterns[i].dwaVariableIndexes = xr_alloc<u32>(m_tpPatterns[i].dwCardinality);
		F->r		(m_tpPatterns[i].dwaVariableIndexes,m_tpPatterns[i].dwCardinality*sizeof(u32));
		u32			m_dwComplexity = 1;
		for (int j=0; j<(int)m_tpPatterns[i].dwCardinality; ++j)
			m_dwComplexity *= m_dwaAtomicFeatureRange[m_tpPatterns[i].dwaVariableIndexes[j]];
		m_dwParameterCount += m_dwComplexity;
	}
	
	m_faParameters	= xr_alloc<float>(m_dwParameterCount);
	F->r			(m_faParameters,m_dwParameterCount*sizeof(float));
	FS.r_close		(F);

	m_dwaVariableValues = xr_alloc<u32>(m_dwVariableCount);
	
	xr_free			(m_dwaAtomicIndexes);
    
	ef_storage().m_fpaBaseFunctions[m_dwFunctionType] = this;
	
	_splitpath		(caPath,0,0,m_caName,0);

	// Msg			("* Evaluation function \"%s\" is successfully loaded",m_caName);
}