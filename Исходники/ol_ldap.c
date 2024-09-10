/*
 **| method: string dn2ufn ( string dn );
 **|  Convert the given DN to an user friendly form thereof. This will
 **|  strip the type names from the passed dn. See RFC 1781 for more
 **|  details. 
 **
 **| arg: string dn
 **|  an UTF-8 string with the dn to convert.
 **
 **| returns: the user friendly form of the DN.
 */
static void
f_ldap_dn2ufn(INT32 args)
{
    struct pike_string   *dn = NULL;
    char                 *ufn;
    
    if (args != 1)
        Pike_error("OpenLDAP.Client->dn2ufn(): requires exactly one 8-bit string argument\n");

    get_all_args("OpenLDAP.Client->dn2ufn()", args, "%S", &dn);
    
    pop_n_elems(args);
    
    if (!dn) {
        push_int(0);
        return;
    }

    ufn = ldap_dn2ufn(dn->str);
    if (!ufn) {
        push_int(0);
    } else {
        push_string(make_shared_string(ufn));
        ldap_memfree(ufn);
    }
}