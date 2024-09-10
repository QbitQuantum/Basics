    char* char_traits::StrUpper( char* psz )
    {
#ifdef _MBCS
      return (char*)_mbsupr((unsigned char*)psz);
#else
      return strupr(psz);
#endif
    }