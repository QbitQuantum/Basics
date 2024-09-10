static int st_delete(SearchThread *st)
{
    char *dn = NULL;
    int rval;
    int e;

    /* Decide what entry to modify, for this we need a table */
    if (NULL == sdattable || sdt_getlen(sdattable) == 0) {
        fprintf(stderr, "-d option requires a DN file.  Use -B file.\n");
        return 0;
    }

    /* Get the target dn */
    do {
        e = sdt_getrand(sdattable);
    } while (e < 0);
    dn = sdt_dn_get(sdattable, e);

    rval = ldap_delete_ext_s(st->ld, dn, NULL, NULL);
    if (rval != LDAP_SUCCESS) {
        if (rval == LDAP_NO_SUCH_OBJECT) {
			rval = LDAP_SUCCESS;
        } else {
            fprintf(stderr, "T%d: Failed to delete error=0x%x\n", st->id, rval);
            fprintf(stderr, "dn: %s\n", dn);
        }
    }
    return rval;
}