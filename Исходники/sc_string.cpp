sc_string_old
operator+( const char* s, const sc_string_old& t )
{
    int len = strlen(s);
    sc_string_rep* r = new sc_string_rep( len + t.length() + 1 );
    strcpy( r->str, s );
    strcpy( r->str + len, t );
    return sc_string_old(r);
}