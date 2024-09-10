jsgf_rule_t *
jsgf_import_rule(jsgf_t * jsgf, char *name)
{
    char *c, *path, *newpath;
    size_t namelen, packlen;
    void *val;
    jsgf_t *imp;
    int import_all;

    /* Trim the leading and trailing <> */
    namelen = strlen(name);
    path = ckd_malloc(namelen - 2 + 6); /* room for a trailing .gram */
    strcpy(path, name + 1);
    /* Split off the first part of the name */
    c = strrchr(path, '.');
    if (c == NULL) {
        E_ERROR("Imported rule is not qualified: %s\n", name);
        ckd_free(path);
        return NULL;
    }
    packlen = c - path;
    *c = '\0';

    /* Look for import foo.* */
    import_all = (strlen(name) > 2
                  && 0 == strcmp(name + namelen - 3, ".*>"));

    /* Construct a filename. */
    for (c = path; *c; ++c)
        if (*c == '.')
            *c = '/';
    strcat(path, ".gram");
    newpath = path_list_search(jsgf->searchpath, path);
    if (newpath == NULL) {
        E_ERROR("Failed to find grammar %s\n", path);
        ckd_free(path);
        return NULL;
    }
    ckd_free(path);

    path = newpath;
    E_INFO("Importing %s from %s to %s\n", name, path, jsgf->name);

    /* FIXME: Also, we need to make sure that path is fully qualified
     * here, by adding any prefixes from jsgf->name to it. */
    /* See if we have parsed it already */
    if (hash_table_lookup(jsgf->imports, path, &val) == 0) {
        E_INFO("Already imported %s\n", path);
        imp = val;
        ckd_free(path);
    }
    else {
        /* If not, parse it. */
        imp = jsgf_parse_file(path, jsgf);
        val = hash_table_enter(jsgf->imports, path, imp);
        if (val != (void *) imp) {
            E_WARN("Multiply imported file: %s\n", path);
        }
    }
    if (imp != NULL) {
        hash_iter_t *itor;
        /* Look for public rules matching rulename. */
        for (itor = hash_table_iter(imp->rules); itor;
             itor = hash_table_iter_next(itor)) {
            hash_entry_t *he = itor->ent;
            jsgf_rule_t *rule = hash_entry_val(he);
            int rule_matches;
            char *rule_name = importname2rulename(name);

            if (import_all) {
                /* Match package name (symbol table is shared) */
                rule_matches =
                    !strncmp(rule_name, rule->name, packlen + 1);
            }
            else {
                /* Exact match */
                rule_matches = !strcmp(rule_name, rule->name);
            }
            ckd_free(rule_name);
            if (rule->is_public && rule_matches) {
                void *val;
                char *newname;

                /* Link this rule into the current namespace. */
                c = strrchr(rule->name, '.');
                assert(c != NULL);
                newname = jsgf_fullname(jsgf, c);

                E_INFO("Imported %s\n", newname);
                val = hash_table_enter(jsgf->rules, newname,
                                       jsgf_rule_retain(rule));
                if (val != (void *) rule) {
                    E_WARN("Multiply defined symbol: %s\n", newname);
                }
                if (!import_all) {
                    hash_table_iter_free(itor);
                    return rule;
                }
            }
        }
    }

    return NULL;
}