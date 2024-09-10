cct_status _cct_source_subrip_read(cct_source_ctx *ctx, cct_sub_entry **entry, unsigned int *eos)
{
    (*entry) = NULL;
    *eos = 0;
    cct_source_subrip_ctx *sctx = (cct_source_subrip_ctx *) ctx->ctx_data;
    char buffer[SRT_MAX_LINE_LENGTH];
    if (!fgets(buffer, SRT_MAX_LINE_LENGTH, sctx->file)) {
        if (feof(sctx->file)) {
            *eos = 1;
            return CCT_OK;
        } else if (ferror(sctx->file)) {
            perror("_cct_subrip_source_read: can't read entry counter");
            return CCT_FATAL;
        }
        fprintf(stderr, "_cct_subrip_source_read: unhandled branch for counter\n");
        return CCT_FATAL;
    }

    unsigned long counter = 0;
    sctx->counter++;
    sscanf(buffer, "%lu", &counter);
    if (counter != sctx->counter) {
        fprintf(stderr, "_cct_subrip_source_read: counter missing: expected %lu, got %lu\n", sctx->counter, counter);
        sctx->counter = counter;
    }

    if (!fgets(buffer, SRT_MAX_LINE_LENGTH, sctx->file)) {
        if (feof(sctx->file)) {
            fprintf(stderr, "_cct_subrip_source_read: premature end of file (time)\n");
            return CCT_FATAL;
        } else if (ferror(sctx->file)) {
            perror("_cct_subrip_source_read: can't read time");
            return CCT_FATAL;
        }
        fprintf(stderr, "_cct_subrip_source_read: unhandled branch for time\n");
        return CCT_FATAL;
    }

    unsigned int st_h, st_m, st_s, st_ms,
            et_h, et_m, et_s, et_ms;

    unsigned long start_time, end_time;

    sscanf(buffer, "%u:%u:%u,%u --> %u:%u:%u,%u", //TODO add display coords handling
           &st_h, &st_m, &st_s, &st_ms,
           &et_h, &et_m, &et_s, &et_ms);

    start_time = st_ms + (st_s * 1000) + (st_m * 1000 * 60) + (st_h * 1000 * 60 * 60);
    end_time = et_ms + (et_s * 1000) + (et_m * 1000 * 60) + (et_h * 1000 * 60 * 60);

    unsigned int lines_count = 0;
    char lines_buffer[SRT_MAX_LINES][SRT_MAX_LINE_LENGTH];
    memset(lines_buffer, 0, SRT_MAX_LINES * SRT_MAX_LINE_LENGTH * sizeof(char));

    while (fgets(lines_buffer[lines_count], SRT_MAX_LINE_LENGTH, sctx->file) && lines_count < SRT_MAX_LINES) {
        //removing trailing \r\n or \n first
        char *c_ptr = strrchr(lines_buffer[lines_count], '\n');
        if (c_ptr) {
            *c_ptr = '\0';
        }
        c_ptr = strrchr(lines_buffer[lines_count], '\r');
        if (c_ptr) {
            *c_ptr = '\0';
        }
        if (!strlen(lines_buffer[lines_count])) {
            if (lines_count == 0) {
                fprintf(stderr, "_cct_subrip_source_read: unexpected empty line\n");
            }
            //done reading entry
            break;
        }
        lines_count++;
    }

    if (lines_count == SRT_MAX_LINES) {
        fprintf(stdout, "_cct_subrip_source_read: too much lines\n");
        return CCT_FATAL;
    }

    if (feof(sctx->file) && lines_count == 0) {
        fprintf(stderr, "_cct_subrip_source_read: premature end of file (lines)\n");
        return CCT_FATAL;
    }
    if (ferror(sctx->file)) {
        perror("_cct_subrip_source_read: cant read lines");
        return CCT_FATAL;
    }

    cct_sub_entry *new_entry = malloc(sizeof(cct_sub_entry));
    if (!new_entry) {
        perror("_cct_subrip_source_read: malloc() new_entry failed");
        return CCT_FATAL;
    }

    new_entry->counter = counter;
    new_entry->start_time = start_time;
    new_entry->end_time = end_time;
    new_entry->lines_count = lines_count;
    new_entry->lines = (char **) malloc(new_entry->lines_count * sizeof(char*));
    if (!new_entry->lines) {
        perror("_cct_subrip_source_read: malloc() new_entry->lines failed");
        return CCT_FATAL;
    }
    for (unsigned int i = 0; i < lines_count; i++) {
        new_entry->lines[i] = strdup(lines_buffer[i]);
        if (!new_entry->lines[i]) {
            perror("_cct_subrip_source_read: strdup() new_entry->lines[i] failed");
            return CCT_FATAL;
        }
    }

    (*entry) = new_entry;
    return CCT_OK;
}