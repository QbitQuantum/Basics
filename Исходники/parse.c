ULONG CDECL ldap_parse_referenceW( WLDAP32_LDAP *ld, WLDAP32_LDAPMessage *message,
    PWCHAR **referrals )
{
    ULONG ret = LDAP_NOT_SUPPORTED;
#ifdef HAVE_LDAP_PARSE_REFERENCE
    char **referralsU = NULL;

    TRACE( "(%p, %p, %p)\n", ld, message, referrals );

    if (!ld) return ~0UL;
    
    ret = ldap_parse_reference( ld, message, &referralsU, NULL, 0 );

    *referrals = strarrayUtoW( referralsU );
    ldap_memfree( referralsU );

#endif
    return ret;
}