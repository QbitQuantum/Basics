/***********************************************************************
 *      ldap_parse_page_controlA      (WLDAP32.@)
 */
ULONG CDECL ldap_parse_page_controlA( WLDAP32_LDAP *ld, PLDAPControlA *ctrls,
    ULONG *count, struct WLDAP32_berval **cookie )
{
    ULONG ret = WLDAP32_LDAP_NOT_SUPPORTED;
#ifdef HAVE_LDAP
    LDAPControlW **ctrlsW = NULL;

    TRACE( "(%p, %p, %p, %p)\n", ld, ctrls, count, cookie );

    if (!ld || !ctrls || !count || !cookie)
        return WLDAP32_LDAP_PARAM_ERROR;

    ctrlsW = controlarrayAtoW( ctrls );
    if (!ctrlsW) return WLDAP32_LDAP_NO_MEMORY;

    ret = ldap_parse_page_controlW( ld, ctrlsW, count, cookie );
    controlarrayfreeW( ctrlsW );
 
#endif
    return ret;
}