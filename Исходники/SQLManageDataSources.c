/*! 
 * \brief   Get the short name of the UI plugin.
 * 
 *          The short name is the file name without path or file extension.
 *
 *          We silently prepend "lib" here as well.
 *
 * \param   pszName     Place to put short name. Should be FILENAME_MAX bytes. 
 * \param   pszUI       Our generic window handle.
 * 
 * \return  char*       pszName returned for convenience.
 */
char *_getUIPluginName( char *pszName, char *pszUI )
{
    *pszName = '\0';

    /* is it being provided by caller? */
    if ( pszUI && *pszUI )
    {
        sprintf( pszName, "lib%s", pszUI );
        return pszName;
    }

    /* is it being provided by env var? */
    {
        char *pEnvVar = getenv( "ODBCINSTUI" );
        if ( pEnvVar )
        {
            sprintf( pszName, "lib%s", pEnvVar );
            return pszName;
        }
    }

    /* is it being provided by odbcinst.ini? */
    {
        char sz[FILENAME_MAX];
        *sz='\0';
        SQLGetPrivateProfileString( "ODBC", "ODBCINSTUI", "", sz, FILENAME_MAX, "odbcinst.ini" );
        if ( *sz )
        {
            sprintf( pszName, "lib%s", sz );
            return pszName;
        }
    }

    /* default to qt4 */
    strcpy( pszName, "libodbcinstQ4" );

    return pszName;
}