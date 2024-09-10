static int
nodeattr_process_opt(opt_t *pdsh_opts, int opt, char *arg)
{
    switch (opt) {
#if !GENDERS_G_ONLY
    case 'a': 
        excllist = list_split_append (excllist, ",", "pdsh_all_skip");
    case 'A':
        allnodes = true;
        break;
    case 'i':
        altnames = true;
        break;
#endif /* !GENDERS_G_ONLY */
    case 'g':
		attrlist = list_split_append (attrlist, ",", arg);
        break;
    case 'X':
		excllist = list_split_append (excllist, ",", arg);
        break;
    case 'F':
        gfile = Strdup (arg);
        break;
    default:
        err("%p: genders_process_opt: invalid option `%c'\n", opt);
        return -1;
        break;
    }
    return 0;
}