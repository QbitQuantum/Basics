void
add_uid(uidtbl_t *tbl, char *name)
{
    uid_t *uid;

    if (tbl->n_size == tbl->n_nent) {	/* reallocation */
        if ((tbl->n_size *= 2) == 0)
            tbl->n_size = 4;	/* first time */
        tbl->n_list = Realloc(tbl->n_list, tbl->n_size*sizeof (uid_t));
    }

    uid = &tbl->n_list[tbl->n_nent++];

    if (isdigit(name[0])) {
        *uid = Atoi(name);
    } else {
        *uid = pwd_getid(name);
    }
}