bool StatsSet::getInt64( const char *name, long long int *val )
{
    std::wstring value;
    std::string sname( name );
    std::map<std::string, std::wstring>::const_iterator iter = m_map.find( sname );
    if( iter == m_map.end() )
    {
        throw Exception( "StatsSet: trying to get non-existent Int64 var [%s] with no default value!", name );
        //return false; // warning C4702: unreachable code
    }
    value = iter->second;
    long long int i64 = 0;
    int r = swscanf( value.c_str(), L"%I64d", &i64 );
    if( r == 1 )
    {
        (*val) = i64;
        return true;
    }
    throw Exception( "StatsSet.getInt: failed to scanf %%I64d from [%s]=[%S]", name, value.c_str() );
}