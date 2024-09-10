/**
 * From gnutls and spice red_peer.c
 * TODO: switch to gnutls and get rid of this
 *
 * This function will check if the given certificate's subject matches
 * the given hostname.  This is a basic implementation of the matching
 * described in RFC2818 (HTTPS), which takes into account wildcards,
 * and the DNSName/IPAddress subject alternative name PKIX extension.
 *
 * Returns: 1 for a successful match, and 0 on failure.
 **/
static int verify_hostname(X509* cert, const char *hostname)
{
    GENERAL_NAMES* subject_alt_names;
    int found_dns_name = 0;
    struct in_addr addr;
    int addr_len = 0;
    int cn_match = 0;

    if (!cert) {
        SPICE_DEBUG("warning: no cert!");
        return 0;
    }

    // only IpV4 supported
    if (inet_aton(hostname, &addr)) {
        addr_len = sizeof(struct in_addr);
    }

    /* try matching against:
     *  1) a DNS name as an alternative name (subjectAltName) extension
     *     in the certificate
     *  2) the common name (CN) in the certificate
     *
     *  either of these may be of the form: *.domain.tld
     *
     *  only try (2) if there is no subjectAltName extension of
     *  type dNSName
     */

    /* Check through all included subjectAltName extensions, comparing
     * against all those of type dNSName.
     */
    subject_alt_names = (GENERAL_NAMES*)X509_get_ext_d2i(cert, NID_subject_alt_name, NULL, NULL);

    if (subject_alt_names) {
        int num_alts = sk_GENERAL_NAME_num(subject_alt_names);
        int i;
        for (i = 0; i < num_alts; i++) {
            const GENERAL_NAME* name = sk_GENERAL_NAME_value(subject_alt_names, i);
            if (name->type == GEN_DNS) {
                found_dns_name = 1;
                if (_gnutls_hostname_compare((char *)ASN1_STRING_data(name->d.dNSName),
                                             ASN1_STRING_length(name->d.dNSName),
                                             hostname)) {
                    SPICE_DEBUG("alt name match=%s", ASN1_STRING_data(name->d.dNSName));
                    GENERAL_NAMES_free(subject_alt_names);
                    return 1;
                }
            } else if (name->type == GEN_IPADD) {
                int alt_ip_len = ASN1_STRING_length(name->d.iPAddress);
                found_dns_name = 1;
                if ((addr_len == alt_ip_len)&&
                    !memcmp(ASN1_STRING_data(name->d.iPAddress), &addr, addr_len)) {
                    SPICE_DEBUG("alt name IP match=%s",
                                inet_ntoa(*((struct in_addr*)ASN1_STRING_data(name->d.dNSName))));
                    GENERAL_NAMES_free(subject_alt_names);
                    return 1;
                }
            }
        }
        GENERAL_NAMES_free(subject_alt_names);
    }

    if (found_dns_name) {
        SPICE_DEBUG("warning: SubjectAltName mismatch");
        return 0;
    }

    /* extracting commonNames */
    X509_NAME* subject = X509_get_subject_name(cert);
    if (subject) {
        int pos = -1;
        X509_NAME_ENTRY* cn_entry;
        ASN1_STRING* cn_asn1;

        while ((pos = X509_NAME_get_index_by_NID(subject, NID_commonName, pos)) != -1) {
            cn_entry = X509_NAME_get_entry(subject, pos);
            if (!cn_entry) {
                continue;
            }
            cn_asn1 = X509_NAME_ENTRY_get_data(cn_entry);
            if (!cn_asn1) {
                continue;
            }

            if (_gnutls_hostname_compare((char*)ASN1_STRING_data(cn_asn1),
                                         ASN1_STRING_length(cn_asn1),
                                         hostname)) {
                SPICE_DEBUG("common name match=%s", (char*)ASN1_STRING_data(cn_asn1));
                cn_match = 1;
                break;
            }
        }
    }

    if (!cn_match)
        SPICE_DEBUG("warning: common name mismatch");

    return cn_match;
}