static engine_return_t engine_fixed_match_all(error_t **error, void *data, const UString *subject, interval_list_t *intervals)
{
    int32_t matches;
    UErrorCode status;
    FETCH_DATA(data, p, fixed_pattern_t);

    matches = 0;
    status = U_ZERO_ERROR;
    if (ustring_empty(p->pattern)) {
        if (IS_WORD_BOUNDED(p->flags)) {
            if (ustring_empty(subject)) {
                return ENGINE_MATCH_FOUND;
            } else {
                int32_t l, u, lastState, state;

                ubrk_setText(p->ubrk, subject->ptr, subject->len, &status);
                if (U_FAILURE(status)) {
                    icu_error_set(error, FATAL, status, "ubrk_setText");
                    return ENGINE_FAILURE;
                }
                if (UBRK_DONE != (l = ubrk_first(p->ubrk))) {
                    lastState = ubrk_getRuleStatus(p->ubrk);
                    while (UBRK_DONE != (u = ubrk_next(p->ubrk))) {
                        state = ubrk_getRuleStatus(p->ubrk);
                        if (UBRK_WORD_NONE == lastState && lastState == state) {
                            return ENGINE_MATCH_FOUND;
                        }
                        lastState = state;
                        l = u;
                    }
                }
                return ENGINE_NO_MATCH;
            }
        } else {
            return ENGINE_MATCH_FOUND;
        }
    } else if (NULL != p->usearch) {
        int32_t l, u;

        if (subject->len > 0) {
            usearch_setText(p->usearch, subject->ptr, subject->len, &status);
            if (U_FAILURE(status)) {
                icu_error_set(error, FATAL, status, "usearch_setText");
                return ENGINE_FAILURE;
            }
            for (l = usearch_first(p->usearch, &status); U_SUCCESS(status) && USEARCH_DONE != l; l = usearch_next(p->usearch, &status)) {
                matches++;
                u = l + usearch_getMatchedLength(p->usearch);
                if (interval_list_add(intervals, subject->len, l, u)) {
                    return ENGINE_WHOLE_LINE_MATCH;
                }
            }
            if (U_FAILURE(status)) {
                icu_error_set(error, FATAL, status, "usearch_[first|next]");
                return ENGINE_FAILURE;
            }
            usearch_unbindText(p->usearch);

            return (matches ? ENGINE_MATCH_FOUND : ENGINE_NO_MATCH);
        } else {
            return ENGINE_NO_MATCH;
        }
    } else {
        UChar *m;
        int32_t pos;

        pos = 0;
        if (NULL != p->ubrk) {
            ubrk_setText(p->ubrk, subject->ptr, subject->len, &status);
            if (U_FAILURE(status)) {
                icu_error_set(error, FATAL, status, "ubrk_setText");
                return ENGINE_FAILURE;
            }
        }
        while (NULL != (m = u_strFindFirst(subject->ptr + pos, subject->len - pos, p->pattern->ptr, p->pattern->len))) {
            pos = m - subject->ptr;
            if (NULL == p->ubrk || (ubrk_isBoundary(p->ubrk, pos) && ubrk_isBoundary(p->ubrk, pos + p->pattern->len))) {
                matches++;
                if (interval_list_add(intervals, subject->len, pos, pos + p->pattern->len)) {
                    return ENGINE_WHOLE_LINE_MATCH;
                }
            }
            pos += p->pattern->len;
        }
        ubrk_unbindText(p->ubrk);

        return (matches ? ENGINE_MATCH_FOUND : ENGINE_NO_MATCH);
    }
}