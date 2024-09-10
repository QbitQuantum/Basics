static char* ConsumeAttribute( const char** ppsz_subtitle, char** psz_attribute_value )
{
    const char* psz_subtitle = *ppsz_subtitle;
    char* psz_attribute_name;

    while (*psz_subtitle == ' ')
        psz_subtitle++;

    size_t attr_len = 0;
    char delimiter;

    while ( *psz_subtitle && isalpha( *psz_subtitle ) )
    {
        psz_subtitle++;
        attr_len++;
    }
    if ( !*psz_subtitle || attr_len == 0 )
        return NULL;
    psz_attribute_name = malloc( attr_len + 1 );
    if ( unlikely( !psz_attribute_name ) )
        return NULL;
    strncpy( psz_attribute_name, psz_subtitle - attr_len, attr_len );
    psz_attribute_name[attr_len] = 0;

    // Skip over to the attribute value
    while ( *psz_subtitle && *psz_subtitle != '=' )
        psz_subtitle++;
    // Skip the '=' sign
    psz_subtitle++;

    // Aknoledge the delimiter if any
    while ( *psz_subtitle && isspace( *psz_subtitle) )
        psz_subtitle++;

    if ( *psz_subtitle == '\'' || *psz_subtitle == '"' )
    {
        // Save the delimiter and skip it
        delimiter = *psz_subtitle;
        psz_subtitle++;
    }
    else
        delimiter = 0;

    // Skip spaces, just in case
    while ( *psz_subtitle && isspace( *psz_subtitle ) )
        psz_subtitle++;

    attr_len = 0;
    while ( *psz_subtitle && ( ( delimiter != 0 && *psz_subtitle != delimiter ) ||
                               ( delimiter == 0 && ( isalnum( *psz_subtitle ) || *psz_subtitle == '#' ) ) ) )
    {
        psz_subtitle++;
        attr_len++;
    }
    if ( unlikely( !( *psz_attribute_value = malloc( attr_len + 1 ) ) ) )
    {
        free( psz_attribute_name );
        return NULL;
    }
    strncpy( *psz_attribute_value, psz_subtitle - attr_len, attr_len );
    (*psz_attribute_value)[attr_len] = 0;
    // Finally, skip over the final delimiter
    if (delimiter != 0 && *psz_subtitle)
        psz_subtitle++;
    *ppsz_subtitle = psz_subtitle;
    return psz_attribute_name;
}