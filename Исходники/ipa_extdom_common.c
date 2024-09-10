int pack_response(struct extdom_res *res, struct berval **ret_val)
{
    BerElement *ber = NULL;
    int ret;

/* We send to follwing response:
 * ExtdomResponseValue ::= SEQUENCE {
 *    responseType ENUMERATED {
 *        sid (1),
 *        name (2),
 *        posix_user (3),
 *        posix_group (4)
 *    },
 *    data OutputData
 * }
 *
 * OutputData ::= CHOICE {
 *    sid OCTET STRING,
 *    name NameDomainData,
 *    user PosixUser,
 *    group PosixGroup
 * }
 *
 * NameDomainData ::= SEQUENCE {
 *    domain_name OCTET STRING,
 *    object_name OCTET STRING
 * }
 *
 * PosixUser ::= SEQUENCE {
 *    domain_name OCTET STRING,
 *    user_name OCTET STRING,
 *    uid INTEGER
 *    gid INTEGER
 * }
 *
 * PosixGroup ::= SEQUENCE {
 *    domain_name OCTET STRING,
 *    group_name OCTET STRING,
 *    gid INTEGER
 * }
 */

    ber = ber_alloc_t( LBER_USE_DER );
    if (ber == NULL) {
        return LDAP_OPERATIONS_ERROR;
    }

    switch (res->response_type) {
        case RESP_SID:
            ret = ber_printf(ber,"{es}", res->response_type, res->data.sid);
            break;
        case RESP_NAME:
            ret = ber_printf(ber,"{e{ss}}", res->response_type,
                                            res->data.name.domain_name,
                                            res->data.name.object_name);
            break;
        case RESP_USER:
            ret = ber_printf(ber,"{e{ssii}}", res->response_type,
                                              res->data.user.domain_name,
                                              res->data.user.user_name,
                                              res->data.user.uid,
                                              res->data.user.gid);
            break;
        case RESP_GROUP:
            ret = ber_printf(ber,"{e{ssi}}", res->response_type,
                                             res->data.group.domain_name,
                                             res->data.group.group_name,
                                             res->data.group.gid);
            break;
        default:
            ber_free(ber, 1);
            return LDAP_OPERATIONS_ERROR;
    }

    if (ret == -1) {
        ber_free(ber, 1);
        return LDAP_OPERATIONS_ERROR;
    }

    ret = ber_flatten(ber, ret_val);
    if (ret == -1) {
        ber_free(ber, 1);
        return LDAP_OPERATIONS_ERROR;
    }

    ber_free(ber, 1);

    return LDAP_SUCCESS;
}