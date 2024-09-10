/* returns:
 *   0 on success
 *   1 if compact was not needed
 *   negative on error
 */
EXPORTED int backup_compact(const char *name,
                            enum backup_open_nonblock nonblock,
                            int force, int verbose, FILE *out)
{
    struct backup *original = NULL;
    struct backup *compact = NULL;
    struct backup_chunk_list *all_chunks = NULL;
    struct backup_chunk_list *keep_chunks = NULL;
    struct backup_chunk *chunk = NULL;
    struct sync_msgid_list *keep_message_guids = NULL;
    struct gzuncat *gzuc = NULL;
    struct protstream *in = NULL;
    time_t since, chunk_start_time, ts;
    int r;

    compact_readconfig();

    r = compact_open(name, &original, &compact, nonblock);
    if (r) return r;

    /* calculate current time after obtaining locks, in case of a wait */
    const time_t now = time(NULL);

    const int retention_days = config_getint(IMAPOPT_BACKUP_RETENTION_DAYS);
    if (retention_days > 0) {
        since = now - (retention_days * 24 * 60 * 60);
    }
    else {
        /* zero or negative retention days means "keep forever" */
        since = -1;
    }

    all_chunks = backup_get_chunks(original);
    if (!all_chunks) goto error;

    keep_chunks = backup_get_live_chunks(original, since);
    if (!keep_chunks) goto error;

    if (!force && !compact_required(all_chunks, keep_chunks)) {
        /* nothing to do */
        backup_chunk_list_free(&all_chunks);
        backup_chunk_list_free(&keep_chunks);
        backup_unlink(&compact);
        backup_close(&original);
        return 1;
    }

    if (verbose) {
        fprintf(out, "keeping " SIZE_T_FMT " chunks:\n", keep_chunks->count);

        for (chunk = keep_chunks->head; chunk; chunk = chunk->next) {
            fprintf(out, " %d", chunk->id);
        }

        fprintf(out, "\n");
    }

    gzuc = gzuc_new(original->fd);
    if (!gzuc) goto error;

    chunk_start_time = -1;
    ts = 0;
    struct buf cmd = BUF_INITIALIZER;
    for (chunk = keep_chunks->head; chunk; chunk = chunk->next) {
        keep_message_guids = sync_msgid_list_create(0);
        r = backup_message_foreach(original, chunk->id, &since,
                                   _keep_message_guids_cb, keep_message_guids);
        if (r) goto error;

        gzuc_member_start_from(gzuc, chunk->offset);

        in = prot_readcb(_prot_fill_cb, gzuc);

        while (1) {
            struct dlist *dl = NULL;

            int c = parse_backup_line(in, &ts, &cmd, &dl);

            if (c == EOF) {
                const char *error = prot_error(in);
                if (error && 0 != strcmp(error, PROT_EOF_STRING)) {
                    syslog(LOG_ERR,
                           "IOERROR: %s: error reading chunk at offset %jd, byte %i: %s\n",
                           name, chunk->offset, prot_bytes_in(in), error);

                    if (out)
                        fprintf(out, "error reading chunk at offset %jd, byte %i: %s\n",
                                chunk->offset, prot_bytes_in(in), error);

                    r = IMAP_IOERROR;
                    goto error;
                }

                break;
            }

            if (chunk_start_time == -1) {
                r = backup_append_start(compact, &ts, BACKUP_APPEND_NOFLUSH);
                if (r) goto error;
                chunk_start_time = ts;
            }

            // XXX if this line is worth keeping
            if (want_append(original, chunk->id, dl, keep_message_guids)) {
                // FIXME if message is removed due to unneeded chunk,
                // subsequent mailbox lines for it will fail here
                // so we need to be able to tell which lines apply to messages we don't want anymore
                r = backup_append(compact, dl, &ts, BACKUP_APPEND_NOFLUSH);
                if (r) goto error;
            }

            dlist_unlink_files(dl);
            dlist_free(&dl);

            // if this line put us over compact_maxsize
            if (want_split(chunk, &compact->append_state->wrote)) {
                r = backup_append_end(compact, &ts);
                chunk_start_time = -1;

                if (verbose) {
                    fprintf(out, "splitting chunk %d\n", chunk->id);
                }
            }
        }

        // if we're due to start a new chunk
        if (compact->append_state && compact->append_state->mode) {
            if (!want_combine(compact->append_state->wrote, chunk->next)) {
                r = backup_append_end(compact, &ts);
                chunk_start_time = -1;
            }
            else if (verbose) {
                fprintf(out, "combining chunks %d and %d\n",
                             chunk->id, chunk->next->id);
            }
        }

        prot_free(in);
        in = NULL;
        gzuc_member_end(gzuc, NULL);

        sync_msgid_list_free(&keep_message_guids);
    }
    buf_free(&cmd);

    if (compact->append_state && compact->append_state->mode)
        backup_append_end(compact, &ts);

    gzuc_free(&gzuc);

    backup_chunk_list_free(&keep_chunks);

    /* if we get here okay, then the compact succeeded */
    r = compact_closerename(&original, &compact, now);
    if (r) goto error;

    return 0;

error:
    if (in) prot_free(in);
    if (gzuc) gzuc_free(&gzuc);
    if (keep_message_guids) sync_msgid_list_free(&keep_message_guids);
    if (all_chunks) backup_chunk_list_free(&all_chunks);
    if (keep_chunks) backup_chunk_list_free(&keep_chunks);
    if (compact) backup_unlink(&compact);
    if (original) backup_close(&original);

    return r ? r : -1;
}