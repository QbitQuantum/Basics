    static InternedSymbol const * SearchBucket( SymbolBucket const & bucket,
                                                wchar_t const * const str,
                                                unsigned int const len )
    {
        BOOST_FOREACH( InternedSymbol const * pSymbol, bucket )
        {
            if( (pSymbol->m_length == len) &&
                (wmemcmp( pSymbol->m_name, str, len ) == 0) )
            {   // Matched symbol name
                return pSymbol;
            }
        }

        return 0;
    }