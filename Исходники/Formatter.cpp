std::string AppSecInc::Formatter::FormatHexA(byte * szObj, unsigned long nNum)
{
    std::string to;
	const int BUF_SIZE = 1024;
    char szTemp[ BUF_SIZE ];
    char szMsg[BUF_SIZE];

    unsigned long i;
    unsigned long j;
    unsigned long max;                

	to.clear();
    
    if ( szObj == NULL || nNum <= 0 )
	{
		return to;
	}

    max    = nNum;
    if ( ( nNum % 8 ) != 0 )
    {
        max += 8 - ( nNum % 8 );
    }
    
    for ( i = 0; i < max; i += 16 )
    {
        SecureZeroMemory(szTemp, sizeof(szTemp));
        SecureZeroMemory(szMsg, sizeof(szMsg));

        StringCchPrintfA(szTemp, BUF_SIZE, "%5.5x\t", i);
        StringCchCopyA(szMsg, BUF_SIZE, szTemp);
    
        for( j = 0; j < 16; j++ )
        {
            if ( ( j + i ) < nNum )
            {
                SecureZeroMemory(szTemp, sizeof(szTemp));
                StringCchPrintfA(szTemp, BUF_SIZE, "%.2x ", szObj[ j + i ]);                    

                if ( strlen( szTemp ) > 3 )
                {
                    szTemp[ 0 ]    = szTemp[ strlen( szTemp ) - 3 ];
                    szTemp[ 1 ]    = szTemp[ strlen( szTemp ) - 2 ];
                    szTemp[ 2 ]    = ' ';
                    szTemp[ 3 ]    = '\0';
                }
            }
            else
            {
                SecureZeroMemory(szTemp, sizeof(szTemp));
                StringCchCopyA(szTemp, BUF_SIZE, "   ");
            }

            StringCchCatA(szMsg, BUF_SIZE, szTemp);                    
        }
        
        StringCchCatA(szMsg, BUF_SIZE, " ");
        SecureZeroMemory(szTemp, sizeof(szTemp));

        for( j = 0; j < 16 && ( j + i ) < nNum; j++ )
        {
            if (    ( szObj[ j + i ] > 31 )    &&
                    ( szObj[ j + i ] < 127 )    )
            {
                szTemp[ 0 ]    = szObj[ j + i ];
                szTemp[ 1 ]    = '\0';                    
                StringCchCatA(szMsg, BUF_SIZE, szTemp);
            }
            else
            {
                StringCchCatA(szMsg, BUF_SIZE, ".");
            }
        }

		if (to.length() > 0) to.append("\n");
		to.append(szMsg);
    }
    return to;
}