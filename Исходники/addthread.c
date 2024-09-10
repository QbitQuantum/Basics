static int at_add(AddThread *at)
{
    LDAPMod *attrs[10];
    LDAPMod attr_cn, attr_sn, attr_givenname,
        attr_objectclass, attr_uid, attr_mail, attr_telephonenumber,
        attr_audio, attr_password;
    struct berval audio_berval;
    struct berval *audio_values[2];
    char dn[100], uid[10], telno[20], *sn, *givenname, cn[50], mail[50];
    char *cn_values[2], *sn_values[2], *givenname_values[2];
    char *uid_values[2], *mail_values[2], *telno_values[2];
#if 1
    char *objectclass_values[] = { "top", "person", "organizationalPerson",
                                   "inetOrgPerson", NULL };
#else
    char *objectclass_values[] = { "inetOrgPerson", NULL };
#endif
    int ret;

    /* make up the strings */
    sprintf(uid, "%lu", getID());
    at_random_tel_number(telno);
    sn = nt_getrand(family_names);
    givenname = nt_getrand(given_names);
    sprintf(cn, "%s %s %s", givenname, sn, uid);
    sprintf(mail, "*****@*****.**", givenname, uid);
    sprintf(dn, "cn=%s,%s", cn, suffix);

    cn_values[0] = cn;
    cn_values[1] = NULL;
    sn_values[0] = sn;
    sn_values[1] = NULL;
    givenname_values[0] = givenname;
    givenname_values[1] = NULL;
    uid_values[0] = uid;
    uid_values[1] = NULL;
    mail_values[0] = mail;
    mail_values[1] = NULL;
    telno_values[0] = telno;
    telno_values[1] = NULL;
    
    attrs[0] = &attr_objectclass;
    attrs[1] = &attr_cn;
    attrs[2] = &attr_sn;
    attrs[3] = &attr_givenname;
    attrs[4] = &attr_uid;
    attrs[5] = &attr_password;
    attrs[6] = &attr_mail;
    attrs[7] = &attr_telephonenumber;
    if (blobsize > 0) {
        audio_values[0] = &audio_berval;
        audio_values[1] = 0;
        audio_berval.bv_len = (blobsize > 32000) ?
            ((long)rand() * 1039) % blobsize :
            (rand() % blobsize);
        audio_berval.bv_val = at->blob;
        attr_audio.mod_op = LDAP_MOD_BVALUES;
        attr_audio.mod_type = "audio";
        attr_audio.mod_values = (char **)&audio_values;
        attrs[8] = &attr_audio;
        attrs[9] = 0;
    }
    else
        attrs[8] = 0;

    attr_cn.mod_op = LDAP_MOD_ADD;
    attr_cn.mod_type = "cn";
    attr_cn.mod_values = cn_values;
    attr_sn.mod_op = LDAP_MOD_ADD;
    attr_sn.mod_type = "sn";
    attr_sn.mod_values = sn_values;
    attr_givenname.mod_op = LDAP_MOD_ADD;
    attr_givenname.mod_type = "givenname";
    attr_givenname.mod_values = givenname_values;
    attr_objectclass.mod_op = LDAP_MOD_ADD;
    attr_objectclass.mod_type = "objectClass";
    attr_objectclass.mod_values = objectclass_values;
    attr_uid.mod_op = LDAP_MOD_ADD;
    attr_uid.mod_type = "uid";
    attr_uid.mod_values = uid_values;
    attr_password.mod_op = LDAP_MOD_ADD;
    attr_password.mod_type = "userpassword";
    attr_password.mod_values = uid_values;
    attr_mail.mod_op = LDAP_MOD_ADD;
    attr_mail.mod_type = "mail";
    attr_mail.mod_values = mail_values;
    attr_telephonenumber.mod_op = LDAP_MOD_ADD;
    attr_telephonenumber.mod_type = "telephonenumber";
    attr_telephonenumber.mod_values = telno_values;

#if 0
    for (i = 0; attrs[i]; i++) {
        fprintf(stderr, "attr '%s': ", attrs[i]->mod_type);
        if (strcasecmp(attrs[i]->mod_type, "audio") == 0)
            fprintf(stderr, "binary data len=%lu\n", ((struct berval **)(attrs[i]->mod_values))[0]->bv_len);
        else 
            fprintf(stderr, "'%s'\n", attrs[i]->mod_values[0]);
    }
#endif
    ret = ldap_add_ext_s(at->ld, dn, attrs, NULL, NULL);
	if (ret != LDAP_SUCCESS) {
        fprintf(stderr, "T%d: failed to add, error = %d\n", at->id, ret);
    }
    return ret;
}