/***********************************************************************
 *      ldap_value_free_len     (WLDAP32.@)
 *
 * Free an array of berval structures.
 *
 * PARAMS
 *  vals  [I] Array of berval structures.
 *
 * RETURNS
 *  Success: LDAP_SUCCESS
 *  Failure: An LDAP error code.
 */
ULONG CDECL WLDAP32_ldap_value_free_len( struct WLDAP32_berval **vals )
{
#ifdef HAVE_LDAP

    TRACE( "(%p)\n", vals );
    ldap_value_free_len( (struct berval **)vals );

#endif
    return WLDAP32_LDAP_SUCCESS;
}