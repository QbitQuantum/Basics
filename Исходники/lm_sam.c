static int ondata_no_sid(struct lm_sam_s *This, PUNICODE_STRING uname, HASH hash, NTSTATUS *result){
    LSA_HANDLE                      h_policy;
    LSA_OBJECT_ATTRIBUTES           objattr;
    POLICY_ACCOUNT_DOMAIN_INFO      *pdomain_info;
    NTSTATUS                        status;
    char                            dname[64];

    memset(&objattr, 0, sizeof(objattr));
    objattr.Length = sizeof(objattr);

    if((status = LsaOpenPolicy(NULL, &objattr, POLICY_VIEW_LOCAL_INFORMATION, &h_policy)) != STATUS_SUCCESS){
        DOUTST2("LsaOpenPolicy", status);
        *result = status;
        return 0;
    }

    if((status = LsaQueryInformationPolicy(h_policy, PolicyAccountDomainInformation, &pdomain_info)) != STATUS_SUCCESS){
        DOUTST2("LsaQueryInformationPolicy", status);
        LsaClose(h_policy);
        *result = status;
        return 0;
    }

    if(unicode2ansi(pdomain_info->DomainName.Buffer, pdomain_info->DomainName.Length, dname, sizeof(dname)) == 0){
        strcpy(dname, "<unknown>");
    }

    dout(va("Current domain is %s.\n", dname));

    This->lsa_policy_info_buffer = pdomain_info;
    This->domain_sid = pdomain_info->DomainSid;

    // delegate processing to no_sam state
    This->state = &state_no_sam;
    return This->state->data(This, uname, hash, result);
}