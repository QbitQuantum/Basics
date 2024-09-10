static krb5_error_code
krb5_rc_dfl_expunge_locked(krb5_context context, krb5_rcache id)
{
    struct dfl_data *t = (struct dfl_data *)id->data;
#ifdef NOIOSTUFF
    int i;
    struct authlist **q;
    struct authlist **qt;
    struct authlist *r;
    struct authlist *rt;
    krb5_int32 now;

    if (krb5_timestamp(context, &now))
	now = 0;

    for (q = &t->a; *q; q = qt) {
	qt = &(*q)->na;
	if (alive(now, &(*q)->rep, t->lifespan) == CMP_EXPIRED) {
	    FREE((*q)->rep.client);
	    FREE((*q)->rep.server);
	    FREE(*q);
	    *q = *qt; /* why doesn't this feel right? */
	}
    }
    for (i = 0; i < t->hsize; i++)
	t->h[i] = (struct authlist *) 0;
    for (r = t->a; r; r = r->na) {
	i = hash(&r->rep, t->hsize);
	rt = t->h[i];
	t->h[i] = r;
	r->nh = rt;
    }
    return 0;
#else
    struct authlist *q;
    char *name;
    krb5_error_code retval = 0;
    krb5_rcache tmp;
    krb5_deltat lifespan = t->lifespan;  /* save original lifespan */

    if (! t->recovering) {
	name = t->name;
	t->name = 0;		/* Clear name so it isn't freed */
	(void) krb5_rc_dfl_close_no_free(context, id);
	retval = krb5_rc_dfl_resolve(context, id, name);
	free(name);
	if (retval)
	    return retval;
	retval = krb5_rc_dfl_recover_locked(context, id);
	if (retval)
	    return retval;
	t = (struct dfl_data *)id->data; /* point to recovered cache */
    }

    tmp = (krb5_rcache) malloc(sizeof(*tmp));
    if (!tmp)
	return ENOMEM;
    retval = krb5_rc_resolve_type(context, &tmp, "dfl");
    if (retval) {
        free(tmp);
        return retval;
    }
    retval = krb5_rc_resolve(context, tmp, 0);
    if (retval)
        goto cleanup;
    retval = krb5_rc_initialize(context, tmp, lifespan);
    if (retval)
        goto cleanup;
    for (q = t->a; q; q = q->na) {
	if (krb5_rc_io_store(context, (struct dfl_data *)tmp->data, &q->rep)) {
            retval = KRB5_RC_IO;
            goto cleanup;
        }
    }
    /* NOTE: We set retval in case we have an error */
    retval = KRB5_RC_IO;
    if (krb5_rc_io_sync(context, &((struct dfl_data *)tmp->data)->d))
        goto cleanup;
    if (krb5_rc_io_sync(context, &t->d))
        goto cleanup;
    if (krb5_rc_io_move(context, &t->d, &((struct dfl_data *)tmp->data)->d))
        goto cleanup;
    retval = 0;
 cleanup:
    (void) krb5_rc_dfl_close(context, tmp);
    return retval;
#endif
}