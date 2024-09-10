static int _parse_entry_multivalue(struct vparse_state *state)
{
    state->entry->multivalue = 1;
    state->entry->v.values = strarray_new();

    NOTESTART();

    while (*state->p) {
        switch (*state->p) {
        /* only one type of quoting */
        case '\\':
            /* seen in the wild - \n split by line wrapping */
            if (state->p[1] == '\r') INC(1);
            if (state->p[1] == '\n') {
                if (state->p[2] != ' ' && state->p[2] != '\t')
                    return PE_BACKQUOTE_EOF;
                INC(2);
            }
            if (!state->p[1])
                return PE_BACKQUOTE_EOF;
            if (state->p[1] == 'n' || state->p[1] == 'N')
                PUTC('\n');
            else
                PUTC(state->p[1]);
            INC(2);
            break;

        case ';':
            strarray_appendm(state->entry->v.values, buf_dup_cstring(&state->buf));
            INC(1);
            break;

        case '\r':
            INC(1);
            break; /* just skip */
        case '\n':
            if (state->p[1] == ' ' || state->p[1] == '\t') {/* wrapped line */
                INC(2);
                break;
            }
            /* otherwise it's the end of the value */
            INC(1);
            goto out;

        default:
            PUTC(*state->p);
            INC(1);
            break;
        }
    }

out:
    /* reaching the end of the file isn't a failure here,
     * it's just another type of end-of-value */
    strarray_appendm(state->entry->v.values, buf_dup_cstring(&state->buf));
    return 0;
}