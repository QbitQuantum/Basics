TString::TString( const TString& s )
{
    data = NULL;

    const char *c = s.c_str();
    int len = s.Length();
    Realloc( len );

    if( len>0 )
        strcpy( data, c );
}