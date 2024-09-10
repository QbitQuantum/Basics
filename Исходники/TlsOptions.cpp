void TlsOptions::setOption( tls_option opt, void *value ) const {
    int ret = ldap_set_option( m_ld, optmap[opt].optval, value);
    if ( ret != LDAP_OPT_SUCCESS )
    {
        if ( ret != LDAP_OPT_ERROR ){
            throw( LDAPException( ret ));
        } else {
            throw( LDAPException( LDAP_PARAM_ERROR, "error while setting TLS option" ) );
        }
    }
    this->newCtx();
}