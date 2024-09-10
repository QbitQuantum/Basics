bool exists_social( const char *social )
{
    SOCIAL_DATA *soc;
    list<SOCIAL_DATA *>::iterator li;
    char search[MSL] = {'\0'};
    char tmp[MSL] = {'\0'};
    string str;
    
    if( !isalpha(*social) )
        return false;

    /* Check the cache list before trying to load from file --Kline */
    for( li = social_list.begin(); li != social_list.end(); li++ )
    {
        soc = *li;
        if( soc->name.find(social) != string::npos )
            return true;
    }
    
    snprintf( search, MSL, "find %s%s/ -iname %s\\*.%s -printf '%%f '", SOCIAL_DIR, initial(social), social, SOCIAL_EXT );
    snprintf( tmp, MSL, "%s", _popen(search) );
    str = tmp;

    if( str.empty() )
        return false;
    
    return true;
}