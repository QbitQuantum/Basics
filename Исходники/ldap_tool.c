/**
int  check_ldap_passwd(LDAP* ld, JBXL_LDAP_Dn user)

LDAP を使用してユーザ認証を行う．

@param  ld    LDAPサーバへのセッションハンドラ
@param  user  ユーザ情報が格納された JBXL_LDAP_Dn

@retval  0    正常終了．
@retval  1    ユーザ認証失敗(ユーザは存在するが，パスワードが一致しない)
@retval  2    ユーザ認証失敗(ユーザが存在しない)
@retval -1    LDAPサーバへのセッションハンドラが NULL
@retval -2    BASE名が不明
*/
int  check_ldap_passwd(LDAP* ld, JBXL_LDAP_Dn user)
{
    int   ret;
    char* dn_attr[] = {_tochar("distinguishedName"), NULL};

    if (ld==NULL) return -1;

    if (user.base.buf==NULL) user.base = dup_Buffer(JBXLdapDnBind->base);
    if (user.base.buf==NULL) return -2;

    //
    if (user.dnbind.buf==NULL) return 2;
    else {
        Buffer tmp = erase_sBuffer(user.dnbind, "*");
        copy_Buffer(&tmp, &user.dnbind);
        free_Buffer(&tmp);
    }
    if (user.dnbind.buf[0]=='\0') return 2;

    Buffer cond = make_Buffer_bystr("uid=");
    cat_Buffer(&user.dnbind, &cond);

    LDAPMessage* res = NULL;
    ret = ldap_search_s(ld, (char*)user.base.buf, LDAP_SCOPE_SUBTREE, (char*)cond.buf, dn_attr, 0, &res);
    if (res==NULL) return 2;

    LDAPMessage* ent = ldap_first_entry(ld, res);
    if (ent==NULL) {
        ldap_msgfree(res);
        return 2;
    }

    BerElement* ber = NULL;
    char* attr = ldap_first_attribute(ld, ent, &ber);
    if (attr==NULL) {
        ldap_msgfree(res);
        return 2;
    }

    char** dn = ldap_get_values(ld, ent, attr);
    ldap_memfree(attr);
    ldap_msgfree(res);
    if (dn==NULL || *dn==NULL) return 2;


    // ユーザチェック   Password "" is OK!! Ohhh GeroGero!!
    if (user.passwd.buf==NULL || user.passwd.buf[0]=='\0') return 1;


    // パスワード確認
    ret = ldap_simple_bind_s(ld, *dn, (char*)user.passwd.buf);
    if (ret!=LDAP_SUCCESS) return 1;

    // 念のため，セッションを確認
    //ret = ldap_compare_s(ld, *dn, "name", (char*)user.dnbind.buf);
    //if (ret!=LDAP_COMPARE_TRUE) return 1;

    return 0;
}