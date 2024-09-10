inline bool sc_isfinite( T x )
{
#if defined ( SC_VS ) && SC_VS < 12 // std::isfinite was added in vs2013
  return _finite( x ) != 0;
#else
  return std::isfinite( x );
#endif
}