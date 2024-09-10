// The native fpclassify broken for long doubles with aCC
// use portable one instead....
inline int fpclassify BOOST_NO_MACRO_EXPAND(long double t)
{
   return BOOST_FPCLASSIFY_PREFIX fpclassify(t);
}