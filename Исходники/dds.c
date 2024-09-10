int
ldap_refresh(
    LDAP		*ld,
    struct berval	*dn,
    ber_int_t		ttl,
    LDAPControl	**sctrls,
    LDAPControl	**cctrls,
    int		*msgidp )
{
    struct berval	bv = { 0, NULL };
    BerElement	*ber = NULL;
    int		rc;

    assert( ld != NULL );
    assert( LDAP_VALID( ld ) );
    assert( dn != NULL );
    assert( msgidp != NULL );

    *msgidp = -1;

    ber = ber_alloc_t( LBER_USE_DER );

    if ( ber == NULL ) {
        ld->ld_errno = LDAP_NO_MEMORY;
        return ld->ld_errno;
    }

    ber_printf( ber, "{tOtiN}",
                LDAP_TAG_EXOP_REFRESH_REQ_DN, dn,
                LDAP_TAG_EXOP_REFRESH_REQ_TTL, ttl );

    rc = ber_flatten2( ber, &bv, 0 );

    if ( rc < 0 ) {
        rc = ld->ld_errno = LDAP_ENCODING_ERROR;
        goto done;
    }

    rc = ldap_extended_operation( ld, LDAP_EXOP_REFRESH, &bv,
                                  sctrls, cctrls, msgidp );

done:
    ;
    ber_free( ber, 1 );

    return rc;
}