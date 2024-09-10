// Insert glyph sheets
UINT STDMETHODCALLTYPE CFW1GlyphAtlas::InsertSheet(IFW1GlyphSheet *pGlyphSheet) {
	if(pGlyphSheet == NULL)
		return 0xffffffff;
	
	UINT sheetIndex = 0xffffffff;
	
	EnterCriticalSection(&m_glyphSheetsCriticalSection);
	if(m_sheetCount < m_maxSheetCount) {
		pGlyphSheet->AddRef();
		
		sheetIndex = m_sheetCount;
		
		m_glyphSheets[sheetIndex] = pGlyphSheet;
		
		_WriteBarrier();
		MemoryBarrier();
		
		++m_sheetCount;
		
		// Restrict the number of open sheets
		UINT numActiveSheets = 4;
		
		if(m_sheetCount > m_currentSheetIndex + numActiveSheets) {
			m_glyphSheets[m_currentSheetIndex]->CloseSheet();
			
			++m_currentSheetIndex;
		}
	}
	LeaveCriticalSection(&m_glyphSheetsCriticalSection);
	
	return sheetIndex;
}