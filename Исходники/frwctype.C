int _Fr_iswlower(FrChar16 c)
{
#ifndef NO_WCTYPE
   return iswlower(c) ;
#else
   return Fr_is8bit(c) ? islower(c) : false ;
#endif /* NO_WCTYPE */
}