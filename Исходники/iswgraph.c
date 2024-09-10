int iswgraph( wint_t wc )
{
    return iswctype( wc, _PDCLIB_CTYPE_GRAPH );
}