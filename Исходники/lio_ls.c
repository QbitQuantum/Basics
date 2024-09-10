int main(int argc, char **argv)
{
    int i, j, ftype, rg_mode, start_option, start_index, prefix_len, nosort, err;
    ex_off_t fcount;
    char *fname;
    ls_entry_t *lse;
    tbx_list_t *table;
//  lio_path_tuple_t tuple;
    os_regex_table_t *rp_single, *ro_single;
    os_object_iter_t *it;
    tbx_list_iter_t lit;
    opque_t *q;
    op_generic_t *gop;
    char *keys[] = { "system.owner", "system.exnode.size", "system.modify_data", "os.create",  "os.link_count" };
    char *vals[5];
    int v_size[5];
    int n_keys = 5;
    int recurse_depth = 0;
    int obj_types = OS_OBJECT_ANY;
    int return_code = 0;

//printf("argc=%d\n", argc);
    if (argc < 2) {
        printf("\n");
        printf("lio_ls LIO_COMMON_OPTIONS [-rd recurse_depth] [-ns] LIO_PATH_OPTIONS\n");
        lio_print_options(stdout);
        lio_print_path_options(stdout);
        printf("\n");
        printf("    -rd recurse_depth  - Max recursion depth on directories. Defaults to %d\n", recurse_depth);
        printf("    -t  object_types   - Types of objects to list bitwise OR of 1=Files, 2=Directories, 4=symlink, 8=hardlink.  Default is %d.\n", obj_types);
        printf("    -ns                - Don't sort the output\n");
        return(1);
    }

    lio_init(&argc, &argv);

    //*** Parse the args
    rp_single = ro_single = NULL;
    nosort = 0;

    rg_mode = lio_parse_path_options(&argc, argv, lio_gc->auto_translate, &tuple, &rp_single, &ro_single);

    i=1;
    do {
        start_option = i;

        if (strcmp(argv[i], "-rd") == 0) { //** Recurse depth
            i++;
            recurse_depth = atoi(argv[i]);
            i++;
        } else if (strcmp(argv[i], "-t") == 0) {  //** Object types
            i++;
            obj_types = atoi(argv[i]);
            i++;
        } else if (strcmp(argv[i], "-ns") == 0) {  //** Strip off the path prefix
            i++;
            nosort = 1;
        }

    } while ((start_option < i) && (i<argc));
    start_index = i;

    if (rg_mode == 0) {
        if (i>=argc) {
            info_printf(lio_ifd, 0, "Missing directory!\n");
            return(2);
        }
    } else {
        start_index--;  //** Ther 1st entry will be the rp created in lio_parse_path_options
    }

    fcount = 0;

    q = new_opque();
    table = tbx_list_create(0, &tbx_list_string_compare, NULL, tbx_list_no_key_free, tbx_list_no_data_free);


    for (j=start_index; j<argc; j++) {
        log_printf(5, "path_index=%d argc=%d rg_mode=%d\n", j, argc, rg_mode);
        if (rg_mode == 0) {
            //** Create the simple path iterator
            tuple = lio_path_resolve(lio_gc->auto_translate, argv[j]);
            lio_path_wildcard_auto_append(&tuple);
            rp_single = os_path_glob2regex(tuple.path);
        } else {
            rg_mode = 0;  //** Use the initial rp
        }

        for (i=0; i<n_keys; i++) v_size[i] = -tuple.lc->max_attr;
        memset(vals, 0, sizeof(vals));
        it = lio_create_object_iter_alist(tuple.lc, tuple.creds, rp_single, ro_single, obj_types, recurse_depth, keys, (void **)vals, v_size, n_keys);
        if (it == NULL) {
            info_printf(lio_ifd, 0, "ERROR: Failed with object_iter creation\n");
            return_code = EIO;
            goto finished;
        }

        while ((ftype = lio_next_object(tuple.lc, it, &fname, &prefix_len)) > 0) {
            tbx_type_malloc_clear(lse, ls_entry_t, 1);
            lse->fname = fname;
            lse->ftype = ftype;
            lse->prefix_len = prefix_len;
            memcpy(lse->v_size, v_size, sizeof(v_size));
            memcpy(lse->vals, vals, sizeof(vals));

            for (i=0; i<n_keys; i++) v_size[i] = -tuple.lc->max_attr;
            memset(vals, 0, sizeof(vals));

            //** Check if we have a link.  If so we need to resolve the link path
            if ((ftype & OS_OBJECT_SYMLINK) > 0) {
                lse->link_size = -64*1024;
                gop = gop_lio_get_attr(tuple.lc, tuple.creds, lse->fname, NULL, "os.link", (void **)&(lse->link), &(lse->link_size));
                gop_set_private(gop, lse);
                opque_add(q, gop);
                if (nosort == 1) opque_waitall(q);
            }

            if (fcount == 0) {
                info_printf(lio_ifd, 0, "  Perms     Ref   Owner        Size           Creation date              Modify date             Filename [-> link]\n");
                info_printf(lio_ifd, 0, "----------  ---  ----------  ----------  ------------------------  ------------------------  ------------------------------\n");
            }
            fcount++;

            if (nosort == 1) {
                ls_format_entry(lio_ifd, lse);
            } else {
                tbx_list_insert(table, lse->fname, lse);
            }
        }

        lio_destroy_object_iter(tuple.lc, it);

        lio_path_release(&tuple);
        if (rp_single != NULL) {
            os_regex_table_destroy(rp_single);
            rp_single = NULL;
        }
        if (ro_single != NULL) {
            os_regex_table_destroy(ro_single);
            ro_single = NULL;
        }
    }

    //** Wait for any readlinks to complete
    err = (opque_task_count(q) > 0) ? opque_waitall(q) : OP_STATE_SUCCESS;
    if (err != OP_STATE_SUCCESS) {
        info_printf(lio_ifd, 0, "ERROR: Failed with readlink operation!\n");
        return_code = EIO;
    }

    //** Now sort and print things if needed
    if (nosort == 0) {
        lit = tbx_list_iter_search(table, NULL, 0);
        while ((tbx_list_next(&lit, (tbx_list_key_t **)&fname, (tbx_list_data_t **)&lse)) == 0) {
            ls_format_entry(lio_ifd, lse);
        }
    }

    tbx_list_destroy(table);

    if (fcount == 0) return_code = 2;

finished:
    opque_free(q, OP_DESTROY);

    lio_shutdown();

    return(return_code);
}