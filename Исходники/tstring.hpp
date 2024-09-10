        inline
        int    IndexOf( const TString&  needle,
                              int              startIdx= 0,
                              enums::Case      sensitivity=  enums::Case::Sensitive )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0 )                           startIdx= 0;
                if ( startIdx + needle.Length() > length )    return -1;
                if ( needle.Length() == 0  )                  return  startIdx;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if (    startIdx < 0
                         || startIdx >= length
                         || needle.Length() == 0    )
                        dbgAStringAlibError( "Non checking and illegal parameters" );
                #endif
            }


            #if defined (__GLIBCXX__)
                const char* foundAt= sensitivity == enums::Case::Sensitive
                     ? strstr    ( ToCString() + startIdx, needle.ToCString() )
                     : strcasestr( ToCString() + startIdx, needle.ToCString() );
                return  foundAt != nullptr ?  foundAt - buffer  :   -1;
            #else
                if ( sensitivity == enums::Case::Sensitive )
                {
                    const char* foundAt=  strstr( ToCString() + startIdx, needle.ToCString() );
                    return  foundAt != nullptr ?  (int) (foundAt - buffer)  :   -1;
                }
                else
                    // there is no strcasestr in windows, we use the slower String version, non-checking
                    return IndexOfSubstring<false>( needle, startIdx , enums::Case::Ignore );
            #endif
        }