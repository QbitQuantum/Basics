  bool parse( sim_t*, const std::string& n, const std::string& v ) const override
  {
    if ( n != name() )
      return false;
#if defined( SC_WINDOWS ) && defined( SC_VS )
    _ref = _strtoui64( v.c_str(), nullptr, 10 );
#else
    _ref = strtoull( v.c_str(), nullptr, 10 );
#endif
    return true;
  }