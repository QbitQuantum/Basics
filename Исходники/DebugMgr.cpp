void CDebugMgr::RecordStack(const CONTEXT* pContext)
{
    m_pchBuffer += wsprintf(m_pchBuffer,"\nCall stack:\n" );

    m_pchBuffer += wsprintf(m_pchBuffer,"Address   Frame     Logical addr  Module\n" );

    DWORD pc = pContext->Eip;
    PDWORD pFrame, pPrevFrame;
    
    pFrame = (PDWORD)pContext->Ebp;

    do
    {
        TCHAR szModule[MAX_PATH] = "";
        DWORD section = 0, offset = 0;

        FindLogicalAddress((PVOID)pc, szModule,sizeof(szModule),section,offset );

        m_pchBuffer += wsprintf(m_pchBuffer,"%08X  %08X  %04X:%08X %s",
                  pc, pFrame, section, offset, szModule );

		// See if we need to spit out symbol/source/line info

		if ( m_dwOptions & DEBUGMGR_RESOLVESYMBOLS )
		{
			// Generate the name of the map file

			TCHAR szMap[MAX_PATH] = "";
			wsprintf(szMap, szModule);
			wsprintf(&szMap[lstrlen(szMap)-3], "MAP");

			TCHAR szSymbol[256] = "<unknown>";
			TCHAR szUnmangledSymbol[1024] = "<unknown>";
			TCHAR szObject[128] = "<unknown>";

			if ( FindSymbol(szMap, section, offset, szSymbol, szObject) )
			{
				if ( m_dwOptions & DEBUGMGR_UNMANGLESYMBOLS && *szSymbol == '?' )
				{
					UnDecorateSymbolName(szSymbol, szUnmangledSymbol, 1024, UNDNAME_COMPLETE);
				}
				else
				{
					wsprintf(szUnmangledSymbol, szSymbol);
				}
			}

			m_pchBuffer += wsprintf(m_pchBuffer, " in function %s in object file %s", szUnmangledSymbol, szObject);

			if ( m_dwOptions & DEBUGMGR_RESOLVESOURCELINE )
			{
				TCHAR szSource[256];
				TCHAR szLine[256];

				if ( FindSourceLine(szMap, szObject, section, offset, szSource, szLine) )
				{
					m_pchBuffer += wsprintf(m_pchBuffer, " at Line %s of %s\n", szLine, szSource);
				}
				else
				{
					m_pchBuffer += wsprintf(m_pchBuffer, " at Line ??? of ???\n");
				}
			}
			else
			{
				m_pchBuffer += wsprintf(m_pchBuffer, "\n\n");
			}
		}
		else
		{
			m_pchBuffer += wsprintf(m_pchBuffer, "\n");
		}

		// Go on to the next stack frame

        pc = pFrame[1];

        pPrevFrame = pFrame;

        pFrame = (PDWORD)pFrame[0]; // proceed to next higher frame on stack

        if ( (DWORD)pFrame & 3 )    // Frame pointer must be aligned on a
            break;                  // DWORD boundary.  Bail if not so.

        if ( pFrame <= pPrevFrame )
            break;

        // Can two DWORDs be read from the supposed frame address?          
        if ( IsBadWritePtr(pFrame, sizeof(PVOID)*2) )
            break;

    } while ( 1 );
}