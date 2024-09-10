int
init_ldap(char * host, int port)
{
    int status = ldap_initialize(&LDAP_handle,host);
    if(status != LDAP_SUCCESS)
    {
        LOG(PURGER_LOG_ERR,"Error: unable to create LDAP handle.");
        return -1;
    }
    int version = LDAP_VERSION3;
    ldap_set_option(LDAP_handle, LDAP_OPT_PROTOCOL_VERSION, (void*)&version);

}