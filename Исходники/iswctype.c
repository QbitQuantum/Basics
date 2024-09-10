/* Determine if the given character is of the specified type. */
_WCRTLINK int iswctype( wint_t wc, wctype_t desc )
{
    switch( desc ) {
    case WCTYPE_ALNUM:   return( iswalnum( wc ) );
    case WCTYPE_ALPHA:   return( iswalpha( wc ) );
    case WCTYPE_BLANK:   return( iswblank( wc ) );
    case WCTYPE_CNTRL:   return( iswcntrl( wc ) );
    case WCTYPE_DIGIT:   return( iswdigit( wc ) );
    case WCTYPE_GRAPH:   return( iswgraph( wc ) );
    case WCTYPE_LOWER:   return( iswlower( wc ) );
    case WCTYPE_PRINT:   return( iswprint( wc ) );
    case WCTYPE_PUNCT:   return( iswpunct( wc ) );
    case WCTYPE_SPACE:   return( iswspace( wc ) );
    case WCTYPE_UPPER:   return( iswupper( wc ) );
    case WCTYPE_XDIGIT:  return( iswxdigit( wc ) );
    default:             return( 0 );
    }
}