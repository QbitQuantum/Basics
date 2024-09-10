/**
 * 
 * Determine and set Grisbi locale as follows (in order of priority):
 * - Value of HKCU\SOFTWARE\GRISBI\LANG
 * - Value of %LANG% (LANG con content a LOCALE definition or a LCID value)
 * - Default user value
 * 
 * @return Does the function change the application context LANG value
 * @retval TRUE a value have set to LANG
 * @retval FALSE LANG has not been modified for any reason.
 * 
*/
gboolean win32_set_locale() 
{ /* {{{ */
    gchar* gzLocale = NULL;
    BOOL    bFound           = FALSE;
    
    // ---------------------------------------------------------------------
    // Grisbi language has been configured through the specific application
    // ---------------------------------------------------------------------
    // 1 - look into HKCU/SOFTWARE/GRISBI/LANG
    gzLocale = win32_strdup_registry(HKEY_CURRENT_USER,"SOFTWARE\\GRISBI","LANG",REG_SZ);
    bFound   = (BOOL)(gzLocale && (*gzLocale));
    
    // ---------------------------------------------------------------------
    // Try to find language setting using the LANG environment variable
    // ---------------------------------------------------------------------
    if(!bFound)
    {
		g_unsetenv("LANG");
        gzLocale = g_getenv("LANG");
        bFound   = (BOOL)(gzLocale && (*gzLocale));
        if (bFound)
        {
            // LANG can contain the Windows LCID instead of the LC_LOCALE value, in this case we need to convert it
            // LANG can the LCID given in decimal
            // LANG can the LCID given is hexadecimal
            // When LANG is the LCID its size is 3 or 4 and start with a digit
            // In other case we suppose LANG to be a valid LC_LOCALE value
            int len = strlen(gzLocale);
            if ( (len==3||len==4)&&(g_ascii_isdigit(*gzLocale))) 
            {
                    gzLocale = win32_lcid_to_lang(atoi(gzLocale));
                    bFound   = (BOOL)(gzLocale && (*gzLocale));
            }
        }
    
    }
    // ---------------------------------------------------------------------
    // Last change: retrieve current Windows value
    // ---------------------------------------------------------------------
    if ( (!bFound) || (!gzLocale) || ( (gzLocale) && (!(*gzLocale)) ) )
    {
        gzLocale = win32_lcid_to_lang(GetUserDefaultLCID());
    }

    if ((gzLocale)&&(*gzLocale))
    {
        bFound = TRUE;
        g_setenv("LANG",gzLocale,TRUE);
        g_free(gzLocale);
        gzLocale = NULL;
    }
    return bFound;
} /* }}} */