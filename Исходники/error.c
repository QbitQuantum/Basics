/***********************************************************************
 *      ldap_result2error     (WLDAP32.@)
 *
 * Parse an LDAP message and return the error obtained from it.
 *
 * PARAMS
 *  ld    [I] Pointer to an LDAP context.
 *  res   [I] Pointer to an LDAPMessage structure.
 *  free  [I] Ask for the LDAPMessage structure to be freed.
 *
 * RETURNS
 *  Success: LDAP_SUCCESS
 *  Failure: An LDAP error code.
 *
 * NOTES
 *  If not asked for, use ldap_msgfree to free the LDAPMessage.
 */
ULONG CDECL WLDAP32_ldap_result2error( WLDAP32_LDAP *ld, WLDAP32_LDAPMessage *res, ULONG free )
{
    ULONG ret = LDAP_NOT_SUPPORTED;
#ifdef HAVE_LDAP
    int error;

    TRACE( "(%p, %p, 0x%08lx)\n", ld, res, free );

    if (!ld || !res) return ~0UL;

    ret = ldap_parse_result( ld, res, &error, NULL, NULL, NULL, NULL, free );

    if (ret == LDAP_SUCCESS)
        ret = error;
    else
        ret = ~0UL;

#endif
    return ret;
}