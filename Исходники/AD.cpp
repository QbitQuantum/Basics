void AD::Enumerate(ADSearchFilter searchFilter)
{
    LDAPMessage *search = NULL;
    LDAPMessage *entry = NULL;
    PWCHAR *value;
    PWCHAR attribute;
    berval *ber = NULL;
    DWORD i;
    DWORD j;
    // 20 strings should be enough?
    LPWSTR filters[20];
    BerElement *berElement = NULL;

    // Fill our filters array (NULL-terminated) with search-specific filters.
    switch(searchFilter)
    {
    case AD_SEARCH_USER:
        SetFilter(L"(&(objectClass=user)(objectCategory=person))");
        filters[0] = L"samAccountName";
        filters[1] = L"cn";
        filters[2] = L"homeDirectory";
        filters[3] = L"memberOf";
        filters[4] = NULL;
        break;
    case AD_SEARCH_GROUP:
        SetFilter(L"(&(objectCategory=group))");
        filters[0] = L"samAccountName";
        filters[1] = L"cn";
        filters[2] = L"member";
        filters[3] = NULL;
        break;
    case AD_SEARCH_MACHINE:
        SetFilter(L"(&(objectCategory=computer))");
        filters[0] = L"samAccountName";
        filters[1] = L"cn";
        filters[2] = NULL;
        break;
    default:
        break;
    }

    if(ldap_search_s(ldap, (const PWCHAR)dn.c_str(), LDAP_SCOPE_SUBTREE, (PWCHAR)filter.c_str(), NULL, 0, &search) != LDAP_SUCCESS)
    {
        Util::Error(LdapGetLastError(), L"ldap_search");
        Util::Notice(L"ret = %x\n", LdapGetLastError());
    }

    switch(searchFilter)
    {
    case AD_SEARCH_USER:
        AddUsers(search);
        break;
    case AD_SEARCH_GROUP:
        AddGroups(search);
        break;
    case AD_SEARCH_MACHINE:
        AddServers(search);
        break;
    default:
        break;
    }
    ldap_msgfree(search);
    ber_free(berElement, 0);
}