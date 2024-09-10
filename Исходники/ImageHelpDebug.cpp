bool CPEDebug::Initialize()
{
	if (m_fIsInitialized)
		return true;				// nur einmal initialisieren
	else if (m_fTriedToInitialize)
		return false;				// schon mal versucht, jedoch fehlgeschlagen
	m_fTriedToInitialize = true;

// Since the largest symbol that the MS code generators can handle
//  is 256 that is all that is needed.
	ATLTRY(m_pSymbol = (IMAGEHLP_SYMBOL *)new BYTE [sizeof(IMAGEHLP_SYMBOL) + 256]);
	if (NULL == m_pSymbol) return false;

// SymbolEngine initialisieren
	if (m_SymEngine.SymInitialize (GetCurrentProcess(), NULL, TRUE)) {
    //  Set the symbol engine to load line information.  This must be
    //  because the symbol engine does not load source-lines by default.
    //  I also turn on the OMAP lookups so that the super-special OMAP
    //  moved blocks will get looked at as well.  Trust me, don't ask.
	    SymSetOptions (SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST);
		m_fIsInitialized = true;
		return true;
	}
	return false;
}