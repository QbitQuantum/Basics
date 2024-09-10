ngram_model_t *
ngram_model_set_read(cmd_ln_t * config,
                     const char *lmctlfile, logmath_t * lmath)
{
    FILE *ctlfp;
    glist_t lms = NULL;
    glist_t lmnames = NULL;
    __BIGSTACKVARIABLE__ char str[1024];
    ngram_model_t *set = NULL;
    hash_table_t *classes;
    char *basedir, *c;

    /* Read all the class definition files to accumulate a mapping of
     * classnames to definitions. */
    classes = hash_table_new(0, FALSE);
    if ((ctlfp = fopen(lmctlfile, "r")) == NULL) {
        E_ERROR_SYSTEM("Failed to open %s", lmctlfile);
        return NULL;
    }

    /* Try to find the base directory to append to relative paths in
     * the lmctl file. */
    if ((c = strrchr(lmctlfile, '/')) || (c = strrchr(lmctlfile, '\\'))) {
        /* Include the trailing slash. */
        basedir = ckd_calloc(c - lmctlfile + 2, 1);
        memcpy(basedir, lmctlfile, c - lmctlfile + 1);
    }
    else {
        basedir = NULL;
    }
    E_INFO("Reading LM control file '%s'\n", lmctlfile);
    if (basedir)
        E_INFO("Will prepend '%s' to unqualified paths\n", basedir);

    if (fscanf(ctlfp, "%1023s", str) == 1) {
        if (strcmp(str, "{") == 0) {
            /* Load LMclass files */
            while ((fscanf(ctlfp, "%1023s", str) == 1)
                   && (strcmp(str, "}") != 0)) {
                char *deffile;
                if (basedir && !path_is_absolute(str))
                    deffile = string_join(basedir, str, NULL);
                else
                    deffile = ckd_salloc(str);
                E_INFO("Reading classdef from '%s'\n", deffile);
                if (read_classdef_file(classes, deffile) < 0) {
                    ckd_free(deffile);
                    goto error_out;
                }
                ckd_free(deffile);
            }

            if (strcmp(str, "}") != 0) {
                E_ERROR("Unexpected EOF in %s\n", lmctlfile);
                goto error_out;
            }

            /* This might be the first LM name. */
            if (fscanf(ctlfp, "%1023s", str) != 1)
                str[0] = '\0';
        }
    }
    else
        str[0] = '\0';

    /* Read in one LM at a time and add classes to them as necessary. */
    while (str[0] != '\0') {
        char *lmfile;
        ngram_model_t *lm;

        if (basedir && str[0] != '/' && str[0] != '\\')
            lmfile = string_join(basedir, str, NULL);
        else
            lmfile = ckd_salloc(str);
        E_INFO("Reading lm from '%s'\n", lmfile);
        lm = ngram_model_read(config, lmfile, NGRAM_AUTO, lmath);
        if (lm == NULL) {
            ckd_free(lmfile);
            goto error_out;
        }
        if (fscanf(ctlfp, "%1023s", str) != 1) {
            E_ERROR("LMname missing after LMFileName '%s'\n", lmfile);
            ckd_free(lmfile);
            goto error_out;
        }
        ckd_free(lmfile);
        lms = glist_add_ptr(lms, lm);
        lmnames = glist_add_ptr(lmnames, ckd_salloc(str));

        if (fscanf(ctlfp, "%1023s", str) == 1) {
            if (strcmp(str, "{") == 0) {
                /* LM uses classes; read their names */
                while ((fscanf(ctlfp, "%1023s", str) == 1) &&
                       (strcmp(str, "}") != 0)) {
                    void *val;
                    classdef_t *classdef;

                    if (hash_table_lookup(classes, str, &val) == -1) {
                        E_ERROR("Unknown class %s in control file\n", str);
                        goto error_out;
                    }
                    classdef = val;
                    if (ngram_model_add_class(lm, str, 1.0,
                                              classdef->words,
                                              classdef->weights,
                                              classdef->n_words) < 0) {
                        goto error_out;
                    }
                    E_INFO("Added class %s containing %d words\n",
                           str, classdef->n_words);
                }
                if (strcmp(str, "}") != 0) {
                    E_ERROR("Unexpected EOF in %s\n", lmctlfile);
                    goto error_out;
                }
                if (fscanf(ctlfp, "%1023s", str) != 1)
                    str[0] = '\0';
            }
        }
        else
            str[0] = '\0';
    }
    fclose(ctlfp);

    /* Now construct arrays out of lms and lmnames, and build an
     * ngram_model_set. */
    lms = glist_reverse(lms);
    lmnames = glist_reverse(lmnames);
    {
        int32 n_models;
        ngram_model_t **lm_array;
        char **name_array;
        gnode_t *lm_node, *name_node;
        int32 i;

        n_models = glist_count(lms);
        lm_array = ckd_calloc(n_models, sizeof(*lm_array));
        name_array = ckd_calloc(n_models, sizeof(*name_array));
        lm_node = lms;
        name_node = lmnames;
        for (i = 0; i < n_models; ++i) {
            lm_array[i] = gnode_ptr(lm_node);
            name_array[i] = gnode_ptr(name_node);
            lm_node = gnode_next(lm_node);
            name_node = gnode_next(name_node);
        }
        set = ngram_model_set_init(config, lm_array, name_array,
                                   NULL, n_models);

        for (i = 0; i < n_models; ++i) {
            ngram_model_free(lm_array[i]);
        }
        ckd_free(lm_array);
        ckd_free(name_array);
    }
  error_out:
    {
        gnode_t *gn;
        glist_t hlist;

        if (set == NULL) {
            for (gn = lms; gn; gn = gnode_next(gn)) {
                ngram_model_free(gnode_ptr(gn));
            }
        }
        glist_free(lms);
        for (gn = lmnames; gn; gn = gnode_next(gn)) {
            ckd_free(gnode_ptr(gn));
        }
        glist_free(lmnames);
        hlist = hash_table_tolist(classes, NULL);
        for (gn = hlist; gn; gn = gnode_next(gn)) {
            hash_entry_t *he = gnode_ptr(gn);
            ckd_free((char *) he->key);
            classdef_free(he->val);
        }
        glist_free(hlist);
        hash_table_free(classes);
        ckd_free(basedir);
    }
    return set;
}