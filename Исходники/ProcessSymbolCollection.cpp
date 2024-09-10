/** 
 * 
 * Enumerates one module in a process
 * 
 * @param       dwDllBases_i - Base address of module to enumerate
 * @return      bool         - Return true
 * @exception   Nil
 * @see         Nil
 * @since       1.0
 */
bool ProcessSymbolCollection::EnumerateModuleSymbols( DWORD dwDllBases_i, 
                                                      SymbolCollection*& pModSymColl_o,
                                                      LPCTSTR lpctszModuleFileName_i,
                                                      const DWORD dwModuleSize_i,
                                                      const bool bRefresh_i )
{
    UNREFERENCED_PARAMETER( lpctszModuleFileName_i );
    UNREFERENCED_PARAMETER( dwModuleSize_i );

    bool bFound = false;
    if( bRefresh_i )
    {
        // Find in map
        bFound = m_ModSymMap.Lookup( dwDllBases_i, pModSymColl_o ) != FALSE;

        if( bFound )
        {
            // Remove entry from map
            m_ModSymMap.RemoveKey( dwDllBases_i );
            delete pModSymColl_o;
        }// End if
    }// End if

    if( bRefresh_i || !m_ModSymMap.Lookup( dwDllBases_i, pModSymColl_o ))
    {
        // Allocate a new module symbol collection
        pModSymColl_o = new SymbolCollection;
    	SymEnumSymbols( m_hProcess, 
						dwDllBases_i, 
						0, 
						EnumModuleSymbolsCB,  
						pModSymColl_o );

        // Add this entry to map
        m_ModSymMap[dwDllBases_i] = pModSymColl_o;
    }// End if

    return true;
}// End Enumerate