/*
 * This implements a very limited PEM header parser that does not support the
 * full grammar of rfc1421.  In particular, folded headers are not supported,
 * nor is additional whitespace.
 *
 * A robust implementation would make use of a library that turns the headers
 * into a BIO from which one folded line is read at a time, and is then split
 * into a header label and content.  We would then parse the content of the
 * headers we care about.  This is overkill for just this limited use-case, but
 * presumably we also parse rfc822-style headers for S/MIME, so a common
 * abstraction might well be more generally useful.
 */
int PEM_get_EVP_CIPHER_INFO(char *header, EVP_CIPHER_INFO *cipher)
{
    static const char ProcType[] = "Proc-Type:";
    static const char ENCRYPTED[] = "ENCRYPTED";
    static const char DEKInfo[] = "DEK-Info:";
    const EVP_CIPHER *enc = NULL;
    int ivlen;
    char *dekinfostart, c;

    cipher->cipher = NULL;
    if ((header == NULL) || (*header == '\0') || (*header == '\n'))
        return 1;

    if (strncmp(header, ProcType, sizeof(ProcType)-1) != 0) {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_NOT_PROC_TYPE);
        return 0;
    }
    header += sizeof(ProcType)-1;
    header += strspn(header, " \t");

    if (*header++ != '4' || *header++ != ',')
        return 0;
    header += strspn(header, " \t");

    /* We expect "ENCRYPTED" followed by optional white-space + line break */
    if (strncmp(header, ENCRYPTED, sizeof(ENCRYPTED)-1) != 0 ||
        strspn(header+sizeof(ENCRYPTED)-1, " \t\r\n") == 0) {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_NOT_ENCRYPTED);
        return 0;
    }
    header += sizeof(ENCRYPTED)-1;
    header += strspn(header, " \t\r");
    if (*header++ != '\n') {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_SHORT_HEADER);
        return 0;
    }

    /*-
     * https://tools.ietf.org/html/rfc1421#section-4.6.1.3
     * We expect "DEK-Info: algo[,hex-parameters]"
     */
    if (strncmp(header, DEKInfo, sizeof(DEKInfo)-1) != 0) {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_NOT_DEK_INFO);
        return 0;
    }
    header += sizeof(DEKInfo)-1;
    header += strspn(header, " \t");

    /*
     * DEK-INFO is a comma-separated combination of algorithm name and optional
     * parameters.
     */
    dekinfostart = header;
    header += strcspn(header, " \t,");
    c = *header;
    *header = '\0';
    cipher->cipher = enc = EVP_get_cipherbyname(dekinfostart);
    *header = c;
    header += strspn(header, " \t");

    if (enc == NULL) {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_UNSUPPORTED_ENCRYPTION);
        return 0;
    }
    ivlen = EVP_CIPHER_iv_length(enc);
    if (ivlen > 0 && *header++ != ',') {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_MISSING_DEK_IV);
        return 0;
    } else if (ivlen == 0 && *header == ',') {
        PEMerr(PEM_F_PEM_GET_EVP_CIPHER_INFO, PEM_R_UNEXPECTED_DEK_IV);
        return 0;
    }

    if (!load_iv(&header, cipher->iv, EVP_CIPHER_iv_length(enc)))
        return 0;

    return 1;
}