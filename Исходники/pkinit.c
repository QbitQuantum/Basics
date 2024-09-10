static int
match_ms_upn_san(krb5_context context,
		 krb5_kdc_configuration *config,
		 hx509_context hx509ctx,
		 hx509_cert client_cert,
		 krb5_const_principal match)
{
    hx509_octet_string_list list;
    krb5_principal principal = NULL;
    int ret, found = 0;
    MS_UPN_SAN upn;
    size_t size;

    memset(&list, 0 , sizeof(list));

    ret = hx509_cert_find_subjectAltName_otherName(hx509ctx,
						   client_cert,
						   oid_id_pkinit_ms_san(),
						   &list);
    if (ret)
	goto out;

    if (list.len != 1) {
	kdc_log(context, config, 0,
		"More then one PK-INIT MS UPN SAN");
	goto out;
    }

    ret = decode_MS_UPN_SAN(list.val[0].data, list.val[0].length, &upn, &size);
    if (ret) {
	kdc_log(context, config, 0, "Decode of MS-UPN-SAN failed");
	goto out;
    }

    kdc_log(context, config, 0, "found MS UPN SAN: %s", upn);

    ret = krb5_parse_name(context, upn, &principal);
    free_MS_UPN_SAN(&upn);
    if (ret) {
	kdc_log(context, config, 0, "Failed to parse principal in MS UPN SAN");
	goto out;
    }

    /*
     * This is very wrong, but will do for now, should really and a
     * plugin to the windc layer to very this ACL.
    */
    strupr(principal->realm);

    if (krb5_principal_compare(context, principal, match) == TRUE)
	found = 1;

out:
    if (principal)
	krb5_free_principal(context, principal);
    hx509_free_octet_string_list(&list);
    if (ret)
	return ret;

    if (!found)
	return KRB5_KDC_ERR_CLIENT_NAME_MISMATCH;

    return 0;
}