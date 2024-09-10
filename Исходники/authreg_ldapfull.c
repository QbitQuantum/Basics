/** connect to ldap and bind as data->binddn */
static int _ldapfull_connect_bind(moddata_t data)
{
    if(data->ld != NULL && data->binded ) {
        return 0;
    }

    if( _ldapfull_connect(data) ) {
        return 1;
    }

    if(ldap_simple_bind_s(data->ld, data->binddn, data->bindpw))
    {
        log_write(data->ar->c2s->log, LOG_ERR, "ldap: bind as '%s' failed: %s", data->binddn, ldap_err2string(_ldapfull_get_lderrno(data->ld)));
        _ldapfull_unbind(data);
        return 1;
    }

    log_debug(ZONE, "binded to ldap server");
    data->binded = 1;
    return 0;
}