HqBool unicode_has_binary_property(UTF32 c,
                                   UTF32_Property which,
                                   HqBool *error_occured )
{
  HQASSERT(error_occured != NULL, "error_occured is NULL") ;
  HQASSERT((int)UCHAR_BINARY_START == (int)UTF32_BINARY_START,
           "icu and hqn enumerations appear to be out of synch") ;
  HQASSERT((int)UCHAR_STRING_LIMIT == (int)UTF32_STRING_LIMIT,
           "icu and hqn enumerations appear to be out of synch") ;

  *error_occured = FALSE ;

  if ( !unicode_icu_ready() ) {
    *error_occured = TRUE ;
    return FALSE ;
  }

  return (HqBool)u_hasBinaryProperty((UChar32)c, (UProperty)which) ;
}