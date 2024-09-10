/**
 * Don't modify this function, it reproduces a part of fixed engine (engine_fixed_split)
 **/
static UBool engine_bin_split(error_t **error, void *data, const UString *subject, DArray *array, interval_list_t *intervals)
{
    UErrorCode status;
    int32_t l, lastU;
    dlist_element_t *el;
    FETCH_DATA(data, p, bin_pattern_t);

    lastU = l = 0;
    status = U_ZERO_ERROR;

    CASE_FOLD_FORBIDDEN(error, p, FALSE); /* the only engine specific thing */

    if (NULL != p->ubrk) {
        ubrk_setText(p->ubrk, subject->ptr, subject->len, &status);
        if (U_FAILURE(status)) {
            icu_error_set(error, FATAL, status, "ubrk_setText");
            return FALSE;
        }
    }
    for (el = intervals->head; NULL != el; el = el->next) {
        FETCH_DATA(el->data, i, interval_t);

        if (i->lower_limit > 0) {
            if (!binary_fwd_n(p->ubrk, p->pattern, subject, NULL, i->lower_limit - lastU, &l)) {
                break;
            }
        }
        if (!binary_fwd_n(p->ubrk, p->pattern, subject, array, i->upper_limit - i->lower_limit, &l)) {
            break;
        }
        lastU = i->upper_limit;
    }
    ubrk_unbindText(p->ubrk);

    return TRUE;
}