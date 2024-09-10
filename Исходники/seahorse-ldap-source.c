static void
dump_ldap_entry (LDAP *ld, LDAPMessage *res)
{
    BerElement *pos;
    gchar **values;
    gchar **v;
    char *t;
    
    t = ldap_get_dn (ld, res);
    g_debug ("dn: %s\n", t);
    ldap_memfree (t);
    
    for (t = ldap_first_attribute (ld, res, &pos); t; 
         t = ldap_next_attribute (ld, res, pos)) {
             
        values = get_ldap_values (ld, res, t);
        for (v = values; *v; v++) 
            g_debug ("%s: %s\n", t, *v);

        g_strfreev (values);
        ldap_memfree (t);
    }
    
    ber_free (pos, 0);
}