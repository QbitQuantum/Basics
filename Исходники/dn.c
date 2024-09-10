/***********************************************************************
 *      ldap_ufn2dnA     (WLDAP32.@)
 *
 * See ldap_ufn2dnW.
 */
ULONG CDECL ldap_ufn2dnA( PCHAR ufn, PCHAR *dn )
{
    ULONG ret = WLDAP32_LDAP_SUCCESS;
#ifdef HAVE_LDAP
    PWCHAR ufnW = NULL, dnW = NULL;

    TRACE( "(%s, %p)\n", debugstr_a(ufn), dn );

    if (!dn) return WLDAP32_LDAP_PARAM_ERROR;

    *dn = NULL;

    if (ufn) {
        ufnW = strAtoW( ufn );
        if (!ufnW) return WLDAP32_LDAP_NO_MEMORY;
    }

    ret = ldap_ufn2dnW( ufnW, &dnW );

    if (dnW) {
        *dn = strWtoA( dnW );
        if (!*dn) ret = WLDAP32_LDAP_NO_MEMORY;
    }

    strfreeW( ufnW );
    ldap_memfreeW( dnW );

#endif
    return ret;
}